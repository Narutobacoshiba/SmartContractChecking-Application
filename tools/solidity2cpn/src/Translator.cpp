#include "../include/Translator.hpp"
#include "../include/Utils.hpp"

namespace SOL2CPN {

void SubNetNode::set_in_places(const std::vector<PlaceNodePtr> _places){
    in_places = _places;
}

PlaceNodePtr SubNetNode::get_in_places(const unsigned int& x){
    return in_places[x];
}

size_t SubNetNode::num_in_places(){
    return in_places.size();
}

void SubNetNode::set_name(const std::string& _name){
    name = _name;
}

std::string SubNetNode::get_name() const{
    return name;
}

void SubNetNode::add_in_place(const PlaceNodePtr& _place){
    if(get_in_place_by_name(_place->get_name()) == nullptr){
        in_places.push_back(_place);
    }
}

PlaceNodePtr SubNetNode::get_in_place_by_domain(const string& _domain){
    for (auto it = in_places.begin(); it != in_places.end(); ++it)
            if ((*it)->get_domain() == _domain)
                return (*it);
    return nullptr;
}

PlaceNodePtr SubNetNode::get_in_place_by_name(const string& _name){
    for (auto it = in_places.begin(); it != in_places.end(); ++it)
            if ((*it)->get_name() == _name)
                return (*it);
    return nullptr;
}

void SubNetNode::add_tempdata_place(const PlaceNodePtr& _place, const string& _name){
    tempdata_places[_name] = _place;
}

void SubNetNode::remove_tempdata_place_bye_name(const string& _name){
    if ( tempdata_places.find(_name) != tempdata_places.end() ) {
        tempdata_places.erase(_name);
    }
    return;              
}

PlaceNodePtr SubNetNode::get_place_tempdata_by_name(const string& _name){
    if ( tempdata_places.find(_name) != tempdata_places.end() ) {
        return tempdata_places[_name];
    }
    return nullptr;
}

void SubNetNode::set_wft_transition(const TransitionNodePtr& _trans){
    wait_for_let_transition = _trans;
}

TransitionNodePtr SubNetNode::get_wft_transition(){
    return wait_for_let_transition;
}



NetNodePtr Translator::translate() {
    net = std::make_shared<NetNode>();

    for (int i = 0; i < rootNode->num_fields(); i++)
            if (rootNode->get_field(i)->get_node_type() == NodeTypeContractDefinition) {
                //create the net
                auto contractNode = std::static_pointer_cast<ContractDefinitionNode>(rootNode->get_field(i));
                net->set_name(contractNode->get_name());
                generatePredefinedColors();
                PlaceNodePtr state_place = std::make_shared<PlaceNode>();
                state_place->set_name("state");
                state_place->set_domain("STATE");
                net->add_place(state_place);

                for (int i = 0; i < contractNode->num_members(); i++){
                    auto member = contractNode->get_member(i);
                    if (member->get_node_type() == NodeTypeStructDefinition) {
                        auto structNode = std::static_pointer_cast<StructDefinitionNode>(member);
                        StructColorNodePtr struct_type = translateStruct(structNode);

                        net->add_color(struct_type);
                    }else if (member->get_node_type() == NodeTypeVariableDeclaration) {
                        translateVariableDeclaration(member);
                    }
                    else if (member->get_node_type() == NodeTypeFunctionDefinition) {
                        is_in_function = true;
                        FunctionDefinitionNodePtr func = std::static_pointer_cast<FunctionDefinitionNode>(member);
                        generateFunctionColor(func);
                        PlaceNodePtr func_place = createParFuncPlace(func->get_name());
                        net->add_place(func_place);

                        BlockNodePtr func_body = func->get_function_body();
                        SubNetNodePtr func_subnet = std::make_shared<SubNetNode>();
                        func_subnet->set_name(func->get_name());
                        func_subnet->set_in_places(std::vector<PlaceNodePtr>{state_place,func_place});
                        current_subnet = func_subnet;

                        translateBlock(func_body);
                        is_in_function = false;
                    }
                }
            }

    return net;
}

void Translator::translateBlock(BlockNodePtr block){
    for(int i = 0; i < block->num_statements(); i++){
        ASTNodePtr statement = block->get_statement(i);
        if(statement->get_node_type() == NodeTypeIfStatement){
            IfStatementNodePtr if_statement = std::static_pointer_cast<IfStatementNode>(statement);
            translateIfStatement(if_statement);
        }else if(statement->get_node_type() == NodeTypeForStatement){
            ForStatementNodePtr for_statement = std::static_pointer_cast<ForStatementNode>(statement);
            translateForStatement(for_statement);
        }else if(statement->get_node_type() == NodeTypeExpressionStatement){
            ExpressionStatementNodePtr expression_statement = std::static_pointer_cast<ExpressionStatementNode>(statement);
            translateExpressionStatement(expression_statement);
        }else if(statement->get_node_type() == NodeTypeVariableDeclarationStatement){
            VariableDeclarationStatementNodePtr vardecl_statement = std::static_pointer_cast<VariableDeclarationStatementNode>(statement);
            translateVariableDeclarationStatement(vardecl_statement);
        }
        current_subnet->count++;
    }
}

void Translator::translateIfStatement(IfStatementNodePtr statement){
    std::string exp = translateRequireExpressionToString(statement->get_condition());

    TransitionNodePtr ifstate = std::make_shared<TransitionNode>();
    ifstate->set_name(current_subnet->get_name()+"_ifstate"+std::to_string(current_subnet->count));
    ifstate->set_guard(exp);

    std::vector<PlaceNodePtr> out_places;
    PlaceNodePtr cflow = std::make_shared<PlaceNode>();
    cflow->set_name(current_subnet->get_name()+"_is"+std::to_string(current_subnet->count));
    cflow->set_domain(current_subnet->get_name()+"_state");
    cflow->set_place_type(PlaceTypeControlFlow);
    net->add_place(cflow);
    out_places.push_back(cflow);

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");
        ifstate->add_inArc(arc);

        if(param->get_name() == "state"){
            ArcNodePtr narc = std::make_shared<ArcNode>();
            narc->set_placeName(cflow->get_name());
            narc->set_label("<({"+param->get_name()+"_pr,"+current_subnet->get_name()+"_parameter_pr})>");
            ifstate->add_outArc(narc);

        }else if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr noarc = std::make_shared<ArcNode>();
            noarc->set_placeName(cflow->get_name());
            noarc->set_label("<("+param->get_name()+"_pr)>");
            ifstate->add_outArc(noarc);

        }else if(param->get_place_type() == PlaceTypeData){
            ifstate->add_outArc(arc);
            out_places.push_back(param);
        }else if(param->get_place_type() == PlaceTypeTempData){
            ifstate->add_outArc(arc);
        }
    }

    net->add_transition(ifstate);
    current_subnet->set_in_places(out_places);

    if(statement->get_then()->get_node_type() == NodeTypeBlockNode){
        translateBlock(std::static_pointer_cast<BlockNode>(statement->get_then()));
    }else if(statement->get_then()->get_node_type() == NodeTypeExpressionStatement){
        translateExpressionStatement(std::static_pointer_cast<ExpressionStatementNode>(statement->get_then()));
    }
}

