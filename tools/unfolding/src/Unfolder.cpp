#include "./Unfolder.hpp"

Unfolder::Unfolder(const StructuredNetNodePtr& _context, std::stringstream& _sol_lna_stream, const nlohmann::json& lna_json,const nlohmann::json& ltl_json){
    sol_information = lna_json;
    ltl_information = ltl_json;

    unfolded_func = FindUnfoldedFunction();
  
    cpn_model = analyseLnaFile(_sol_lna_stream);

    cpn_context = _context;
}

std::vector<std::string> Unfolder::FindUnfoldedFunction(){
    std::vector<std::string> unfolded_func;
    unfolded_func.push_back("state");
    std::vector<std::string> list_required_variables;
    
    std::string ltl_type = ltl_information.at("type");
    auto ltl_param = ltl_information.at("params");
    if(ltl_type == "general"){
        std::string ltl_name = ltl_param.at("name");
        if(ltl_name == "under_over_flow"){
            auto inputs = ltl_param.at("inputs");
            std::string variable = inputs.at("selected_variable");
            list_required_variables.push_back(variable);
        }
    }else if(ltl_type == "specific"){
        list_required_variables = LTLTranslator::getListVariableFromFormula(ltl_param.at("formula"));
    } 

    std::map<std::string, std::string> global_variables;
    auto gvs = sol_information.at("globalVariables");
    for(size_t i = 0; i < gvs.size(); i++){
        auto gv = gvs[i];
        std::string gv_name = gv.at("name");
        global_variables[gv_name] = gv.at("placeType");
    }
    
    auto functions = sol_information.at("functions");
    for(size_t i = 0; i < functions.size(); i++){
        std::map<std::string, std::string> local_var;
        auto lvs =  functions[i].at("localVariables");
        for(size_t i = 0; i < lvs.size(); i++){
            auto lv = lvs[i];
            std::string lv_name = lv.at("name"); 
            local_var[lv_name] = lv.at("place");
        }
        for(auto it = list_required_variables.begin(); it != list_required_variables.end(); ++it){
            if(local_var.find(*it) != local_var.end()){
                unfolded_func.push_back(functions[i].at("name"));
                break;
            }
        }        
    }

    for(auto it = list_required_variables.begin(); it != list_required_variables.end(); ++it){
        if(global_variables.find(*it) != global_variables.end()){
            unfolded_func.clear();
            break;
        }
    }

    return unfolded_func;
}

StructuredNetNodePtr Unfolder::analyseLnaFile(std::stringstream& _sol_lna_stream){
    StructuredNetNodePtr model = std::make_shared<StructuredNetNode>();
    std::list<std::string> _sol_lines;

    std::string new_line;
    while (std::getline(_sol_lna_stream, new_line)) {
        if (!new_line.empty()) {
            std::string temp = std::string(new_line);
            trim_ex(temp);
            if(temp.length() > 0)
                _sol_lines.emplace_back(new_line);
        }
    }
    std::list<std::string>::iterator ptr_pointer_end = _sol_lines.end();
    std::list<std::string>::iterator ptr_pointer_line = _sol_lines.begin();
    
    while(ptr_pointer_line != ptr_pointer_end){
        std::string model_name = get_first_alpha_only_string(*ptr_pointer_line);
        if(model_name.length() > 0){
            model->set_name(model_name);

            std::string parameter_def = substr_by_edge(*ptr_pointer_line,"(",")");
            std::vector<std::string> parameters = split(parameter_def,",");
            if(parameters.size() > 0){
                for(auto it = parameters.begin(); it != parameters.end(); ++it){
                    std::vector<std::string> param = split_ex(*it,":=",2);
                    if(param.size() == 2){
                        trim_ex(param[0]);
                        trim_ex(param[1]);

                        ParameterNodePtr mpr = std::make_shared<ParameterNode>();
                        mpr->set_name(param[0]);
                        mpr->set_number(param[1]);
                        model->add_parameter(mpr);
                    }
                }
            }
            break;
        }
        ptr_pointer_line++;
    }

    bool wait2set = false;
    std::string current_submodel_name;
    while (ptr_pointer_line != ptr_pointer_end){       
        if(retrieve_string_element(*ptr_pointer_line,1," ") == "Function:"){ 
            current_submodel_name = retrieve_string_element(*ptr_pointer_line,2," ");
            wait2set = true;
        }else{
            std::string keyword = get_first_alpha_only_string(*ptr_pointer_line);
            if(keyword == TRANSITION_TOKEN){
                TransitionNodePtr transition = handleTransition(ptr_pointer_line,ptr_pointer_end);
                if(wait2set){
                    model->add_transition(std::make_shared<CommentNode>("\n/*\n * Function: "+current_submodel_name+"\n */\n"));
                    wait2set = false;
                }
                model->add_transition(transition);
            }else if(keyword == PLACE_TOKEN){
                PlaceNodePtr place = handlePlace(ptr_pointer_line,ptr_pointer_end);
                if(wait2set){
                    model->add_place(std::make_shared<CommentNode>("\n/*\n * Function: "+current_submodel_name+"\n */\n"));
                    wait2set = false;
                }
                model->add_place(place);
            }else if(keyword == TYPE_TOKEN || keyword == SUBTYPE_TOKEN){
                ColorNodePtr color = handleColor(ptr_pointer_line,ptr_pointer_end);
                model->add_color(color);
            }else if(keyword == FUNCTION_TOKEN){
                FunctionNodePtr function = handleFunction(ptr_pointer_line,ptr_pointer_end);
                model->add_function(function);
            }
        }

        ptr_pointer_line++;
    }
    return model;
}
 
