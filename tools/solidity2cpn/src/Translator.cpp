#include "../include/Translator.hpp"
#include "../include/Utils.hpp"

namespace SOL2CPN {
    
bool Translator::isNormalSign(std::string sign){
    if(NormalSign.find(sign) != NormalSign.end()){
        return true;
    }
    return false;
}

bool Translator::isSpecialSign(std::string sign){
    if (std::find(SpecialSign.begin(), SpecialSign.end(), sign) != SpecialSign.end())
    {
        return true;
    }
    return false;
}

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
                        createParFuncPlace(func);

                        SubNetNodePtr func_subnet = std::make_shared<SubNetNode>();
                        func_subnet->set_name(func->get_name());
                        current_subnet = func_subnet;

                        createInTransition(func);
                        
                        BlockNodePtr func_body = func->get_function_body();
                        translateBlock(func_body);
                        
                        TransitionNodePtr end_func = std::make_shared<TransitionNode>();
                        end_func->set_name(func->get_name()+"_endfunc");

                        for(int i = 0; i < current_subnet->num_in_places(); i++){
                            PlaceNodePtr param = current_subnet->get_in_places(i);
                            ArcNodePtr arc = std::make_shared<ArcNode>();
                            arc->set_placeName(param->get_name());
                            arc->set_label("<("+param->get_name()+"_pr)>");
                            end_func->add_inArc(arc);
                            
                            if(param->get_place_type() == PlaceTypeControlFlow){
                                ArcNodePtr noarc = std::make_shared<ArcNode>();
                                noarc->set_placeName("state");
                                noarc->set_label("<("+param->get_name()+"_pr.state)>");
                                end_func->add_outArc(noarc);

                                ArcNodePtr poarc = std::make_shared<ArcNode>();
                                poarc->set_placeName(func->get_name()+"_parameter");
                                poarc->set_label("<("+param->get_name()+"_pr.par)>");
                                end_func->add_outArc(poarc);
                            }
                        }
                        net->add_transition(end_func);
                        is_in_function = false;
                    }
                }
            }

    return net;
}

void Translator::createParFuncPlace(FunctionDefinitionNodePtr func){
    PlaceNodePtr func_place = std::make_shared<PlaceNode>();
    func_place->set_name(func->get_name()+"_parameter");
    func_place->set_domain(func->get_name()+"_par");
    /* func_place->set_init("<(0,0,"+")>"); */
    net->add_place(func_place);
}

void Translator::createInTransition(FunctionDefinitionNodePtr func){
    PlaceNodePtr cflow = std::make_shared<PlaceNode>();
    cflow->set_name(func->get_name()+"_enter");
    cflow->set_domain(func->get_name()+"_state");
    cflow->set_place_type(PlaceTypeControlFlow);
    net->add_place(cflow);

    TransitionNodePtr func_trans = std::make_shared<TransitionNode>();
    func_trans->set_name(func->get_name());
                        
    ArcNodePtr state_arc = std::make_shared<ArcNode>();
    state_arc->set_placeName("state");
    state_arc->set_label("<(state_pr)>");

    ArcNodePtr par_arc = std::make_shared<ArcNode>();
    par_arc->set_placeName(func->get_name()+"_parameter");
    par_arc->set_label("<("+func->get_name()+"_pr"+")>");

    ArcNodePtr cflow_arc = std::make_shared<ArcNode>();
    cflow_arc->set_placeName(cflow->get_name());
    cflow_arc->set_label("<({state_pr,"+func->get_name()+"_pr"+"})>");

    func_trans->add_inArc(state_arc);
    func_trans->add_inArc(par_arc);
    func_trans->add_outArc(cflow_arc);

    net->add_transition(func_trans);
    current_subnet->set_in_places(std::vector<PlaceNodePtr>{cflow});
}

void Translator::translateBlock(BlockNodePtr block){
    for(int i = 0; i < block->num_statements(); i++){
        current_subnet->count++;
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
    }
}