void Translator::translateVariableDeclarationStatement(VariableDeclarationStatementNodePtr statement){
    VariableDeclarationNodePtr decl = statement->get_decl();
    translateVariableDeclaration(decl);

    std::vector<PlaceNodePtr> out_places;
    TransitionNodePtr vardec = std::make_shared<TransitionNode>();
    vardec->set_name(current_subnet->get_name()+"_vardec"+std::to_string(current_subnet->count));
    
    PlaceNodePtr cflow = std::make_shared<PlaceNode>();
    cflow->set_name(current_subnet->get_name()+"_vd"+std::to_string(current_subnet->count));
    cflow->set_domain(current_subnet->get_name()+"_state");
    cflow->set_place_type(PlaceTypeControlFlow);
    net->add_place(cflow);
    out_places.push_back(cflow);

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");

        if(param->get_name() == "state"){
            ArcNodePtr narc = std::make_shared<ArcNode>();
            narc->set_placeName(cflow->get_name());
            narc->set_label("<({"+param->get_name()+"_pr,"+current_subnet->get_name()+"_parameter_pr})>");
            vardec->add_outArc(narc);

        }else if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr noarc = std::make_shared<ArcNode>();
            noarc->set_placeName(cflow->get_name());
            noarc->set_label("<("+param->get_name()+"_pr)>");
            vardec->add_outArc(noarc);

        }else if(param->get_place_type() == PlaceTypeData){
            vardec->add_outArc(arc);
            out_places.push_back(param);
        }else if(param->get_place_type() == PlaceTypeTempData){
            vardec->add_outArc(arc);
        }

        if(param->get_place_type() != PlaceTypeWaitData){
            vardec->add_inArc(arc);
        }else{
            ArcNodePtr arc = std::make_shared<ArcNode>();
            arc->set_placeName(param->get_name());
            arc->set_label("<("+translateRequireExpressionToString(statement->get_value())+")>");

            param->set_place_type(PlaceTypeTempData);
            vardec->add_outArc(arc);
        }
    }

    net->add_transition(vardec);
    current_subnet->set_in_places(out_places);
}

void Translator::translateExpressionStatement(ExpressionStatementNodePtr statement){
    translate_value_equivalent_node(statement->get_expression());
}

void Translator::translate_value_equivalent_node(ASTNodePtr _node){
    if (_node->get_node_type() == NodeTypeFunctionCall) {
        translateFunctionCall(std::static_pointer_cast<FunctionCallNode>(_node));
    }else if(_node->get_node_type() == NodeTypeVariableDeclarationStatement){

    }else if(_node->get_node_type() == NodeTypeAssignment){
        translateAssignment(std::static_pointer_cast<AssignmentNode>(_node));
    }
}