std::map<std::string,std::string> Unfolder::UnfoldModel(const std::string& _context){
    StructuredNetNodePtr unfold_model;
    if(_context == "DCR" || _context == "CPN"){
        unfold_model = unfoldModelWithDCRContext();
    }else if(_context == "FREE"){
        unfold_model = unfoldModelWithFreeContext();
    }else{
        unfold_model = std::make_shared<StructuredNetNode>();
    }

    LTLTranslator ltl_translator = LTLTranslator(sol_information,ltl_information);
    std::map<std::string,std::string> ltl_result = ltl_translator.translate();

    unfold_model->add_transition(std::make_shared<CommentNode>(ltl_result["propositions"]));
    
    std::map<std::string,std::string> result;
    result["lna"] = unfold_model->source_code();
    result["prop"] = ltl_result["property"];

    return result;
}
StructuredNetNodePtr Unfolder::unfoldModelWithFreeContext(){
    StructuredNetNodePtr unfold_model = std::make_shared<StructuredNetNode>();

    unfold_model->set_name(cpn_model->get_name());
    if(unfolded_func.size() > 0){
        std::string current_submodel_name;

        for(size_t i = 0; i < cpn_model->num_parameters(); i++){
            unfold_model->add_parameter(cpn_model->get_parameter(i));
        }
        for(size_t i = 0; i < cpn_model->num_colors(); i++){
            unfold_model->add_color(cpn_model->get_color(i));
        }
        for(size_t i = 0; i < cpn_model->num_functions(); i++){
            unfold_model->add_function(cpn_model->get_function(i));
        }

        std::vector<std::string> list_func;
        for(size_t i = 0; i < cpn_model->num_places(); i++){
            LnaNodePtr node = cpn_model->get_place(i);
            if(node->get_node_type() == LnaNodeTypeComment){
                current_submodel_name = get_model_name_from_comment(std::static_pointer_cast<CommentNode>(node));
                if (std::find(unfolded_func.begin(), unfolded_func.end(), current_submodel_name) != unfolded_func.end()){
                    unfold_model->add_place(std::make_shared<CommentNode>("\n/*\n * Function: "+current_submodel_name+"\n */\n"));
                }
            }else if(node->get_node_type() == LnaNodeTypePlace){
                PlaceNodePtr place = std::static_pointer_cast<PlaceNode>(node);
                if (std::find(unfolded_func.begin(), unfolded_func.end(), current_submodel_name) != unfolded_func.end()){
                    unfold_model->add_place(place);
                }
            }
        }
        for(size_t i = 0; i < cpn_model->num_transitions(); i++){
            LnaNodePtr node = cpn_model->get_transition(i);
            if(node->get_node_type() == LnaNodeTypeComment){
                current_submodel_name = get_model_name_from_comment(std::static_pointer_cast<CommentNode>(node));
                if (std::find(unfolded_func.begin(), unfolded_func.end(), current_submodel_name) != unfolded_func.end()){
                    unfold_model->add_transition(std::make_shared<CommentNode>("\n/*\n * Function: "+current_submodel_name+"\n */\n"));
                }
            }else if(node->get_node_type() == LnaNodeTypeTransition){
                TransitionNodePtr transition = std::static_pointer_cast<TransitionNode>(node);
                if (std::find(unfolded_func.begin(), unfolded_func.end(), current_submodel_name) != unfolded_func.end()){
                    unfold_model->add_transition(transition);
                }
            }
        }
    }
    return unfold_model;
}