void Translator::translateIfStatement(IfStatementNodePtr statement){
    std::vector<PlaceNodePtr> init_out_places;
    
    std::string exp = translateRequireExpressionToString(statement->get_condition());

    TransitionNodePtr ifstate = std::make_shared<TransitionNode>();
    ifstate->set_name(current_subnet->get_name()+"_ifstate"+std::to_string(current_subnet->count));
    ifstate->set_guard(exp+";");

    std::vector<PlaceNodePtr> out_places;
    PlaceNodePtr cflow = std::make_shared<PlaceNode>();
    cflow->set_name(current_subnet->get_name()+"_is"+std::to_string(current_subnet->count));
    cflow->set_domain(current_subnet->get_name()+"_state");
    cflow->set_place_type(PlaceTypeControlFlow);
    net->add_place(cflow);
    out_places.push_back(cflow);

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        init_out_places.push_back(param);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");
        ifstate->add_inArc(arc);
        
        if(param->get_place_type() == PlaceTypeControlFlow){
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

    if(statement->get_then() != nullptr){
        if(statement->get_then()->get_node_type() == NodeTypeBlockNode){
            translateBlock(std::static_pointer_cast<BlockNode>(statement->get_then()));
        }else if(statement->get_then()->get_node_type() == NodeTypeExpressionStatement){
            current_subnet->count++;
            translateExpressionStatement(std::static_pointer_cast<ExpressionStatementNode>(statement->get_then()));
        }
    }

    std::vector<PlaceNodePtr> final_out_places;
    PlaceNodePtr cflow_end = std::make_shared<PlaceNode>();
    cflow_end->set_name(current_subnet->get_name()+"_eif"+std::to_string(current_subnet->count));
    cflow_end->set_domain(current_subnet->get_name()+"_state");
    cflow_end->set_place_type(PlaceTypeControlFlow);
    net->add_place(cflow_end);
    final_out_places.push_back(cflow_end);

    TransitionNodePtr end_if = std::make_shared<TransitionNode>();
    end_if->set_name(current_subnet->get_name()+"_endif"+std::to_string(current_subnet->count));

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");
        end_if->add_inArc(arc);

        if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr noarc = std::make_shared<ArcNode>();
            noarc->set_placeName(cflow_end->get_name());
            noarc->set_label("<("+param->get_name()+"_pr)>");
            end_if->add_outArc(noarc);

        }if(param->get_place_type() == PlaceTypeTempData){
            end_if->add_outArc(arc);
        }
    }
    net->add_transition(end_if);
    

    if(statement->get_else() != nullptr){
        if(statement->get_else()->get_node_type() != NodeTypeIfStatement){
            std::vector<PlaceNodePtr> else_out_places;
            PlaceNodePtr cflow_else = std::make_shared<PlaceNode>();
            cflow_else->set_name(current_subnet->get_name()+"_else"+std::to_string(current_subnet->count));
            cflow_else->set_domain(current_subnet->get_name()+"_state");
            cflow_else->set_place_type(PlaceTypeControlFlow);
            net->add_place(cflow_else);
            else_out_places.push_back(cflow_else);

            TransitionNodePtr else_trans = std::make_shared<TransitionNode>();
            else_trans->set_name(current_subnet->get_name()+"_else"+std::to_string(current_subnet->count));
            else_trans->set_guard("not ("+exp+");");

            for(int i = 0; i < init_out_places.size(); i++){
                PlaceNodePtr param = init_out_places[i];
                ArcNodePtr arc = std::make_shared<ArcNode>();
                arc->set_placeName(param->get_name());
                arc->set_label("<("+param->get_name()+"_pr)>");
                else_trans->add_inArc(arc);

                if(param->get_place_type() == PlaceTypeControlFlow){
                    ArcNodePtr noarc = std::make_shared<ArcNode>();
                    noarc->set_placeName(cflow_else->get_name());
                    noarc->set_label("<("+param->get_name()+"_pr)>");
                    else_trans->add_outArc(noarc);

                }if(param->get_place_type() == PlaceTypeTempData){
                    else_trans->add_outArc(arc);
                }
            }
            net->add_transition(else_trans);
            current_subnet->set_in_places(else_out_places);

            if(statement->get_else()->get_node_type() == NodeTypeExpressionStatement){
                current_subnet->count++;
                translateExpressionStatement(std::static_pointer_cast<ExpressionStatementNode>(statement->get_else()));
            }
            
            TransitionNodePtr end_if_else = std::make_shared<TransitionNode>();
            end_if_else->set_name(current_subnet->get_name()+"_endifelse"+std::to_string(current_subnet->count));

            for(int i = 0; i < current_subnet->num_in_places(); i++){
                PlaceNodePtr param = current_subnet->get_in_places(i);
                ArcNodePtr arc = std::make_shared<ArcNode>();
                arc->set_placeName(param->get_name());
                arc->set_label("<("+param->get_name()+"_pr)>");
                end_if_else->add_inArc(arc);

                if(param->get_place_type() == PlaceTypeControlFlow){
                    ArcNodePtr noarc = std::make_shared<ArcNode>();
                    noarc->set_placeName(cflow_end->get_name());
                    noarc->set_label("<("+param->get_name()+"_pr)>");
                    end_if_else->add_outArc(noarc);

                }if(param->get_place_type() == PlaceTypeTempData){
                    end_if_else->add_outArc(arc);
                }
            }
            net->add_transition(end_if_else);
            current_subnet->set_in_places(final_out_places);
        }
    }else{
        TransitionNodePtr not_if = std::make_shared<TransitionNode>();
        not_if->set_name(current_subnet->get_name()+"_n_ifstate"+std::to_string(current_subnet->count));
        not_if->set_guard("not ("+exp+");");

        for(int i = 0; i < init_out_places.size(); i++){
            PlaceNodePtr param = init_out_places[i];
            ArcNodePtr arc = std::make_shared<ArcNode>();
            arc->set_placeName(param->get_name());
            arc->set_label("<("+param->get_name()+"_pr)>");
            not_if->add_inArc(arc);

            if(param->get_place_type() == PlaceTypeControlFlow){
                ArcNodePtr noarc = std::make_shared<ArcNode>();
                noarc->set_placeName(cflow_end->get_name());
                noarc->set_label("<("+param->get_name()+"_pr)>");
                not_if->add_outArc(noarc);

            }if(param->get_place_type() == PlaceTypeTempData){
                not_if->add_outArc(arc);
            }
        }
        net->add_transition(not_if);
        current_subnet->set_in_places(final_out_places);
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

        if(param->get_place_type() == PlaceTypeControlFlow){
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
    translate_equivalent_node(statement->get_expression());
}

void Translator::translate_equivalent_node(ASTNodePtr _node){
    if (_node->get_node_type() == NodeTypeFunctionCall) {
        translateFunctionCall(std::static_pointer_cast<FunctionCallNode>(_node));
    }else if(_node->get_node_type() == NodeTypeVariableDeclarationStatement){
        translateVariableDeclarationStatement(std::static_pointer_cast<VariableDeclarationStatementNode>(_node));
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

    std::string left_member = translateRequireExpressionToString(assignment->get_left_hand_operand());
    std::string right_member = translateRequireExpressionToString(assignment->get_right_hand_operand());

    if(current_subnet->get_place_tempdata_by_name(left_member) != nullptr){
        left_member = current_subnet->get_place_tempdata_by_name(left_member)->get_name()+"_pr";
    }
    if(current_subnet->get_place_tempdata_by_name(right_member) != nullptr){
        right_member = current_subnet->get_place_tempdata_by_name(right_member)->get_name()+"_pr";
    }

    std::vector<std::string> temp = Utils::split(left_member,"_pr");
    PlaceNodePtr left_place = net->get_place_by_name(temp[0]);

    FunctionNodePtr cvalue = std::make_shared<FunctionNode>();
    cvalue->set_name("change_"+temp[0]+"_value"+std::to_string(current_subnet->count));
    cvalue->set_returnType(left_place->get_domain());

    std::string out_arc_label = "<(" + cvalue->get_name() + "(";
    
    std::string fbody;
    fbody = "\t"+left_place->get_domain() + " " + left_place->get_name() + "_temp " + NormalSign[EqualSign] + " " + left_place->get_name() + "_pr;\n\t";
    std::string l_member;
    l_member = temp[0] + "_temp";
    for(int i = 1; i < temp.size()-1; i++){
        l_member += temp[i] + "_pr";
    }
    l_member += temp[temp.size()-1];
    fbody += l_member + " " +translateOperator(assignment->get_operator(),l_member) + " " + right_member + ";\n";
    fbody += "\treturn " + left_place->get_name() + "_temp;";
    
    cvalue->set_body(fbody);

    ArcNodePtr out_arc_c = std::make_shared<ArcNode>();

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr p = current_subnet->get_in_places(i);
        
        ArcNodePtr in_arc = std::make_shared<ArcNode>();
        in_arc->set_placeName(p->get_name());
        in_arc->set_label("<("+p->get_name()+"_pr)>");
        assign->add_inArc(in_arc);

        ParamNodePtr param = std::make_shared<ParamNode>();
        param->set_type(p->get_domain());
        param->set_name(p->get_name()+"_pr");
        cvalue->add_parameter(param);

        out_arc_label += p->get_name()+"_pr,";

        if(p->get_place_type() == PlaceTypeControlFlow){
            if(left_place->get_place_type() != PlaceTypeControlFlow){
                ArcNodePtr in_arc = std::make_shared<ArcNode>();
                in_arc->set_placeName(cflow->get_name());
                in_arc->set_label("<("+p->get_name()+"_pr)>");
                assign->add_outArc(in_arc);
            }else{
                out_arc_c->set_placeName(cflow->get_name());
            }
        }

        if(p->get_place_type() == PlaceTypeTempData){
            if(p->get_name() != left_place->get_name()){
                ArcNodePtr in_arc = std::make_shared<ArcNode>();
                in_arc->set_placeName(p->get_name());
                in_arc->set_label("<("+p->get_name()+"_pr)>");
                assign->add_outArc(in_arc);
            }else{
                out_arc_c->set_placeName(cflow->get_name());
            }
        }
    }
    out_arc_label = out_arc_label.substr(0, out_arc_label.size()-1) + "))>";
    out_arc_c->set_label(out_arc_label);
    assign->add_outArc(out_arc_c);

    net->add_function(cvalue);
    net->add_transition(assign);
    current_subnet->set_in_places(out_places);
}

void Translator::translateFunctionCall(FunctionCallNodePtr func_call){
    if(func_call->get_callee() != nullptr){
        if(func_call->get_callee()->get_node_type() == NodeTypeIdentifier){
            IdentifierNodePtr func_name_handler = std::static_pointer_cast<IdentifierNode>(func_call->get_callee());
            if(func_name_handler->get_name() == "require"){
                translateRequireFunctionCall(func_call->get_argument(0));
            }
        }else if(func_call->get_callee()->get_node_type() == NodeTypeMemberAccess){
            MemberAccessNodePtr member_access = std::static_pointer_cast<MemberAccessNode>(func_call->get_callee());
            std::string member = member_access->get_member();
            if(member == "transfer"){
                translateTransferFunctionCall(member_access->get_identifier(),func_call->get_argument(0));
            }else if(member == "push"){
                translatePushFunctionCall(member_access->get_identifier(),func_call->get_argument(0));
            }
            /* translateSpecificFunctionCall(member,member_access->get_identifier(),func_call); */
        }
    }   
}

void Translator::translateSpecificFunctionCall(std::string func_name,ASTNodePtr identifier, FunctionCallNodePtr func_call){}

void Translator::translatePushFunctionCall(ASTNodePtr identifier, ASTNodePtr argument){
    std::string arg = translateRequireExpressionToString(argument);
    std::string ident = translateRequireExpressionToString(identifier);
    
    if(current_subnet->get_place_tempdata_by_name(arg) != nullptr){
        arg = current_subnet->get_place_tempdata_by_name(arg)->get_name()+"_pr";
    }
    if(current_subnet->get_place_tempdata_by_name(ident) != nullptr){
        ident = current_subnet->get_place_tempdata_by_name(ident)->get_name()+"_pr";
    }

    TransitionNodePtr push_trans = std::make_shared<TransitionNode>();
    push_trans->set_name(current_subnet->get_name()+"_push"+std::to_string(current_subnet->count));

    std::vector<PlaceNodePtr> out_places;
    PlaceNodePtr cflow = std::make_shared<PlaceNode>();
    cflow->set_name(current_subnet->get_name()+"_pu"+std::to_string(current_subnet->count));
    cflow->set_domain(current_subnet->get_name()+"_state");
    cflow->set_place_type(PlaceTypeControlFlow);
    net->add_place(cflow);

    out_places.push_back(cflow);

    std::vector<std::string> temp = Utils::split(ident,"_pr");
    PlaceNodePtr ident_place = net->get_place_by_name(temp[0]);

    FunctionNodePtr cvalue = std::make_shared<FunctionNode>();
    cvalue->set_name("push_"+temp[0]+"_value"+std::to_string(current_subnet->count));
    cvalue->set_returnType(ident_place->get_domain());

    std::string out_arc_label = "<(" + cvalue->get_name() + "(";
    
    std::string fbody;
    fbody = "\t"+ident_place->get_domain() + " " + ident_place->get_name() + "_temp " + NormalSign[EqualSign] + " " + ident_place->get_name() + "_pr;\n\t";
    std::string l_member;
    l_member = temp[0] + "_temp";
    for(int i = 1; i < temp.size()-1; i++){
        l_member += temp[i] + "_pr";
    }
    l_member += temp[temp.size()-1];
    fbody += l_member + " := " + l_member + " & "  + arg + ";\n";
    fbody += "\treturn " + ident_place->get_name() + "_temp;";
    
    cvalue->set_body(fbody);

    ArcNodePtr out_arc_c = std::make_shared<ArcNode>();
    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr p = current_subnet->get_in_places(i);
        
        ArcNodePtr in_arc = std::make_shared<ArcNode>();
        in_arc->set_placeName(p->get_name());
        in_arc->set_label("<("+p->get_name()+"_pr)>");
        push_trans->add_inArc(in_arc);

        ParamNodePtr param = std::make_shared<ParamNode>();
        param->set_type(p->get_domain());
        param->set_name(p->get_name()+"_pr");
        cvalue->add_parameter(param);

        out_arc_label += p->get_name()+"_pr,";

        if(p->get_place_type() == PlaceTypeControlFlow){
            if(ident_place->get_place_type() != PlaceTypeControlFlow){
                ArcNodePtr in_arc = std::make_shared<ArcNode>();
                in_arc->set_placeName(cflow->get_name());
                in_arc->set_label("<("+p->get_name()+"_pr)>");
                push_trans->add_outArc(in_arc);
            }else{
                out_arc_c->set_placeName(cflow->get_name());
            }
        }

        if(p->get_place_type() == PlaceTypeTempData){
            if(p->get_name() != ident_place->get_name()){
                ArcNodePtr in_arc = std::make_shared<ArcNode>();
                in_arc->set_placeName(p->get_name());
                in_arc->set_label("<("+p->get_name()+"_pr)>");
                push_trans->add_outArc(in_arc);
            }else{
                out_arc_c->set_placeName(cflow->get_name());
            }
        }
    }

    out_arc_label = out_arc_label.substr(0, out_arc_label.size()-1) + "))>";
    out_arc_c->set_label(out_arc_label);
    push_trans->add_outArc(out_arc_c);

    net->add_function(cvalue);
    net->add_transition(push_trans);
    current_subnet->set_in_places(out_places);

}