void Translator::translateAssignment(AssignmentNodePtr assignment){
    TransitionNodePtr assign = std::make_shared<TransitionNode>();
    assign->set_name(current_subnet->get_name()+"_assign"+std::to_string(current_subnet->count));

    std::vector<PlaceNodePtr> out_places;
    PlaceNodePtr cflow = std::make_shared<PlaceNode>();
    cflow->set_name(current_subnet->get_name()+"_ass"+std::to_string(current_subnet->count));
    cflow->set_domain(current_subnet->get_name()+"_state");
    cflow->set_place_type(PlaceTypeControlFlow);
    net->add_place(cflow);

    out_places.push_back(cflow);

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");
        assign->add_inArc(arc);
        if(param->get_name() == "state"){
            ArcNodePtr narc = std::make_shared<ArcNode>();
            narc->set_placeName(cflow->get_name());
            narc->set_label("<({"+param->get_name()+"_pr,"+current_subnet->get_name()+"_parameter_pr})>");
            assign->add_outArc(narc);
        }else if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr narc = std::make_shared<ArcNode>();
            narc->set_placeName(cflow->get_name());
            narc->set_label("<({"+translateRequireExpressionToString(assignment)+","+param->get_name()+"_pr.par})>");
            assign->add_outArc(narc);          
        }else if(param->get_place_type() == PlaceTypeData){
            assign->add_outArc(arc);
            out_places.push_back(param);
        }else if(param->get_place_type() == PlaceTypeTempData){
            assign->add_outArc(arc);
        }
    }

    net->add_transition(assign);
    current_subnet->set_in_places(out_places);

}

void Translator::translateFunctionCall(FunctionCallNodePtr func_call){
    if(func_call->get_callee()->get_node_type() == NodeTypeIdentifier){
        IdentifierNodePtr func_name_handler = std::static_pointer_cast<IdentifierNode>(func_call->get_callee());
        if(func_name_handler->get_name() == "require"){
            translateRequireFunctionCall(func_call->get_argument(0));
        }
    }
    
}

std::string Translator::translateMemberAcess(std::string _member){
    //temp need update in future
    if(_member == "length"){
        return "'size";
    }else if(_member == "sender"){
        return ".sender.adr";
    }
    return "."+_member;
}

std::string Translator::translateOperator(std::string _operator){
    if(_operator == "=="){
        return "=";
    }else if(_operator == "<="){
        return "<=";
    }else if(_operator == ">="){
        return ">=";
    }else if(_operator == "<"){
        return "<";
    }else if(_operator == ">"){
        return ">";
    }else if(_operator == "!"){
        return "not";
    }else if(_operator == "&&"){
        return "and";
    }else if(_operator == "||"){
        return "or";
    }
    return _operator;
}