StructuredNetNodePtr Unfolder::unfoldModelWithDCRContext(){
    StructuredNetNodePtr unfold_model = std::make_shared<StructuredNetNode>();

    unfold_model->set_name(cpn_model->get_name());

    if(unfolded_func.size() > 0){
        std::string current_submodel_name;

        for(size_t i = 0; i < cpn_context->num_parameters(); i++){
            unfold_model->add_parameter(cpn_context->get_parameter(i));
        }
        for(size_t i = 0; i < cpn_context->num_colors(); i++){
            unfold_model->add_color(cpn_context->get_color(i));
        }
        for(size_t i = 0; i < cpn_context->num_functions(); i++){
            unfold_model->add_function(cpn_context->get_function(i));
        }
        for(size_t i = 0; i < cpn_context->num_places(); i++){
            LnaNodePtr node = cpn_context->get_place(i);
            if(node->get_node_type() == LnaNodeTypeComment){
                current_submodel_name = get_model_name_from_comment(std::static_pointer_cast<CommentNode>(node));
                if (std::find(unfolded_func.begin(), unfolded_func.end(), current_submodel_name) != unfolded_func.end()){
                    unfold_model->add_place(std::make_shared<CommentNode>("\n/*\n * Function: "+current_submodel_name+"\n */\n"));
                }
            }else if(node->get_node_type() == LnaNodeTypePlace){
                PlaceNodePtr place = std::static_pointer_cast<PlaceNode>(node);
                if (std::find(unfolded_func.begin(), unfolded_func.end(), current_submodel_name) != unfolded_func.end()){
                    unfold_model->add_place(place);
                }
            }
        }
        for(size_t i = 0; i < cpn_context->num_transitions(); i++){
            LnaNodePtr node = cpn_context->get_transition(i);
            if(node->get_node_type() == LnaNodeTypeComment){
                current_submodel_name = get_model_name_from_comment(std::static_pointer_cast<CommentNode>(node));
                unfold_model->add_transition(std::make_shared<CommentNode>("\n/*\n * Function: "+current_submodel_name+"\n */\n"));
            }else if(node->get_node_type() == LnaNodeTypeTransition){
                TransitionNodePtr transition = std::static_pointer_cast<TransitionNode>(node);
                if (std::find(unfolded_func.begin(), unfolded_func.end(), current_submodel_name) != unfolded_func.end()){
                    ArcNodePtr cflow_arc_in = std::make_shared<ArcNode>();
                    cflow_arc_in->set_placeName("state_cflow");
                    cflow_arc_in->set_label("epsilon");
                    transition->add_inArc(cflow_arc_in);

                    ArcNodePtr cflow_arc_out = std::make_shared<ArcNode>();
                    cflow_arc_out->set_placeName(current_submodel_name+"_cflow");
                    cflow_arc_out->set_label("epsilon");
                    transition->add_outArc(cflow_arc_out);

                    unfold_model->add_transition(transition);
                }else{
                    ArcNodePtr cflow_arc_in = std::make_shared<ArcNode>();
                    cflow_arc_in->set_placeName("state_cflow");
                    cflow_arc_in->set_label("epsilon");
                    transition->add_inArc(cflow_arc_in);

                    ArcNodePtr cflow_arc_out = std::make_shared<ArcNode>();
                    cflow_arc_out->set_placeName("state_cflow");
                    cflow_arc_out->set_label("epsilon");
                    transition->add_outArc(cflow_arc_out);

                    unfold_model->add_transition(transition);
                }
            }
        }


        for(size_t i = 0; i < cpn_model->num_parameters(); i++){
            unfold_model->add_parameter(cpn_model->get_parameter(i));
        }
        for(size_t i = 0; i < cpn_model->num_colors(); i++){
            unfold_model->add_color(cpn_model->get_color(i));
        }
        for(size_t i = 0; i < cpn_model->num_functions(); i++){
            unfold_model->add_function(cpn_model->get_function(i));
        }

        std::vector<std::string> list_func;
        for(size_t i = 0; i < cpn_model->num_places(); i++){
            LnaNodePtr node = cpn_model->get_place(i);
            if(node->get_node_type() == LnaNodeTypeComment){
                current_submodel_name = get_model_name_from_comment(std::static_pointer_cast<CommentNode>(node));
                if (std::find(unfolded_func.begin(), unfolded_func.end(), current_submodel_name) != unfolded_func.end()){
                    unfold_model->add_place(std::make_shared<CommentNode>("\n/*\n * Function: "+current_submodel_name+"\n */\n"));
                    if(std::find(list_func.begin(), list_func.end(), current_submodel_name) == list_func.end()){
                        PlaceNodePtr cflow = std::make_shared<PlaceNode>();
                        cflow->set_name(current_submodel_name+"_cflow");
                        cflow->set_domain("epsilon");
                        if(current_submodel_name == "state"){
                            cflow->set_init("epsilon");
                        }
                        unfold_model->add_place(cflow);
                        list_func.push_back(current_submodel_name);
                    }
                }
            }else if(node->get_node_type() == LnaNodeTypePlace){
                PlaceNodePtr place = std::static_pointer_cast<PlaceNode>(node);
                if (std::find(unfolded_func.begin(), unfolded_func.end(), current_submodel_name) != unfolded_func.end()){
                    unfold_model->add_place(place);
                }
            }
        }
        for(size_t i = 0; i < cpn_model->num_transitions(); i++){
            LnaNodePtr node = cpn_model->get_transition(i);
            if(node->get_node_type() == LnaNodeTypeComment){
                current_submodel_name = get_model_name_from_comment(std::static_pointer_cast<CommentNode>(node));
                if (std::find(unfolded_func.begin(), unfolded_func.end(), current_submodel_name) != unfolded_func.end()){
                    unfold_model->add_transition(std::make_shared<CommentNode>("\n/*\n * Function: "+current_submodel_name+"\n */\n"));
                }
            }else if(node->get_node_type() == LnaNodeTypeTransition){
                TransitionNodePtr transition = std::static_pointer_cast<TransitionNode>(node);
                if (std::find(unfolded_func.begin(), unfolded_func.end(), current_submodel_name) != unfolded_func.end()){
                    if(transition->get_in_arc_by_name("S") != nullptr){
                        ArcNodePtr cflow_arc_in = std::make_shared<ArcNode>();
                        cflow_arc_in->set_placeName(current_submodel_name+"_cflow");
                        cflow_arc_in->set_label("epsilon");
                        transition->add_inArc(cflow_arc_in);
                    }

                    if(transition->get_out_arc_by_name("S") != nullptr){
                        ArcNodePtr cflow_arc_out = std::make_shared<ArcNode>();
                        cflow_arc_out->set_placeName("state_cflow");
                        cflow_arc_out->set_label("epsilon");
                        transition->add_outArc(cflow_arc_out);
                    }

                    unfold_model->add_transition(transition);
                }
            }
        }

    }
    return unfold_model;
}

std::string Unfolder::get_model_name_from_comment(const CommentNodePtr& _comment){
    std::string name = substr_by_edge(_comment->get_comment(),"Function:","*/");
    trim_ex(name);
    return name;
}