void Translator::translateTransferFunctionCall(ASTNodePtr identifier, ASTNodePtr argument){
    std::string arg = translateRequireExpressionToString(argument);
    if(current_subnet->get_place_tempdata_by_name(arg) != nullptr){
        arg = current_subnet->get_place_tempdata_by_name(arg)->get_name()+"_pr";
    }
    
    std::vector<PlaceNodePtr> out_places;
    TransitionNodePtr func_trans = std::make_shared<TransitionNode>();
    func_trans->set_name(current_subnet->get_name()+"_funcall"+std::to_string(current_subnet->count));

    PlaceNodePtr cflow = std::make_shared<PlaceNode>();
    cflow->set_name(current_subnet->get_name()+"_fc"+std::to_string(current_subnet->count));
    cflow->set_domain(current_subnet->get_name()+"_state");
    cflow->set_place_type(PlaceTypeControlFlow);
    net->add_place(cflow);
    out_places.push_back(cflow);

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");
        func_trans->add_inArc(arc);
        if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr noarc = std::make_shared<ArcNode>();
            noarc->set_placeName(cflow->get_name());
            noarc->set_label("<({"+param->get_name()+"_pr.state :: (contractBalance := "+param->get_name()+"_pr.state.contractBalance - ("+arg+")),"+param->get_name()+"_pr.par})>");
            func_trans->add_outArc(noarc);        
        }else if(param->get_place_type() == PlaceTypeTempData){
            func_trans->add_outArc(arc);
        }
    }

    net->add_transition(func_trans);
    current_subnet->set_in_places(out_places);
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