std::string Translator::translateRequireExpressionToString(ASTNodePtr _arg){
    std::string ret;
    if(_arg->get_node_type() == NodeTypeAssignment){
        AssignmentNodePtr exp = std::static_pointer_cast<AssignmentNode>(_arg);
        std::string left_member = translateRequireExpressionToString(exp->get_left_hand_operand());
        std::string right_member = translateRequireExpressionToString(exp->get_right_hand_operand());

        if(current_subnet->get_place_tempdata_by_name(left_member) != nullptr){
            left_member = current_subnet->get_place_tempdata_by_name(left_member)->get_name()+"_pr";
        }

        if(current_subnet->get_place_tempdata_by_name(right_member) != nullptr){
            right_member = current_subnet->get_place_tempdata_by_name(right_member)->get_name()+"_pr";
        }

        std::vector<std::string> target = Utils::split(left_member,".");
        if(target.size() > 2){
            ret = target[0]+".state :: (";
            for(int i = 2; i < target.size(); i++){
                ret += target[i];
            }
            ret += " := " + right_member + ")";
        }else{
            //error
        }
    }else if(_arg->get_node_type() == NodeTypeBinaryOperation){
        BinaryOperationNodePtr exp = std::static_pointer_cast<BinaryOperationNode>(_arg);
        std::string left_member = translateRequireExpressionToString(exp->get_left_hand_operand());
        std::string right_member = translateRequireExpressionToString(exp->get_right_hand_operand());

        if(current_subnet->get_place_tempdata_by_name(left_member) != nullptr){
            left_member = current_subnet->get_place_tempdata_by_name(left_member)->get_name()+"_pr";
        }

        if(current_subnet->get_place_tempdata_by_name(right_member) != nullptr){
            right_member = current_subnet->get_place_tempdata_by_name(right_member)->get_name()+"_pr";
        }

        ret = "(" + left_member + ") " + translateOperator(exp->get_operator()) + " (" + right_member + ")";
    }else if(_arg->get_node_type() == NodeTypeMemberAccess){
        MemberAccessNodePtr member = std::static_pointer_cast<MemberAccessNode>(_arg);
        ret = translateRequireExpressionToString(member->get_identifier());
        if(current_subnet->get_place_tempdata_by_name(ret) != nullptr){
            ret = current_subnet->get_place_tempdata_by_name(ret)->get_name()+"_pr";
        }

        ret += translateMemberAcess(member->get_member());
    }else if(_arg->get_node_type() == NodeTypeIdentifier){
        std::string operand;
        operand = std::static_pointer_cast<IdentifierNode>(_arg)->get_name();

        if(Utils::isInteger(operand)){
            ret = operand;
        }else if(operand == "msg"){
            if(current_subnet->get_in_place_by_domain(current_subnet->get_name()+"_par") != nullptr){
                ret = current_subnet->get_in_place_by_domain(current_subnet->get_name()+"_par")->get_name()+"_pr";
            }else if(current_subnet->get_in_place_by_domain(current_subnet->get_name()+"_state") != nullptr){
                ret = current_subnet->get_in_place_by_domain(current_subnet->get_name()+"_state")->get_name()+"_pr.par";
            }
        }else if(net->get_state_color_by_name(operand) != nullptr){
            if(current_subnet->get_in_place_by_domain("STATE") != nullptr){
                ret = current_subnet->get_in_place_by_domain("STATE")->get_name()+"_pr."+operand;
            }else if(current_subnet->get_in_place_by_domain(current_subnet->get_name()+"_state") != nullptr){
                ret = current_subnet->get_in_place_by_domain(current_subnet->get_name()+"_state")->get_name()+"_pr.state."+operand;
            }
        }else if(current_subnet->get_place_tempdata_by_name(operand) != nullptr){
            current_subnet->add_in_place(current_subnet->get_place_tempdata_by_name(operand));
            ret = operand;
        }else if(net->get_func_color_by_name(current_subnet->get_name()+"_par") != nullptr){
            StructColorNodePtr par = std::static_pointer_cast<StructColorNode>(net->get_func_color_by_name(current_subnet->get_name()+"_par"));
            if(par->get_component_by_name(operand) != nullptr){
                if(current_subnet->get_in_place_by_domain(current_subnet->get_name()+"_par") != nullptr){
                    ret = current_subnet->get_in_place_by_domain(current_subnet->get_name()+"_par")->get_name()+"_pr."+operand;
                }else if(current_subnet->get_in_place_by_domain(current_subnet->get_name()+"_state") != nullptr){
                    ret = current_subnet->get_in_place_by_domain(current_subnet->get_name()+"_state")->get_name()+"_pr."+current_subnet->get_name()+"_par."+operand;
                }
            }
        }
    }else if(_arg->get_node_type() == NodeTypeIndexAccess){
        IndexAccessNodePtr index = std::static_pointer_cast<IndexAccessNode>(_arg);
        std::string identifier = translateRequireExpressionToString(index->get_identifier());
        std::string index_value =  translateRequireExpressionToString(index->get_index_value());
        if(Utils::isInteger(index_value)){
            ret = identifier+"["+index_value+"]";
        } else if(current_subnet->get_place_tempdata_by_name(index_value) != nullptr){
            ret = identifier+"["+current_subnet->get_place_tempdata_by_name(index_value)->get_name()+"_pr]";
        }else{
            std::string func_name;
            std::string func_param;
            std::vector<std::string> target = Utils::split(identifier,".");

            if(net->get_state_color_by_name(target[target.size()-1]) != nullptr){
                std::string type = net->get_state_color_by_name(target[target.size()-1])->get_name();
                func_name = "get"+type+"Index";
                func_param = type;
            }
            ParamNodePtr param1 = std::make_shared<ParamNode>();
            ParamNodePtr param2 = std::make_shared<ParamNode>();
            param1->set_name(func_param+"_par");
            param1->set_type(func_param);
            param2->set_name("a");
            param2->set_type("address");

            net->add_function(createGetMappingIndexFunction(func_name,std::vector<ParamNodePtr>{param1,param2}));
            ret = identifier+"["+func_name+"("+identifier+","+index_value+")]";
        }
    }else if(_arg->get_node_type() == NodeTypeLiteral){
        ret = std::static_pointer_cast<LiteralNode>(_arg)->get_literal();
    }

    return ret;
}

FunctionNodePtr Translator::createGetMappingIndexFunction(std::string name, std::vector<ParamNodePtr> params){
    FunctionNodePtr func = std::make_shared<FunctionNode>();
    func->set_name(name);

    for(auto param = params.begin(); param != params.end(); param++){
        func->add_parameter(*param);
    }
    
    std::string body;
    body = body + "\n\tint i := 0;" +
                  "\n\twhile (i<"+func->get_parameter(0)->get_name()+"'size and "+func->get_parameter(0)->get_name()+"[i].key!=a) i := i+1;"+
                  "\n\tif(i<"+func->get_parameter(0)->get_name()+"'size)"+
                  "\n\t\treturn i;"+
                  "\n\telse"+
                  "\n\t\treturn -1;";
    func->set_body(body);

    func->set_returnType("int");
   return func;
}

