#include "unfolding.hpp"

/** The main function to process and read the input files (lna)
 */
Unfolding::Unfolding(const std::string& _context, std::stringstream& _sol_stream, std::stringstream& _context_stream, const std::string& param){
    context = _context;

    std::string new_line;
    
    unfold_func = split(param,"/");

    while (std::getline(_sol_stream, new_line)) {
        if (!new_line.empty()) {
            std::string temp = std::string(new_line);
            trim_ex(temp);
            if(temp.length() > 0)
                _sol_lines.emplace_back(new_line);
        }
    }

    while (std::getline(_context_stream, new_line)) {
        if (!new_line.empty()) {
            std::string temp = std::string(new_line);
            trim_ex(temp);
            if(temp.length() > 0)
                _context_lines.emplace_back(new_line);
        }
    }
}

/** Get name of Submodel
 */
std::string SubmodelHolder::get_name(){
    return name;
}
/** Add a transition of context file to storage
 */
void SubmodelHolder::add_context_transition(TransitionNodePtr _transition){
    context_transitions.push_back(_transition);
}
/** Add a transition of solidity file to storage
 */
void SubmodelHolder::add_solidity_transition(TransitionNodePtr _transition){
    solidity_transitions.push_back(_transition);
}
/** Get the number of transition in context file 
 */
size_t SubmodelHolder::num_context_transitions(){
    return context_transitions.size();
}
/** Get the number of transition in solidity file 
 */
size_t SubmodelHolder::num_solidity_transitions(){
    return solidity_transitions.size();
}
/** Get transition of context file by index
 */
TransitionNodePtr SubmodelHolder::get_context_transition(size_t i){
    return context_transitions[i];
}
/** Get transition of solidity file by index
 */
TransitionNodePtr SubmodelHolder::get_solidity_transition(size_t i){
    return solidity_transitions[i];
}
/** Add a place of context file to storage
 */
void SubmodelHolder::add_context_place(PlaceNodePtr _place){
    context_places.push_back(_place);
}
/** Get place of context file by index
 */
PlaceNodePtr SubmodelHolder::get_context_place(size_t i){
    return context_places[i];
}
/** Get the number of place in context file 
 */
size_t SubmodelHolder::num_context_places(){
    return context_places.size();
}
/** Add a transition of solidity file to storage
 */
void SubmodelHolder::add_solidity_place(PlaceNodePtr _place){
    solidity_places.push_back(_place);
}
/** Get place of solidity file by index
 */
PlaceNodePtr SubmodelHolder::get_solidity_place(size_t i){
    return solidity_places[i];
}
/** Get the number of place in solidity file 
 */
size_t SubmodelHolder::num_solidity_places(){
    return solidity_places.size();
}
/** Get an object of SubmodelHolder by name
 */
SubmodelHolderPtr Unfolding::get_submodel_holder_by_name(const std::string& _name){
    for(auto it = submodelHolders.begin(); it != submodelHolders.end(); ++it){
        if((*it)->get_name() == _name){
            return (*it);
        }
    }
    return nullptr;
}
/** Add transition of context file to specific submodel indicated by the name
 */
void Unfolding::add_context_transition_to_submodel(const std::string& _name, TransitionNodePtr _transition){
    SubmodelHolderPtr temp = get_submodel_holder_by_name(_name);
    if(temp != nullptr){
        temp->add_context_transition(_transition);
    }else{
        SubmodelHolderPtr new_th = std::make_shared<SubmodelHolder>(_name);
        new_th->add_context_transition(_transition);
        submodelHolders.push_back(new_th);
    }
}
/** Add transition of solidity file to specific submodel indicated by the name
 */
void Unfolding::add_solidity_transition_to_submodel(const std::string& _name, TransitionNodePtr _transition){
    SubmodelHolderPtr temp = get_submodel_holder_by_name(_name);
    if(temp != nullptr){
        temp->add_solidity_transition(_transition);
    }else{
        SubmodelHolderPtr new_th = std::make_shared<SubmodelHolder>(_name);
        new_th->add_solidity_transition(_transition);
        submodelHolders.push_back(new_th);
    }
}
/** Add place of solidity file to specific submodel indicated by the name
 */