std::string Translator::translateOperator(std::string _operator, std::string member){
    if(isNormalSign(_operator)){
        return NormalSign[_operator];
    }else{
        if(isSpecialSign(_operator)){
            if(_operator == DoublePlussSign){
                return NormalSign[EqualSign]+" "+member+" "+NormalSign[PlusSign]+" 1";
            }else if(_operator == DoubleMinusSign){
                return NormalSign[EqualSign]+" "+member+" "+NormalSign[MinusSign]+" 1";
            }else{
                std::string s(1,_operator[0]);
                return NormalSign[EqualSign]+" "+member+" "+NormalSign[s];
            }
        }
    }
    return _operator;
}

std::string Translator::translateUnknowExpressionToString(std::string _value){
    std::string ret;
    std::vector<std::string> temp = Utils::split(_value,".");
    if(temp[temp.size()-1] == "sender"){
        ret = _value + ".adr";
    }
    return ret;
}
std::string Translator::translateRequireExpressionToString(ASTNodePtr _arg){
    std::string ret;
    if(_arg->get_node_type() == NodeTypeUnaryOperation){
        UnaryOperationNodePtr exp = std::static_pointer_cast<UnaryOperationNode>(_arg);
        std::string opr = translateRequireExpressionToString(exp->get_operand());

        if(current_subnet->get_place_tempdata_by_name(opr) != nullptr){
            opr = current_subnet->get_place_tempdata_by_name(opr)->get_name()+"_pr";
        }
        ret = opr + " " + translateOperator(exp->get_operator(), opr);
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

        ret = "(" + left_member + ") " + translateOperator(exp->get_operator(), "("+left_member+")") + " (" + right_member + ")";
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
                    ret = current_subnet->get_in_place_by_domain(current_subnet->get_name()+"_state")->get_name()+"_pr.par."+operand;
                }
            }else{
                ret = operand;
            }
        }else{
            ret = operand;
        }
    }else if(_arg->get_node_type() == NodeTypeIndexAccess){
        IndexAccessNodePtr index = std::static_pointer_cast<IndexAccessNode>(_arg);
        std::string identifier = translateRequireExpressionToString(index->get_identifier());
        std::string index_value =  translateRequireExpressionToString(index->get_index_value());
        if(Utils::isInteger(index_value)){
            ret = identifier+"["+index_value+"]";
        } else if(current_subnet->get_place_tempdata_by_name(index_value) != nullptr){
            if(current_subnet->get_place_tempdata_by_name(index_value)->get_domain() == "address"){
                ret = identifier+"["+current_subnet->get_place_tempdata_by_name(index_value)->get_name()+"_pr].value";
            }else{
                ret = identifier+"["+current_subnet->get_place_tempdata_by_name(index_value)->get_name()+"_pr]";
            }
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
            ret = identifier+"["+func_name+"("+identifier+","+index_value+")].value";
        }
    }else if(_arg->get_node_type() == NodeTypeLiteral){
        ret = std::static_pointer_cast<LiteralNode>(_arg)->get_literal();
    }else if(_arg->get_node_type() == NodeTypeFunctionCall){
        FunctionCallNodePtr func_call = std::static_pointer_cast<FunctionCallNode>(_arg);
        if(func_call->get_callee() != nullptr){ 
            std::string calle = translateRequireExpressionToString(func_call->get_callee());
            std::string func_param;
            for(int i = 0; i < func_call->num_arguments(); i++){
                std::string param = translateRequireExpressionToString(func_call->get_argument(i));
                 if(current_subnet->get_place_tempdata_by_name(param) != nullptr){
                    param = current_subnet->get_place_tempdata_by_name(param)->get_name()+"_pr";
                }
                func_param += param + ",";
            }
            if(func_param.size() > 1){
                func_param = func_param.substr(0, func_param.size()-1);
            }
            bool succes = translateUnknowFunction(calle);
            if(succes){
                ret =  calle+"("+func_param+")";
            }else{
                if(net->get_color_by_name(calle) != nullptr){
                    if(Utils::split(func_param,",").size() > 1){
                        ret = "{"+func_param+"}";
                    }
                }else{
                    ret = func_param;
                }
            }
        }
    }
    return ret;
}