void Translator::translateRequireFunctionCall(ASTNodePtr _arg){
    std::string require_exp = translateRequireExpressionToString(_arg);
    std::vector<PlaceNodePtr> out_places;

    TransitionNodePtr revert = std::make_shared<TransitionNode>();
    revert->set_name(current_subnet->get_name()+"_revert"+std::to_string(current_subnet->count));
    revert->set_guard("not("+require_exp+");");

    TransitionNodePtr not_revert = std::make_shared<TransitionNode>();
    not_revert->set_name(current_subnet->get_name()+"_n_revert"+std::to_string(current_subnet->count));
    not_revert->set_guard(require_exp+";");

    PlaceNodePtr cflow = std::make_shared<PlaceNode>();
    cflow->set_name(current_subnet->get_name()+"_nr"+std::to_string(current_subnet->count));
    cflow->set_domain(current_subnet->get_name()+"_state");
    cflow->set_place_type(PlaceTypeControlFlow);
    net->add_place(cflow);
    out_places.push_back(cflow);

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");
        revert->add_inArc(arc);
        not_revert->add_inArc(arc);
        if(param->get_name() == "state"){
            revert->add_outArc(arc);
            ArcNodePtr narc = std::make_shared<ArcNode>();
            narc->set_placeName(cflow->get_name());
            narc->set_label("<({"+param->get_name()+"_pr,"+current_subnet->get_name()+"_parameter_pr})>");
            not_revert->add_outArc(narc);
        }else if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr narc = std::make_shared<ArcNode>();
            narc->set_placeName("state");
            narc->set_label("<("+param->get_name()+"_pr.state)>");
            revert->add_outArc(narc);  

            ArcNodePtr noarc = std::make_shared<ArcNode>();
            noarc->set_placeName(cflow->get_name());
            noarc->set_label("<("+param->get_name()+")>");
            not_revert->add_outArc(noarc);         
        }else if(param->get_place_type() == PlaceTypeData){
            revert->add_outArc(arc);
            not_revert->add_outArc(arc);
            out_places.push_back(param);
        }
    }

    net->add_transition(revert);
    net->add_transition(not_revert);
    current_subnet->set_in_places(out_places);
}

void Translator::translateVariableDeclaration(ASTNodePtr _var){
    if(_var->get_node_type() == NodeTypeVariableDeclaration){
        auto varNode = std::static_pointer_cast<VariableDeclarationNode>(_var);

        if (varNode->get_type()->get_node_type() == NodeTypeMapping) {
            ListColorNodePtr mapping_type = translateMapping(_var);
            net->add_color(mapping_type);

        }else if(varNode->get_type()->get_node_type() == NodeTypeElementaryTypeName){
            std::string name = std::static_pointer_cast<ElementaryTypeNameNode>(varNode->get_type())->get_type_name();
            ColorNodePtr new_type = std::make_shared<ColorNode>();  
            new_type->set_name(name);
            new_type->set_typeDef(DataTypeRange[name]);
            net->add_color(new_type);

            if(!is_in_function){
                net->add_state_color(new_type,varNode->get_variable_name());
            }else{
                PlaceNodePtr new_place = std::make_shared<PlaceNode>();
                new_place->set_domain(name);
                new_place->set_name(current_subnet->get_name()+"_"+varNode->get_variable_name()+std::to_string(current_subnet->count));
                new_place->set_place_type(PlaceTypeWaitData);
                net->add_place(new_place);

                current_subnet->add_tempdata_place(new_place,varNode->get_variable_name());
                current_subnet->add_in_place(new_place);
            }
        }else if(varNode->get_type()->get_node_type() == NodeTypeArrayTypeName){
            auto arrayNode = std::static_pointer_cast<ArrayTypeNameNode>(varNode->get_type());
            ListColorNodePtr array_type = translateArray(arrayNode);
            net->add_color(array_type);
        }else if(varNode->get_type()->get_node_type() == NodeTypeUserDefinedTypeName){
            UserDefinedTypeNameNodePtr type = std::static_pointer_cast<UserDefinedTypeNameNode>(varNode->get_type());
            if(!is_in_function){
                net->add_state_color(net->get_color_by_name(type->get_type_name()),varNode->get_variable_name());
            }else{
                PlaceNodePtr new_place = std::make_shared<PlaceNode>();
                new_place->set_domain(type->get_type_name());
                new_place->set_name(current_subnet->get_name()+"_"+varNode->get_variable_name()+std::to_string(current_subnet->count));
                new_place->set_place_type(PlaceTypeWaitData);
                net->add_place(new_place);

                current_subnet->add_tempdata_place(new_place,varNode->get_variable_name());
                current_subnet->add_in_place(new_place);
            }
        }

    }else if(_var->get_node_type() == NodeTypeElementaryTypeName){
        std::string name = std::static_pointer_cast<ElementaryTypeNameNode>(_var)->get_type_name();
        ColorNodePtr new_type = std::make_shared<ColorNode>();  
        new_type->set_name(name);
        new_type->set_typeDef(DataTypeRange[name]);
        net->add_color(new_type);

    }else if(_var->get_node_type() == NodeTypeArrayTypeName){
        auto arrayNode = std::static_pointer_cast<ArrayTypeNameNode>(_var);
        ListColorNodePtr array_type = translateArray(arrayNode);
        net->add_color(array_type);
    }
}