void Unfolding::add_solidity_place_to_submodel(const std::string& _name, PlaceNodePtr _place){
    SubmodelHolderPtr temp = get_submodel_holder_by_name(_name);
    if(temp != nullptr){
        temp->add_solidity_place(_place);
    }else{
        SubmodelHolderPtr new_th = std::make_shared<SubmodelHolder>(_name);
        new_th->add_solidity_place(_place);
        submodelHolders.push_back(new_th);
    }
}
/** Add place of context file to specific submodel indicated by the name
 */
void Unfolding::add_context_place_to_submodel(const std::string& _name, PlaceNodePtr _place){
    SubmodelHolderPtr temp = get_submodel_holder_by_name(_name);
    if(temp != nullptr){
        temp->add_context_place(_place);
    }else{
        SubmodelHolderPtr new_th = std::make_shared<SubmodelHolder>(_name);
        new_th->add_context_place(_place);
        submodelHolders.push_back(new_th);
    }
}

/** Read code in lna file and convert to object
 */
void Unfolding::analyseLnaFile(const std::string type){
    if(type == "context"){
        ptr_pointer_end = _context_lines.end();
        ptr_pointer_line = _context_lines.begin();
    }else if(type == "solidity"){
        ptr_pointer_end = _sol_lines.end();
        ptr_pointer_line = _sol_lines.begin();
    }
    
    while(ptr_pointer_line != ptr_pointer_end){
        std::string model_name = get_first_alpha_only_string(*ptr_pointer_line);
        if(model_name.length() > 0){
            if(type == "solidity"){
                model->set_name(model_name);
            }

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

    std::string current_submodel_name;
    while (ptr_pointer_line != ptr_pointer_end){       
        if(retrieve_string_element(*ptr_pointer_line,1," ") == "Function:"){ 
            current_submodel_name = retrieve_string_element(*ptr_pointer_line,2," ");
        }else{
            std::string keyword = get_first_alpha_only_string(*ptr_pointer_line);
            if(keyword == TRANSITION_TOKEN){
                TransitionNodePtr transition = handleTransition(ptr_pointer_line,ptr_pointer_end);
                if(type == "context"){
                    add_context_transition_to_submodel(current_submodel_name,transition);
                }else if(type == "solidity"){
                    add_solidity_transition_to_submodel(current_submodel_name,transition);
                }
            }else if(keyword == PLACE_TOKEN){
                PlaceNodePtr place = handlePlace(ptr_pointer_line,ptr_pointer_end);
                if(type == "context"){
                    add_context_place_to_submodel(current_submodel_name,place);
                }else if(type == "solidity"){
                    add_solidity_place_to_submodel(current_submodel_name,place);
                }
            }else if(keyword == TYPE_TOKEN){
                ColorNodePtr color = handleColor(ptr_pointer_line,ptr_pointer_end);
                model->add_member(color);
            }else if(keyword == FUNCTION_TOKEN){
                FunctionNodePtr function = handleFunction(ptr_pointer_line,ptr_pointer_end);
                model->add_member(function);
            }
        }

        ptr_pointer_line++;
    }
}
/** Unfolding the solidity file by instructions in the context file  
 */
NetNodePtr Unfolding::unfolding(){
    model = std::make_shared<NetNode>();

    analyseLnaFile("context");

    analyseLnaFile("solidity");

    if(context == DCRContext){
        unfolding_dcr_context();
    }else if(context == FreeContext){
        unfolding_free_context();
    }

    CommentNodePtr prop_area = make_shared<CommentNode>("\n/*** proposition ***/\n");
    model->add_member(prop_area);
    return model;
}

void Unfolding::unfolding_free_context(){

}
/** Unfolding the solidity file by instructions in the DCR context file  
 */
void Unfolding::unfolding_dcr_context(){
    for(auto it = submodelHolders.begin(); it != submodelHolders.end(); ++it){
        string submodel_name = (*it)->get_name();
        model->add_member(make_shared<CommentNode>("\n/*\n * Function: " + submodel_name + "\n */\n"));
        if(submodel_name == "state"){
            for(size_t i = 0; i < (*it)->num_context_places(); i++){
                model->add_member((*it)->get_context_place(i));
            }

            PlaceNodePtr state_cflow = std::make_shared<PlaceNode>();
            state_cflow->set_name("cflow");
            state_cflow->set_domain("epsilon");
            state_cflow->set_init("epsilon");
            model->add_member(state_cflow);

            for(size_t i = 0; i < (*it)->num_solidity_places(); i++){
                model->add_member((*it)->get_solidity_place(i));
            }
            for(size_t i = 0; i < (*it)->num_context_transitions(); i++){
                model->add_member((*it)->get_context_transition(i));
            }
            for(size_t i = 0; i < (*it)->num_solidity_transitions(); i++){
                model->add_member((*it)->get_solidity_transition(i));
            }
        }else if(std::find(unfold_func.begin(), unfold_func.end(), submodel_name) != unfold_func.end()){
            PlaceNodePtr cflow = std::make_shared<PlaceNode>();
            cflow->set_name(submodel_name+"_cflow");
            cflow->set_domain("epsilon");
            model->add_member(cflow);
            
            for(size_t i = 0; i < (*it)->num_context_places(); i++){
                model->add_member((*it)->get_context_place(i));
            }
            for(size_t i = 0; i < (*it)->num_solidity_places(); i++){
                model->add_member((*it)->get_solidity_place(i));
            }
            for(size_t i = 0; i < (*it)->num_context_transitions(); i++){
                TransitionNodePtr temp = (*it)->get_context_transition(i);

                ArcNodePtr cflow_arc_in = std::make_shared<ArcNode>();
                cflow_arc_in->set_placeName("cflow");
                cflow_arc_in->set_label("epsilon");
                temp->add_inArc(cflow_arc_in);

                ArcNodePtr cflow_arc_out = std::make_shared<ArcNode>();
                cflow_arc_out->set_placeName(cflow->get_name());
                cflow_arc_out->set_label("epsilon");
                temp->add_outArc(cflow_arc_out);

                model->add_member(temp);
            }
            for(size_t i = 0; i < (*it)->num_solidity_transitions(); i++){
                TransitionNodePtr temp = (*it)->get_solidity_transition(i);
                if(temp->get_in_arc_by_name("S") != nullptr){
                    ArcNodePtr cflow_arc_in = std::make_shared<ArcNode>();
                    cflow_arc_in->set_placeName(cflow->get_name());
                    cflow_arc_in->set_label("epsilon");
                    temp->add_inArc(cflow_arc_in);
                }

                if(temp->get_out_arc_by_name("S") != nullptr){
                    ArcNodePtr cflow_arc_out = std::make_shared<ArcNode>();
                    cflow_arc_out->set_placeName("cflow");
                    cflow_arc_out->set_label("epsilon");
                    temp->add_outArc(cflow_arc_out);
                }

                model->add_member(temp);
            }
        }else{
            for(size_t i = 0; i < (*it)->num_context_places(); i++){
                model->add_member((*it)->get_context_place(i));
            }
            for(size_t i = 0; i < (*it)->num_context_transitions(); i++){
                TransitionNodePtr temp = (*it)->get_context_transition(i);

                ArcNodePtr cflow_arc_in = std::make_shared<ArcNode>();
                cflow_arc_in->set_placeName("cflow");
                cflow_arc_in->set_label("epsilon");
                temp->add_inArc(cflow_arc_in);

                ArcNodePtr cflow_arc_out = std::make_shared<ArcNode>();
                cflow_arc_out->set_placeName("cflow");
                cflow_arc_out->set_label("epsilon");
                temp->add_outArc(cflow_arc_out);

                model->add_member(temp);
            }
        }
    }
}