bool Translator::translateUnknowFunction(std::string func_name){
    if(func_name == "keccak256"){
        generateKeccak256();
        return true;
    }
    return false;
}

void Translator::generateKeccak256(){
    FunctionNodePtr func = std::make_shared<FunctionNode>();
    func->set_name("keccak256");
    func->set_returnType("bytes32");

    ParamNodePtr uint_par = std::make_shared<ParamNode>();
    uint_par->set_name("value");
    uint_par->set_type("uint");
    ParamNodePtr byte32_par = std::make_shared<ParamNode>();
    byte32_par->set_name("secret");
    byte32_par->set_type("bytes32");

    func->add_parameter(uint_par);
    func->add_parameter(byte32_par);

    std::string body = "\treturn bytes32 (nat (value) * nat (secret));";
    func->set_body(body);

    net->add_function(func);
}

FunctionNodePtr Translator::createGetMappingIndexFunction(std::string name, std::vector<ParamNodePtr> params){
    FunctionNodePtr func = std::make_shared<FunctionNode>();
    func->set_name(name);

    for(auto param = params.begin(); param != params.end(); param++){
        func->add_parameter(*param);
    }
    
    std::string body;
    body = body + "\tint i := 0;" +
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
        if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr narc = std::make_shared<ArcNode>();
            narc->set_placeName("state");
            narc->set_label("<("+param->get_name()+"_pr.state)>");
            revert->add_outArc(narc);  

            ArcNodePtr noarc = std::make_shared<ArcNode>();
            noarc->set_placeName(cflow->get_name());
            noarc->set_label("<("+param->get_name()+"_pr)>");
            not_revert->add_outArc(noarc);         
        }else if(param->get_place_type() == PlaceTypeTempData){
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

void Translator::translateForStatement(ForStatementNodePtr forStatement){
    //init transition
    TransitionNodePtr forloopInt = std::make_shared<TransitionNode>();
    forloopInt->set_name(current_subnet->get_name()+"_initforloop_"+std::to_string(current_subnet->count));
    
    std::vector<PlaceNodePtr> init_out_places;
    std::vector<PlaceNodePtr> out_places;

    PlaceNodePtr initPlace = std::make_shared<PlaceNode>();
    initPlace->set_name(current_subnet->get_name()+"_init_"+std::to_string(current_subnet->count));
    initPlace->set_domain(current_subnet->get_name()+"_state");
    initPlace->set_place_type(PlaceTypeControlFlow);
    net->add_place(initPlace);
    out_places.push_back(initPlace);

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        init_out_places.push_back(param);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");
        forloopInt->add_inArc(arc);

        if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr noarc = std::make_shared<ArcNode>();
            noarc->set_placeName(initPlace->get_name());
            noarc->set_label("<("+param->get_name()+"_pr)>");
            forloopInt->add_outArc(noarc);         
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
    std::vector<PlaceNodePtr> out_places_n_cond;
    std::string exp = translateRequireExpressionToString(forStatement->get_condition());
    
    forloopCond->set_guard(exp+";");
    forloopCondRevert->set_guard("not ("+exp+");");

    PlaceNodePtr condPlace = std::make_shared<PlaceNode>();
    condPlace->set_name(current_subnet->get_name()+"_cond_"+std::to_string(current_subnet->count));
    condPlace->set_domain(current_subnet->get_name()+"_state");
    condPlace->set_place_type(PlaceTypeControlFlow);
    net->add_place(condPlace);
    out_places_cond.push_back(condPlace);

    PlaceNodePtr not_condPlace = std::make_shared<PlaceNode>();
    not_condPlace->set_name(current_subnet->get_name()+"_n_cond_"+std::to_string(current_subnet->count));
    not_condPlace->set_domain(current_subnet->get_name()+"_state");
    not_condPlace->set_place_type(PlaceTypeControlFlow);
    net->add_place(not_condPlace);
    out_places_n_cond.push_back(not_condPlace);

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");
        forloopCond->add_inArc(arc);
        forloopCondRevert->add_inArc(arc);

        if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr narc = std::make_shared<ArcNode>();
            narc->set_placeName(not_condPlace->get_name());
            narc->set_label("<("+param->get_name()+"_pr)>");
            forloopCondRevert->add_outArc(narc);

            ArcNodePtr noarc = std::make_shared<ArcNode>();
            noarc->set_placeName(condPlace->get_name());
            noarc->set_label("<("+param->get_name()+"_pr)>");
            forloopCond->add_outArc(noarc);         
        }else if(param->get_place_type() == PlaceTypeTempData){
            forloopCond->add_outArc(arc);
            forloopCondRevert->add_outArc(arc);
        }
    }

    net->add_transition(forloopCond);
    current_subnet->set_in_places(out_places_cond);

    current_subnet->remove_tempdata_place_bye_name(init_value);

    if(forStatement->get_body()->get_node_type() == NodeTypeBlockNode){
        translateBlock(std::static_pointer_cast<BlockNode>(forStatement->get_body()));
    }else if(forStatement->get_body()->get_node_type() == NodeTypeExpressionStatement){
        current_subnet->count++;
        translateExpressionStatement(std::static_pointer_cast<ExpressionStatementNode>(forStatement->get_body()));
    }


    TransitionNodePtr inc = std::make_shared<TransitionNode>();
    inc->set_name(current_subnet->get_name()+"_forinc"+std::to_string(current_subnet->count));
    
    std::string inc_value = "";
    if(forStatement->get_increment() != nullptr){
        if(forStatement->get_increment()->get_node_type() == NodeTypeExpressionStatement){
            ExpressionStatementNodePtr inc_statement = std::static_pointer_cast<ExpressionStatementNode>(forStatement->get_increment());
            std::string rinc_value = translateRequireExpressionToString(inc_statement->get_expression());

            if(Utils::split(rinc_value," := ").size() > 1){
                inc_value = Utils::split(rinc_value," := ")[1];
            }
        }
    }

    initValuePlace->set_place_type(PlaceTypeWaitData);
    current_subnet->add_in_place(initValuePlace);

    for(int i = 0; i < current_subnet->num_in_places(); i++){
        PlaceNodePtr param = current_subnet->get_in_places(i);
        ArcNodePtr arc = std::make_shared<ArcNode>();
        arc->set_placeName(param->get_name());
        arc->set_label("<("+param->get_name()+"_pr)>");
        inc->add_inArc(arc);
        if(param->get_place_type() == PlaceTypeControlFlow){
            ArcNodePtr arc = std::make_shared<ArcNode>();
            arc->set_placeName(initPlace->get_name());
            arc->set_label("<("+param->get_name()+"_pr)>");
            inc->add_outArc(arc);
        }else if(param->get_place_type() == PlaceTypeTempData){
            ArcNodePtr arc = std::make_shared<ArcNode>();
            arc->set_placeName(param->get_name());
            arc->set_label("<("+param->get_name()+"_pr)>");
            inc->add_outArc(arc);
        }else if(param->get_place_type() == PlaceTypeWaitData){
            ArcNodePtr arc = std::make_shared<ArcNode>();
            arc->set_placeName(param->get_name());
            if(inc_value != ""){
                arc->set_label("<("+inc_value+")>");
            }else{
                arc->set_label("<("+param->get_name()+"_pr)>");
            }
            inc->add_outArc(arc);
        }
    }
    net->add_transition(inc);
    net->add_transition(forloopCondRevert);
    current_subnet->set_in_places(out_places_n_cond);
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
    list_color->set_capacity("50");

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
    list_color->set_capacity("50");
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