PlaceNodePtr Translator::createParFuncPlace(std::string func_name){
    PlaceNodePtr func_place = std::make_shared<PlaceNode>();
    func_place->set_name((func_name+"_parameter"));
    func_place->set_domain(func_name+"_par");
    /* func_place->set_init("<(0,0,"+")>"); */

    return func_place;
}

void Translator::translateForStatement(ForStatementNodePtr forStatement){
    //init transition
    TransitionNodePtr forloopInt = std::make_shared<TransitionNode>();
    forloopInt->set_name(current_subnet->get_name()+"_initforloop_"+std::to_string(current_subnet->count));
    
    std::vector<PlaceNodePtr> out_places;

    PlaceNodePtr initPlace = std::make_shared<PlaceNode>();
    initPlace->set_name(current_subnet->get_name()+"_init_"+std::to_string(current_subnet->count));
    initPlace->set_domain(current_subnet->get_name()+"_state");
    initPlace->set_place_type(PlaceTypeControlFlow);
    net->add_place(initPlace);
    out_places.push_back(initPlace);

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");
        forloopInt->add_inArc(arc);
        if(param->get_name() == "state"){
            ArcNodePtr narc = std::make_shared<ArcNode>();
            narc->set_placeName(initPlace->get_name());
            narc->set_label("<({"+param->get_name()+"_pr,"+current_subnet->get_name()+"_parameter_pr})>");
            forloopInt->add_outArc(narc);
        }else if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr noarc = std::make_shared<ArcNode>();
            noarc->set_placeName(initPlace->get_name());
            noarc->set_label("<("+param->get_name()+"_pr)>");
            forloopInt->add_outArc(noarc);         
        }else if(param->get_place_type() == PlaceTypeData){
            forloopInt->add_outArc(arc);
            out_places.push_back(param);
        }else if(param->get_place_type() == PlaceTypeTempData){
            forloopInt->add_outArc(arc);
        }
    }

    //init value
    PlaceNodePtr initValuePlace = std::make_shared<PlaceNode>();
    std::string init_value;
    std::string init_name;
    if(forStatement->get_init()->get_node_type() == NodeTypeVariableDeclarationStatement){
        VariableDeclarationStatementNodePtr init_statement = std::static_pointer_cast<VariableDeclarationStatementNode>(forStatement->get_init());
        init_name = init_statement->get_decl()->get_variable_name();
        if(init_statement->get_value()->get_node_type() == NodeTypeLiteral){
            LiteralNodePtr value = std::static_pointer_cast<LiteralNode>(init_statement->get_value());
            init_value = value->get_literal();
        }

        initValuePlace->set_name(current_subnet->get_name()+"_"+init_name+"_"+std::to_string(current_subnet->count));
        initValuePlace->set_domain("int");
        initValuePlace->set_place_type(PlaceTypeTempData);
        net->add_place(initValuePlace);

        ArcNodePtr valueParamInt = std::make_shared<ArcNode>();
        valueParamInt->set_placeName(initValuePlace->get_name());
        valueParamInt->set_label("<("+init_value+")>");
        forloopInt->add_outArc(valueParamInt);
    }
    net->add_transition(forloopInt);
    current_subnet->set_in_places(out_places);
    current_subnet->add_tempdata_place(initValuePlace,init_name);

    //condition transition
    TransitionNodePtr forloopCondRevert = std::make_shared<TransitionNode>();
    forloopCondRevert->set_name(current_subnet->get_name()+"_condforloop_n_"+std::to_string(current_subnet->count));

    TransitionNodePtr forloopCond = std::make_shared<TransitionNode>();
    forloopCond->set_name(current_subnet->get_name()+"_condforloop_"+std::to_string(current_subnet->count));

    std::vector<PlaceNodePtr> out_places_cond;
    std::string exp = translateRequireExpressionToString(forStatement->get_condition());
    
    forloopCond->set_guard(exp+";");
    forloopCondRevert->set_guard("not ("+exp+");");

    PlaceNodePtr condPlace = std::make_shared<PlaceNode>();
    condPlace->set_name(current_subnet->get_name()+"_cond_"+std::to_string(current_subnet->count));
    condPlace->set_domain(current_subnet->get_name()+"_state");
    condPlace->set_place_type(PlaceTypeControlFlow);
    net->add_place(condPlace);
    out_places_cond.push_back(condPlace);

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");
        forloopCond->add_inArc(arc);
        forloopCondRevert->add_inArc(arc);
        if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr narc = std::make_shared<ArcNode>();
            narc->set_placeName("state");
            narc->set_label("<("+param->get_name()+"_pr.state)>");
            forloopCondRevert->add_outArc(narc);

            ArcNodePtr noarc = std::make_shared<ArcNode>();
            noarc->set_placeName(condPlace->get_name());
            noarc->set_label("<("+param->get_name()+"_pr)>");
            forloopCond->add_outArc(noarc);         
        }else if(param->get_place_type() == PlaceTypeData){
            forloopCond->add_outArc(arc);
            forloopCondRevert->add_outArc(arc);
            out_places_cond.push_back(param);
        }else if(param->get_place_type() == PlaceTypeTempData){
            forloopCond->add_outArc(arc);
            forloopCondRevert->add_outArc(arc);
        }
    }

    net->add_transition(forloopCond);
    net->add_transition(forloopCondRevert);
    current_subnet->set_in_places(out_places_cond);

    current_subnet->remove_tempdata_place_bye_name(init_value);

    if(forStatement->get_body()->get_node_type() == NodeTypeBlockNode){
        translateBlock(std::static_pointer_cast<BlockNode>(forStatement->get_body()));
    }else if(forStatement->get_body()->get_node_type() == NodeTypeExpressionStatement){
        translateExpressionStatement(std::static_pointer_cast<ExpressionStatementNode>(forStatement->get_body()));
    }


}


void Translator::generatePredefinedColors() {
    ColorNodePtr address = std::make_shared<ColorNode>();
    address->set_name("address");
    address->set_typeDef(DataTypeRange["address"]);
    net->add_color(address);

    ColorNodePtr eth = std::make_shared<ColorNode>();
    eth->set_name("uint");
    eth->set_typeDef(DataTypeRange["uint"]);
    net->add_color(eth);

    ColorNodePtr user = std::make_shared<ColorNode>();
    user->set_name("USER");
    user->set_typeDef("struct { address adr;uint balance;}");
    net->add_color(user);

    net->add_state_color(eth,"contractBalance");
}


StructColorNodePtr Translator::translateStruct(StructDefinitionNodePtr struct_node) {
    StructColorNodePtr struct_color = std::make_shared<StructColorNode>();
    struct_color->set_name(struct_node->get_name());
            
    for (int i = 0; i < struct_node->num_fields(); i++) {
        translateVariableDeclaration(struct_node->get_field(i));

        VariableDeclarationNodePtr variable = std::static_pointer_cast<VariableDeclarationNode>(struct_node->get_field(i));
        ComponentNodePtr component = std::make_shared<ComponentNode>();
        component->set_name(variable->get_variable_name());

        //if type in struct does'not exist then return error
        component->set_type(std::static_pointer_cast<ElementaryTypeNameNode>(variable->get_type())->get_type_name());//can change to function get varinfor
        struct_color->add_component(component);
    }
    return struct_color;
}

ListColorNodePtr Translator::translateMapping(ASTNodePtr _node) {
    ListColorNodePtr list_color = std::make_shared<ListColorNode>();
    StructColorNodePtr struct_color = std::make_shared<StructColorNode>();
    auto var_node = std::static_pointer_cast<VariableDeclarationNode>(_node);
    auto mapNode = std::static_pointer_cast<MappingNode>(var_node->get_type());
    struct_color->set_name("struct_" + var_node->get_variable_name());
    ComponentNodePtr key = std::make_shared<ComponentNode>();
    key->set_name("key");
    if (mapNode->get_key_type()->get_node_type() == NodeTypeElementaryTypeName) {
        auto key_type = std::static_pointer_cast<ElementaryTypeNameNode>(mapNode->get_key_type());
        key->set_type(key_type->get_type_name());
    }
    else {
        auto key_type = std::static_pointer_cast<UserDefinedTypeNameNode>(mapNode->get_key_type());
        key->set_type(key_type->get_type_name());
    }
    translateVariableDeclaration(mapNode->get_key_type());
    ComponentNodePtr value = std::make_shared<ComponentNode>();

    value->set_name("value");
    if (mapNode->get_value_type()->get_node_type() == NodeTypeElementaryTypeName) {
        auto value_type = std::static_pointer_cast<ElementaryTypeNameNode>(mapNode->get_value_type());
        value->set_type(value_type->get_type_name());
    }
    else if (mapNode->get_value_type()->get_node_type() == NodeTypeArrayTypeName) {
        auto value_type = std::static_pointer_cast<ArrayTypeNameNode>(mapNode->get_value_type());
        ListColorNodePtr array_type = translateArray(value_type);
        net->add_color(array_type);
        value->set_type(array_type->get_name());
    }
    translateVariableDeclaration(mapNode->get_value_type());

    struct_color->add_component(key);
    struct_color->add_component(value);
    net->add_color(struct_color);
    
    list_color->set_name("list_"+ var_node->get_variable_name());
    list_color->set_index_type("nat");
    list_color->set_element_type(struct_color->get_name());
    list_color->set_capacity("100");

    if(!is_in_function){
        net->add_state_color(list_color,var_node->get_variable_name());
    }
    return list_color;
}

ListColorNodePtr Translator::translateArray(ArrayTypeNameNodePtr array_node){
    translateVariableDeclaration(array_node->get_base_type());
    auto base_type = std::static_pointer_cast<UserDefinedTypeNameNode>(array_node->get_base_type());
    ListColorNodePtr list_color = std::make_shared<ListColorNode>();
    list_color->set_name("list_"+ base_type->get_type_name());
    list_color->set_index_type("nat");
    list_color->set_element_type(base_type->get_type_name());
    list_color->set_capacity("100");
    return list_color;
}

void Translator::generateFunctionColor(FunctionDefinitionNodePtr func){
    StructColorNodePtr funcParColor = std::make_shared<StructColorNode>();
    funcParColor->set_name(func->get_name()+"_par");

    ComponentNodePtr spcomponent = std::make_shared<ComponentNode>();
    spcomponent->set_name("sender");
    spcomponent->set_type("USER");
    funcParColor->add_component(spcomponent);

    ComponentNodePtr vpcomponent = std::make_shared<ComponentNode>();
    vpcomponent->set_name("value");
    vpcomponent->set_type("uint");
    funcParColor->add_component(vpcomponent);

    ParameterListNodePtr func_params = func->get_params();
    for(int i = 0; i < func_params->num_parameters(); i++){
        auto param = func_params->get_parameter(i);
        if(param->get_node_type() == NodeTypeVariableDeclaration){
            auto varParam = std::static_pointer_cast<VariableDeclarationNode>(param);
            if(varParam->get_type()->get_node_type() == NodeTypeElementaryTypeName){
                std::string type_name = std::static_pointer_cast<ElementaryTypeNameNode>(varParam->get_type())->get_type_name();
                if(net->get_state_color_by_name(type_name) != nullptr){
                    ComponentNodePtr component = std::make_shared<ComponentNode>();
                    component->set_name(varParam->get_variable_name());
                    component->set_type(type_name);
                    funcParColor->add_component(component);
                }else{
                        //error!!! type name does not exist
                }
            }else if(varParam->get_type()->get_node_type() == NodeTypeArrayTypeName){
                auto arrayNode = std::static_pointer_cast<ArrayTypeNameNode>(varParam->get_type());
                ListColorNodePtr array_type = translateArray(arrayNode);
                net->add_color(array_type);

                ComponentNodePtr component = std::make_shared<ComponentNode>();
                component->set_name(varParam->get_variable_name());
                component->set_type(array_type->get_name());
                funcParColor->add_component(component);
            }
        }
    }
    net->add_func_color(funcParColor);

    StructColorNodePtr funcReturnColor = std::make_shared<StructColorNode>();
    funcReturnColor->set_name(func->get_name()+"_return");

    ComponentNodePtr srcomponent = std::make_shared<ComponentNode>();
    srcomponent->set_name("sender");
    srcomponent->set_type("USER");
    funcReturnColor->add_component(srcomponent);

    ParameterListNodePtr func_return = func->get_returns();
    for(int i = 0; i < func_return->num_parameters(); i++){
        auto param = func_return->get_parameter(i);
        if(param->get_node_type() == NodeTypeVariableDeclaration){
            auto varReturn = std::static_pointer_cast<VariableDeclarationNode>(param);
            if(varReturn->get_type()->get_node_type() == NodeTypeElementaryTypeName){
                std::string type_name = std::static_pointer_cast<ElementaryTypeNameNode>(varReturn->get_type())->get_type_name();
                if(net->get_state_color_by_name(type_name) != nullptr){
                    ComponentNodePtr component = std::make_shared<ComponentNode>();
                    component->set_name(varReturn->get_variable_name());
                    component->set_type(type_name);
                    funcReturnColor->add_component(component);
                }else{
                        //error!!! type name does not exist
                }
            }else if(varReturn->get_type()->get_node_type() == NodeTypeArrayTypeName){
                auto arrayNode = std::static_pointer_cast<ArrayTypeNameNode>(varReturn->get_type());
                ListColorNodePtr array_type = translateArray(arrayNode);
                net->add_color(array_type);

                ComponentNodePtr component = std::make_shared<ComponentNode>();
                component->set_name(varReturn->get_variable_name());
                component->set_type(array_type->get_name());
                funcReturnColor->add_component(component);
            }
        }
    }
    net->add_func_color(funcReturnColor);

    StructColorNodePtr funcStateColor = std::make_shared<StructColorNode>();
    funcStateColor->set_name(func->get_name()+"_state");

    ComponentNodePtr sscomponent = std::make_shared<ComponentNode>();
    sscomponent->set_name("state");
    sscomponent->set_type("STATE");
    funcStateColor->add_component(sscomponent);

    ComponentNodePtr pscomponent = std::make_shared<ComponentNode>();
    pscomponent->set_name("par");
    pscomponent->set_type(func->get_name()+"_par");
    funcStateColor->add_component(pscomponent);
    net->add_func_color(funcStateColor);
}

}
