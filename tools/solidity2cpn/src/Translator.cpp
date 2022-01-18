#include "./Translator.hpp"
#include "../../include/Utils.hpp"

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

/** Function Net **/

/** get the net's name
 */
std::string FunctionNet::get_name(){
    return name;
}

/** Add color to the net
 */
void FunctionNet::add_color(const ColorNodePtr& _color) {
    color_nodes.push_back(_color);
}
/** Get a color of the net
 */
ColorNodePtr FunctionNet::get_color(const unsigned int& x) {
    return color_nodes[x];
}
/** Get the number of color in net
 */
size_t FunctionNet::num_colors() {
    return color_nodes.size();
}

void FunctionNet::add_local_variable(const std::string& _name, const PlaceNodePtr& _place){
    if(!is_local_variable(_name)){
        local_variables[_name] = _place;
    }
}

bool FunctionNet::is_local_variable(const std::string& _name){
    if(local_variables.find(_name) == local_variables.end()){
        return false;
    }
    return true;
}

PlaceNodePtr FunctionNet::get_local_variable_by_name(const std::string& _name){
    if(is_local_variable(_name)){
        return local_variables[_name];
    }
    return nullptr;
}

void FunctionNet::set_param_place(const PlaceNodePtr& _place){
    param_place = _place;
}

void FunctionNet::add_place(const PlaceNodePtr& _place){
    std::string place_name = _place->get_name();
    int count = place_name.back() - '0';
    place_name.pop_back();

    place_node_names[place_name] = count;
    place_nodes.push_back(_place);
}

PlaceNodePtr FunctionNet::get_place(const unsigned int& x){
    return place_nodes[x];
}

size_t FunctionNet::num_places(){
    return place_nodes.size();
}

PlaceNodePtr FunctionNet::generateControlFlowPlace(const std::string& _str){
    std::string new_name = to_upper_copy(name)+_str;
    int current_count;
    if(place_node_names.find(new_name) != place_node_names.end()){
        current_count = place_node_names[new_name];
    }else{
        current_count = 0;
    }

    std::string place_name = new_name + std::to_string(current_count+1);

    PlaceNodePtr cflow = std::make_shared<PlaceNode>();
    cflow->set_name(place_name);
    cflow->set_domain(to_upper_copy(name)+"_STATE");

    return cflow;
}

void FunctionNet::add_transition(const TransitionNodePtr& _trans){
    std::string trans_name = _trans->get_name();
    int count = trans_name.back() - '0';
    trans_name.pop_back();

    transition_node_names[trans_name] = count;
    transition_nodes.push_back(_trans);
}

TransitionNodePtr FunctionNet::get_transition(const unsigned int& x){
    return transition_nodes[x];
}

size_t FunctionNet::num_transitions(){
    return transition_nodes.size();
}

std::string FunctionNet::generateTransitionName(const std::string& _str){
    std::string new_name = to_upper_copy(name)+_str;
    int current_count;
    if(transition_node_names.find(new_name) != transition_node_names.end()){
        current_count = transition_node_names[new_name];
    }else{
        current_count = 0;
    }
    
    return new_name + std::to_string(current_count+1);
}

/** SmartContract Net **/
SmartContractNet::SmartContractNet(std::string _name){
    name = _name;

    ColorNodePtr address = std::make_shared<ColorNode>();
    address->set_name("ADDRESS");
    address->set_typeDef("range 0 .. 100");
    
    ColorNodePtr cuint = std::make_shared<ColorNode>();
    cuint->set_name("UINT");
    cuint->set_typeDef("range 0 .. (int'last)"); 

    StructColorNodePtr user = std::make_shared<StructColorNode>();
    user->set_name("USER");

    ComponentNodePtr acomponent = std::make_shared<ComponentNode>();
    acomponent->set_name("adr");
    acomponent->set_type("ADDRESS");
    user->add_component(acomponent);

    ComponentNodePtr bcomponent = std::make_shared<ComponentNode>();
    bcomponent->set_name("balance");
    bcomponent->set_type("UINT");
    user->add_component(bcomponent);

    default_color_nodes.push_back(address);
    default_color_nodes.push_back(cuint);
    default_color_nodes.push_back(user);
}
/** get the net's name
 */
std::string SmartContractNet::get_name(){
    return name;
}
/** Add color to the net
 */
void SmartContractNet::add_color(const ColorNodePtr& _color) {
    color_nodes.push_back(_color);
}
/** Get a color of the net
 */
ColorNodePtr SmartContractNet::get_color(const unsigned int& x) {
    return color_nodes[x];
}
/** Get a color by name
 */
ColorNodePtr SmartContractNet::get_color_by_name(const std::string& _name){
    for(auto it = color_nodes.begin(); it != color_nodes.end(); it++){
        if((*it)->get_name() == _name){
            return (*it);
        }
    }
    return nullptr;
}
/** Get the number of color in net
 */
size_t SmartContractNet::num_colors() {
    return color_nodes.size();
}

void SmartContractNet::add_function_node(const FunctionNodePtr& _func){
    function_nodes.push_back(_func);
}

FunctionNodePtr SmartContractNet::get_function_node(const unsigned int& x){
    return function_nodes[x];
}

size_t SmartContractNet::num_function_nodes(){
    return function_nodes.size();
}


void SmartContractNet::add_state_color(const ColorNodePtr& _color,const std::string& _var_name){
    if(!is_state_color(_var_name))
    {
        stateColor[_var_name] = _color;
    }
}

bool SmartContractNet::is_state_color(const std::string& _name){
    if(stateColor.find(_name) == stateColor.end()){ 
        return false;
    }
    return true;
}

ColorNodePtr SmartContractNet::get_state_color_by_name(const string& _name){
    if(is_state_color(_name)){
        return stateColor[_name];
    }
    return nullptr;
}

void SmartContractNet::add_function(const FunctionNetPtr& _func){
    functionNets.push_back(_func);
}

FunctionNetPtr SmartContractNet::get_function_by_name(const std::string& _func_name){
    for(auto it = functionNets.begin(); it != functionNets.end(); it++){
        if((*it)->get_name() == _func_name){
            return *it;
        }
    }
    return nullptr;
}

std::string SmartContractNet::convertColorInit(const ColorNodePtr& _color){
    if(_color->get_node_type() == LnaNodeTypeColor){
        return _color->get_init_value();
    }else if(_color->get_node_type() == LnaNodeTypeStruct_Color){
        return "";
    }else if(_color->get_node_type() == LnaNodeTypeListColor){
        return "";
    }
    return "";
}


std::string SmartContractNet::source_code(){
    StructuredNetNodePtr net = std::make_shared<StructuredNetNode>(name);
    std::map<std::string, bool> colors;

    net->add_color(std::make_shared<CommentNode>("\n// DEFAULT COLORS DEFINITIONS\n"));
    for(auto it = default_color_nodes.begin(); it != default_color_nodes.end(); it++){
        if(colors.find((*it)->get_name()) == colors.end()){
            colors[(*it)->get_name()] = true;
            net->add_color(*it);
        }
    }

    net->add_color(std::make_shared<CommentNode>("\n// SMARTCONTRACT COLORS DEFINITIONS\n"));
    for(auto it = color_nodes.begin(); it != color_nodes.end(); it++){
        if(colors.find((*it)->get_name()) == colors.end()){
            colors[(*it)->get_name()] = true;
            net->add_color(*it);
        }
    }

    std::vector<std::string> state_init;
    PlaceNodePtr state_place = std::make_shared<PlaceNode>();
    state_place->set_name("S");
    state_place->set_domain("STATE");

    StructColorNodePtr state_color = std::make_shared<StructColorNode>();
    state_color->set_name("STATE");

    for(auto it = stateColor.begin(); it != stateColor.end(); it++){
        ComponentNodePtr state_component = std::make_shared<ComponentNode>();
        state_component->set_name(it->first);
        state_component->set_type((it->second)->get_name());

        state_color->add_component(state_component);
        state_init.push_back(convertColorInit(it->second));

    }
    net->add_color(std::static_pointer_cast<ColorNode>(state_color));

    for(auto it = function_nodes.begin(); it != function_nodes.end(); it++){
        net->add_function(*it);
    }


    net->add_place(std::make_shared<CommentNode>("\n/*\n * Function: state\n */\n"));
    state_place->set_init("<({"+join(state_init,",")+"})>");
    net->add_place(state_place);


    for(auto it = functionNets.begin(); it != functionNets.end(); it++){
        for(size_t i = 0; i < (*it)->num_colors(); i++){
            ColorNodePtr color = (*it)->get_color(i);
            net->add_color(color);
        }
        net->add_place(std::make_shared<CommentNode>("\n/*\n * Function: " + (*it)->get_name() + "\n */\n"));
        for(size_t i = 0; i < (*it)->num_places(); i++){
            PlaceNodePtr place = (*it)->get_place(i);
            net->add_place(place);
        }
        net->add_transition(std::make_shared<CommentNode>("\n/*\n * Function: " + (*it)->get_name() + "\n */\n"));
        for(size_t i = 0; i < (*it)->num_transitions(); i++){
            TransitionNodePtr trans = (*it)->get_transition(i);
            net->add_transition(trans);
        }
    }
    return net->source_code();
}


/** Start translate
 */
std::string Translator::translate() {
    net = std::make_shared<NetNode>();

    for (int i = 0; i < rootNode->num_fields(); i++)
            if (rootNode->get_field(i)->get_node_type() == NodeTypeContractDefinition) {
                //create the net
                auto contractNode = std::static_pointer_cast<ContractDefinitionNode>(rootNode->get_field(i));
                SmartContractNetPtr contractNet = std::make_shared<SmartContractNet>(contractNode->get_name());
                currentCNet = contractNet;

                for (int i = 0; i < contractNode->num_members(); i++){
                    auto member = contractNode->get_member(i);
                    
                    if (member->get_node_type() == NodeTypeStructDefinition) {
                        auto structNode = std::static_pointer_cast<StructDefinitionNode>(member);
                        StructColorNodePtr struct_type = translateStruct(structNode);
                        currentCNet->add_color(std::static_pointer_cast<ColorNode>(struct_type));
                    }else if (member->get_node_type() == NodeTypeVariableDeclaration) {
                        translateVariableDeclaration(member,VariableGlobalType);
                    }
                    else if (member->get_node_type() == NodeTypeFunctionDefinition) {
                        FunctionDefinitionNodePtr func = std::static_pointer_cast<FunctionDefinitionNode>(member);
                        FunctionNetPtr functionNet = std::make_shared<FunctionNet>(func->get_name());
                        currentFNet = functionNet;

                        createFunctionColorPlace(func);

                        BlockNodePtr func_body = func->get_function_body();
                        translateBlock(func_body);

                        in_places.clear();
                        currentCNet->add_function(currentFNet);   
                    }
                }
            }
    return currentCNet->source_code();
}

PlaceNodePtr Translator::translateVariableDeclaration(const ASTNodePtr& _var,const std::string& _type){
    if(_var->get_node_type() == NodeTypeVariableDeclaration){
        auto varNode = std::static_pointer_cast<VariableDeclarationNode>(_var);

        if (varNode->get_type()->get_node_type() == NodeTypeMapping) {
            ListColorNodePtr mapping_type = translateMapping(_var);
            currentCNet->add_color(std::static_pointer_cast<ColorNode>(mapping_type));

            if(_type == VariableGlobalType){
                currentCNet->add_state_color(mapping_type,varNode->get_variable_name());
            }
        }else if(varNode->get_type()->get_node_type() == NodeTypeElementaryTypeName){
            std::string name = std::static_pointer_cast<ElementaryTypeNameNode>(varNode->get_type())->get_type_name();
            ColorNodePtr new_type = std::make_shared<ColorNode>();  
            name = to_upper_copy(name);
            new_type->set_name(name);
            new_type->set_typeDef(DataTypeRange[name]);

            std::string type_value;
            auto value = varNode->get_initial_value();
            if(value != nullptr){
                if(value->get_node_type() == NodeTypeLiteral){
                    type_value = std::static_pointer_cast<LiteralNode>(value)->get_literal();
                }
            }
            new_type->set_init_value(type_value);
            currentCNet->add_color(new_type);

            if(_type == VariableGlobalType){
                currentCNet->add_state_color(new_type,varNode->get_variable_name());
 
            }else if(_type == VariableLocalType){
                PlaceNodePtr new_place = std::make_shared<PlaceNode>();
                std::string place_name = to_upper_copy(currentFNet->get_name())+"_"+varNode->get_variable_name();
                new_place->set_domain(name);
                new_place->set_name(place_name);

                currentFNet->add_place(new_place);
                currentFNet->add_local_variable(varNode->get_variable_name(),new_place);
                
                return new_place;
            }
        }else if(varNode->get_type()->get_node_type() == NodeTypeElementaryTypeName){
            
        }
    }else if(_var->get_node_type() == NodeTypeElementaryTypeName){
        std::string name = std::static_pointer_cast<ElementaryTypeNameNode>(_var)->get_type_name();
        ColorNodePtr new_type = std::make_shared<ColorNode>();  
        name = to_upper_copy(name);
        new_type->set_name(name);
        new_type->set_typeDef(DataTypeRange[name]);
        currentCNet->add_color(new_type);

    }else if(_var->get_node_type() == NodeTypeArrayTypeName){

    }
    return nullptr;
}

StructColorNodePtr Translator::translateStruct(const StructDefinitionNodePtr& struct_node) {
    StructColorNodePtr struct_color = std::make_shared<StructColorNode>();
    struct_color->set_name(to_upper_copy(struct_node->get_name()));
    
    for (int i = 0; i < struct_node->num_fields(); i++) {
        translateVariableDeclaration(struct_node->get_field(i),VariableNonType);

        VariableDeclarationNodePtr variable = std::static_pointer_cast<VariableDeclarationNode>(struct_node->get_field(i));
        ComponentNodePtr component = std::make_shared<ComponentNode>();
        component->set_name(variable->get_variable_name());

        //if type in struct does'not exist then return error
        component->set_type(to_upper_copy(std::static_pointer_cast<ElementaryTypeNameNode>(variable->get_type())->get_type_name()));//can change to function get varinfor
        struct_color->add_component(component);
    }
    return struct_color;
}

ListColorNodePtr Translator::translateMapping(const ASTNodePtr& _node) {
    ListColorNodePtr list_color = std::make_shared<ListColorNode>();
    StructColorNodePtr struct_color = std::make_shared<StructColorNode>();
    auto var_node = std::static_pointer_cast<VariableDeclarationNode>(_node);
    auto mapNode = std::static_pointer_cast<MappingNode>(var_node->get_type());
    struct_color->set_name("STRUCT_" + to_upper_copy(var_node->get_variable_name()));
    ComponentNodePtr key = std::make_shared<ComponentNode>();
    key->set_name("adr");
    if (mapNode->get_key_type()->get_node_type() == NodeTypeElementaryTypeName) {
        auto key_type = std::static_pointer_cast<ElementaryTypeNameNode>(mapNode->get_key_type());
        key->set_type(to_upper_copy(key_type->get_type_name()));
    }
    else {
        auto key_type = std::static_pointer_cast<UserDefinedTypeNameNode>(mapNode->get_key_type());
        key->set_type(to_upper_copy(key_type->get_type_name()));
    }
    translateVariableDeclaration(mapNode->get_key_type(),VariableNonType);

    ComponentNodePtr value = std::make_shared<ComponentNode>();
    value->set_name("uint");
    if (mapNode->get_value_type()->get_node_type() == NodeTypeElementaryTypeName) {
        auto value_type = std::static_pointer_cast<ElementaryTypeNameNode>(mapNode->get_value_type());
        value->set_type(to_upper_copy(value_type->get_type_name()));
    }
    else if (mapNode->get_value_type()->get_node_type() == NodeTypeArrayTypeName) {
        auto value_type = std::static_pointer_cast<ArrayTypeNameNode>(mapNode->get_value_type());
        ListColorNodePtr array_type = translateArray(value_type);
        currentCNet->add_color(std::static_pointer_cast<ColorNode>(array_type));
        value->set_type(to_upper_copy(array_type->get_name()));
    }
    translateVariableDeclaration(mapNode->get_value_type(),VariableNonType);

    struct_color->add_component(key);
    struct_color->add_component(value);
    currentCNet->add_color(std::static_pointer_cast<ColorNode>(struct_color));
    
    list_color->set_name("LIST_"+ to_upper_copy(var_node->get_variable_name()));
    list_color->set_index_type("nat");
    list_color->set_element_type(struct_color->get_name());
    list_color->set_capacity("50");

    return list_color;
}

ListColorNodePtr Translator::translateArray(const ArrayTypeNameNodePtr& array_node){
    translateVariableDeclaration(array_node->get_base_type(),VariableNonType);
    auto base_type = std::static_pointer_cast<UserDefinedTypeNameNode>(array_node->get_base_type());
    ListColorNodePtr list_color = std::make_shared<ListColorNode>();
    list_color->set_name("list_"+ base_type->get_type_name());
    list_color->set_index_type("nat");
    list_color->set_element_type(base_type->get_type_name());
    list_color->set_capacity("50");
    return list_color;
}

void Translator::createFunctionColorPlace(const FunctionDefinitionNodePtr& func){
    StructColorNodePtr funcParColor = std::make_shared<StructColorNode>();
    funcParColor->set_name(to_upper_copy(func->get_name())+"_PAR");

    ComponentNodePtr spcomponent = std::make_shared<ComponentNode>();
    spcomponent->set_name("sender");
    spcomponent->set_type("USER");
    funcParColor->add_component(spcomponent);

    ComponentNodePtr vpcomponent = std::make_shared<ComponentNode>();
    vpcomponent->set_name("value");
    vpcomponent->set_type("UINT");
    funcParColor->add_component(vpcomponent);

    ParameterListNodePtr func_params = func->get_params();
    for(int i = 0; i < func_params->num_parameters(); i++){
        auto param = func_params->get_parameter(i);
        if(param->get_node_type() == NodeTypeVariableDeclaration){
            auto varParam = std::static_pointer_cast<VariableDeclarationNode>(param);          
            if(varParam->get_type()->get_node_type() == NodeTypeElementaryTypeName){
                std::string type_name = std::static_pointer_cast<ElementaryTypeNameNode>(varParam->get_type())->get_type_name();
                
                ComponentNodePtr component = std::make_shared<ComponentNode>();
                component->set_name(varParam->get_variable_name());
                component->set_type(type_name);
                funcParColor->add_component(component);
                
            }else if(varParam->get_type()->get_node_type() == NodeTypeArrayTypeName){
                auto arrayNode = std::static_pointer_cast<ArrayTypeNameNode>(varParam->get_type());
                ListColorNodePtr array_type = translateArray(arrayNode);
                currentFNet->add_color(array_type);

                ComponentNodePtr component = std::make_shared<ComponentNode>();
                component->set_name(varParam->get_variable_name());
                component->set_type(array_type->get_name());
                funcParColor->add_component(component);
            }
        }
    }
    currentFNet->add_color(funcParColor);

    StructColorNodePtr funcStateColor = std::make_shared<StructColorNode>();
    funcStateColor->set_name(to_upper_copy(func->get_name())+"_STATE");

    ComponentNodePtr sscomponent = std::make_shared<ComponentNode>();
    sscomponent->set_name("state");
    sscomponent->set_type("STATE");
    funcStateColor->add_component(sscomponent);

    ComponentNodePtr pscomponent = std::make_shared<ComponentNode>();
    pscomponent->set_name("par");
    pscomponent->set_type(funcParColor->get_name());
    funcStateColor->add_component(pscomponent);
    currentFNet->add_color(funcStateColor);


    PlaceNodePtr func_place = std::make_shared<PlaceNode>();
    func_place->set_name("P_"+to_upper_copy(func->get_name()));
    func_place->set_domain(funcParColor->get_name());
    currentFNet->set_param_place(func_place);

    PlaceNodePtr state_place = std::make_shared<PlaceNode>();
    state_place->set_name("S");
    state_place->set_domain("STATE");

    in_places.push_back(state_place);
    in_places.push_back(func_place);
    in_state_type = PlaceStateType;
}

void Translator::translateBlock(const BlockNodePtr& block){
    for(int i = 0; i < block->num_statements(); i++){
        ASTNodePtr statement = block->get_statement(i);
        if(statement->get_node_type() == NodeTypeIfStatement){
            IfStatementNodePtr if_statement = std::static_pointer_cast<IfStatementNode>(statement);
            translateIfStatement(if_statement);
        }else if(statement->get_node_type() == NodeTypeForStatement){
            ForStatementNodePtr for_statement = std::static_pointer_cast<ForStatementNode>(statement);
            /* translateForStatement(for_statement); */
        }else if(statement->get_node_type() == NodeTypeExpressionStatement){
            ExpressionStatementNodePtr expression_statement = std::static_pointer_cast<ExpressionStatementNode>(statement);
            translateExpressionStatement(expression_statement);
        }else if(statement->get_node_type() == NodeTypeVariableDeclarationStatement){
            VariableDeclarationStatementNodePtr vardecl_statement = std::static_pointer_cast<VariableDeclarationStatementNode>(statement);
            translateVariableDeclarationStatement(vardecl_statement);
        }
    }
}

void Translator::translateExpressionStatement(const ExpressionStatementNodePtr& statement){
    translate_equivalent_node(statement->get_expression());
}

void Translator::translate_equivalent_node(const ASTNodePtr& _node){
    if (_node->get_node_type() == NodeTypeFunctionCall) {
        translateFunctionCall(std::static_pointer_cast<FunctionCallNode>(_node));
    }else if(_node->get_node_type() == NodeTypeVariableDeclarationStatement){
        translateVariableDeclarationStatement(std::static_pointer_cast<VariableDeclarationStatementNode>(_node));
    }else if(_node->get_node_type() == NodeTypeAssignment){
        translateAssignment(std::static_pointer_cast<AssignmentNode>(_node));
    }
}

void Translator::translateFunctionCall(const FunctionCallNodePtr& func_call){
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
                /* translateTransferFunctionCall(member_access->get_identifier(),func_call->get_argument(0)); */
            }else if(member == "push"){
                /* translatePushFunctionCall(member_access->get_identifier(),func_call->get_argument(0)); */
            }
            /* translateSpecificFunctionCall(member,member_access->get_identifier(),func_call); */
        }
    }   
}

void Translator::translateRequireFunctionCall(const ASTNodePtr& _arg){
    std::string require_exp = translateRequireExpressionToString(_arg);
    
    TransitionNodePtr revert = std::make_shared<TransitionNode>();
    revert->set_name(currentFNet->generateTransitionName("_revert"));
    revert->set_guard("not("+require_exp+");");

    TransitionNodePtr not_revert = std::make_shared<TransitionNode>();
    not_revert->set_name(currentFNet->generateTransitionName("_n_revert"));
    not_revert->set_guard(require_exp+";");

    PlaceNodePtr cflow = currentFNet->generateControlFlowPlace("_P");
    currentFNet->add_place(cflow);

    ArcNodePtr oarc = generateStateParOutArc(cflow);
    not_revert->add_outArc(oarc);
    

    ArcNodePtr narc = generateStateOutArc();
    revert->add_outArc(narc); 

    while(!in_places.empty()){
        PlaceNodePtr param = in_places.back();
        std::string place_type = getPlaceTypeInFlow(param);
        ArcNodePtr arc = generateArcInByPlace(param,place_type);
        revert->add_inArc(arc);
        not_revert->add_inArc(arc);

        in_places.pop_back();
    }

    in_places.push_back(cflow);

    currentFNet->add_transition(revert);
    currentFNet->add_transition(not_revert);
    in_state_type = PlaceStateParType;
}

void Translator::translateVariableDeclarationStatement(const VariableDeclarationStatementNodePtr& statement){
    VariableDeclarationNodePtr decl = statement->get_decl();
    std::string vardec_exp = translateRequireExpressionToString(statement->get_value());

    PlaceNodePtr cflow =  currentFNet->generateControlFlowPlace("_VD");
    currentFNet->add_place(cflow);

    TransitionNodePtr vardec = std::make_shared<TransitionNode>();
    vardec->set_name(currentFNet->generateTransitionName("_vd"));

    ArcNodePtr oarc = generateStateParOutArc(cflow);
    vardec->add_outArc(oarc);
    

    PlaceNodePtr color_place = translateVariableDeclaration(decl, VariableLocalType);
    ArcNodePtr decArc = std::make_shared<ArcNode>();
    decArc->set_placeName(color_place->get_name());
    decArc->set_label("<("+vardec_exp+")>");
    vardec->add_outArc(decArc);

    while(!in_places.empty()){
        PlaceNodePtr param = in_places.back();
        std::string place_type = getPlaceTypeInFlow(param);
        ArcNodePtr arc = generateArcInByPlace(param,place_type);
        vardec->add_inArc(arc);
        
        in_places.pop_back();
    }
    in_places.push_back(cflow);

    currentFNet->add_transition(vardec);
    
    in_state_type = PlaceStateParType;
}

void Translator::translateIfStatement(const IfStatementNodePtr& statement){
    std::vector<PlaceNodePtr> init_out_places;
    
    std::string exp = translateRequireExpressionToString(statement->get_condition());

    TransitionNodePtr ifstate = std::make_shared<TransitionNode>();
    ifstate->set_name(currentFNet->generateTransitionName("_tT"));
    ifstate->set_guard(exp+";");

    TransitionNodePtr not_ifstate = std::make_shared<TransitionNode>();
    not_ifstate->set_name(currentFNet->generateTransitionName("_tF"));
    not_ifstate->set_guard("not("+exp+");");

    PlaceNodePtr cflow_if = currentFNet->generateControlFlowPlace("_PT");
    currentFNet->add_place(cflow_if);

    ArcNodePtr oarc_if = generateStateParOutArc(cflow_if);
    ifstate->add_outArc(oarc_if);

    PlaceNodePtr cflow_not_if = currentFNet->generateControlFlowPlace("_PF");
    currentFNet->add_place(cflow_not_if);

    ArcNodePtr oarc_not_if = generateStateParOutArc(cflow_not_if);
    not_ifstate->add_outArc(oarc_not_if);

    while(!in_places.empty()){
        PlaceNodePtr param = in_places.back();
        std::string place_type = getPlaceTypeInFlow(param);
        ArcNodePtr arc = generateArcInByPlace(param,place_type);
        ifstate->add_inArc(arc);
        not_ifstate->add_inArc(arc);

        in_places.pop_back();
    }
    in_places.push_back(cflow_if);

    currentFNet->add_transition(ifstate);

    if(statement->get_then() != nullptr){
        if(statement->get_then()->get_node_type() == NodeTypeBlockNode){
            translateBlock(std::static_pointer_cast<BlockNode>(statement->get_then()));
        }else if(statement->get_then()->get_node_type() == NodeTypeExpressionStatement){
            translateExpressionStatement(std::static_pointer_cast<ExpressionStatementNode>(statement->get_then()));
        }
    }

    currentFNet->add_transition(not_ifstate);
    in_places.clear();
    in_places.push_back(cflow_not_if);

    if(statement->get_else() != nullptr){
        if(statement->get_else()->get_node_type() != NodeTypeIfStatement){
            if(statement->get_else()->get_node_type() == NodeTypeExpressionStatement){
                translateExpressionStatement(std::static_pointer_cast<ExpressionStatementNode>(statement->get_else()));
            }
        }else{
            translateIfStatement(std::static_pointer_cast<IfStatementNode>(statement->get_else()));
        }
    }else{

    }
}


void Translator::translateAssignment(const AssignmentNodePtr& assignment){
    TransitionNodePtr assign = std::make_shared<TransitionNode>();
    assign->set_name(currentFNet->generateTransitionName("_as"));

    PlaceNodePtr cflow = currentFNet->generateControlFlowPlace("_AS");
    currentFNet->add_place(cflow);

    std::string left_member = translateRequireExpressionToString(assignment->get_left_hand_operand());
    std::string right_member = translateRequireExpressionToString(assignment->get_right_hand_operand());

    std::vector<std::string> temp = split(left_member,".");
    std::string id = temp[0];

    std::vector<std::string> cvalue = createChangeValueLet(cflow->get_name(),left_member,right_member,assignment->get_operator());
    for(auto it = cvalue.begin(); it != cvalue.end(); it++){
        assign->add_let(*it);
    }

    ArcNodePtr oarc = std::make_shared<ArcNode>();
    oarc->set_placeName(cflow->get_name());
    if(id == "sp"){
        oarc->set_label("<("+id+"_temp"+")>");
    }else if(id == "s"){
        oarc->set_label("<({"+id+"_temp"+","+getParInArc()+"})>");
    }else if(id == "p"){
        oarc->set_label("<({"+getStateInArc()+","+id+"_temp"+"})>");
    }
    assign->add_outArc(oarc);

    while(!in_places.empty()){
        PlaceNodePtr param = in_places.back();
        std::string place_type = getPlaceTypeInFlow(param);
        ArcNodePtr arc = generateArcInByPlace(param,place_type);
        assign->add_inArc(arc);

        in_places.pop_back();
    }
    in_places.push_back(cflow);

    currentFNet->add_transition(assign);
    
    in_state_type = PlaceStateParType;
}


std::string Translator::translateOperator(const std::string& _operator, const std::string& member){
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

std::string Translator::translateMemberAcess(const std::string& _member){
    //temp need update in future
    if(_member == "length"){
        return "'size";
    }else if(_member == "sender"){
        return ".sender.adr";
    }
    return "."+_member;
}

FunctionNodePtr Translator::createGetMappingIndexFunction(const std::string& name, const ParamNodePtr& param1, const ParamNodePtr& param2){
    FunctionNodePtr func = std::make_shared<FunctionNode>();
    func->set_name(name);

    func->add_parameter(param1);
    func->add_parameter(param2);
    
    std::string body;
    body = body + "\tint i := 0;" +
                  "\n\twhile (i<"+param1->get_name()+"'size and "+param1->get_name()+"[i]."+param2->get_name()+"!="+param2->get_name()+") i := i+1;"+
                  "\n\tif(i<"+param1->get_name()+"'size)"+
                  "\n\t\treturn i;"+
                  "\n\telse"+
                  "\n\t\treturn -1;";
    func->set_body(body);

    func->set_returnType("int");
   return func;
}

std::vector<std::string> Translator::createChangeValueLet(const std::string& name, const std::string& left_member, const std::string& right_member, const std::string& op){
    std::vector<std::string> temp = split(left_member,".");
    std::string id = temp[0];
    
    std::string domain;

    if(id == "sp"){
        domain = to_upper_copy(currentFNet->get_name()) + "_STATE";
    }else if(id == "s"){
        domain = "STATE";
    }else if(id == "p"){
        domain = to_upper_copy(currentFNet->get_name()) + "_PAR";
    }
   
    std::vector<std::string> fbody;
    fbody.push_back(domain + " " + id + "_temp " + NormalSign[EqualSign] + " " + id + ";");
    std::string l_member;
    l_member = temp[0] + "_temp.";
    for(int i = 1; i < temp.size()-1; i++){
        l_member += temp[i] + ".";
    }
    l_member += temp[temp.size()-1];
    fbody.push_back(l_member + " " +translateOperator(op,l_member) + " " + right_member + ";");
    return fbody;
}


std::string Translator::translateRequireExpressionToString(const ASTNodePtr& _arg){
    std::string ret;
    if(_arg->get_node_type() == NodeTypeUnaryOperation){
        UnaryOperationNodePtr exp = std::static_pointer_cast<UnaryOperationNode>(_arg);
        std::string opr = translateRequireExpressionToString(exp->get_operand());
    }else if(_arg->get_node_type() == NodeTypeBinaryOperation){
        BinaryOperationNodePtr exp = std::static_pointer_cast<BinaryOperationNode>(_arg);
        std::string left_member = translateRequireExpressionToString(exp->get_left_hand_operand());
        std::string right_member = translateRequireExpressionToString(exp->get_right_hand_operand());

        ret = "(" + left_member + ") " + translateOperator(exp->get_operator(), "("+left_member+")") + " (" + right_member + ")";
    }else if(_arg->get_node_type() == NodeTypeMemberAccess){
        MemberAccessNodePtr member_access = std::static_pointer_cast<MemberAccessNode>(_arg);
        std::string identifier = translateRequireExpressionToString(member_access->get_identifier());
        std::string member = translateMemberAcess(member_access->get_member());
        ret = identifier + member;

    }else if(_arg->get_node_type() == NodeTypeIdentifier){
        std::string operand;
        operand = std::static_pointer_cast<IdentifierNode>(_arg)->get_name();
        
        if(isInteger(operand)){
            ret = operand;
        }else if(operand == "msg"){
            ret = getParInArc();
        }else if(currentFNet->is_local_variable(operand)){
            PlaceNodePtr lc_place = currentFNet->get_local_variable_by_name(operand);
            in_places.push_back(lc_place);

            ret = generateArcInLabel(lc_place, PlaceVarialeLocalType);
        }else if(currentCNet->is_state_color(operand)){
            ret = getStateInArc() + "." + operand;
        }
    }else if(_arg->get_node_type() == NodeTypeLiteral){
        ret = std::static_pointer_cast<LiteralNode>(_arg)->get_literal();
    }else if(_arg->get_node_type() == NodeTypeIndexAccess){
        IndexAccessNodePtr index = std::static_pointer_cast<IndexAccessNode>(_arg);
        std::string identifier = translateRequireExpressionToString(index->get_identifier());
        std::string index_value =  translateRequireExpressionToString(index->get_index_value());
        std::vector<std::string> temp_id = split(identifier,".");
        std::vector<std::string> temp_in = split(index_value,".");
        std::string identifier_last = temp_id[temp_id.size()-1];
        std::string index_last = temp_in[temp_in.size()-1];

        if(isInteger(index_value) || 
          (currentCNet->is_state_color(index_last) && currentCNet->get_state_color_by_name(index_last)->get_name() == "UINT8")){
            ret = identifier+"[nat("+index_value+")]";
        } else{ 
            if(currentCNet->is_state_color(identifier_last)){
                ColorNodePtr or_color = currentCNet->get_state_color_by_name(identifier_last);
                if(or_color->get_node_type() == LnaNodeTypeListColor){
                    ListColorNodePtr color = std::static_pointer_cast<ListColorNode>(or_color);
                    ColorNodePtr color_type = currentCNet->get_color_by_name(color->get_element_type());
                    
                    if(color_type != nullptr && color_type->get_node_type() == LnaNodeTypeStruct_Color){
                        StructColorNodePtr color_type_struct = std::static_pointer_cast<StructColorNode>(color_type);
                        std::string func_name;
                        func_name = "get"+color->get_name()+"Index";

                        ParamNodePtr param1 = std::make_shared<ParamNode>();
                        ParamNodePtr param2 = std::make_shared<ParamNode>();
                        param1->set_name("gis");
                        param1->set_type(color->get_name());
                        param2->set_name(color_type_struct->get_component(0)->get_name());
                        param2->set_type(color_type_struct->get_component(0)->get_type());

                        FunctionNodePtr mif_function = createGetMappingIndexFunction(func_name,param1,param2);
                        currentCNet->add_function_node(mif_function);

                        ret = identifier+"["+func_name+"("+identifier+","+index_value+")]." + color_type_struct->get_component(1)->get_name();
                    }
                }
            }
        }
    }

    return ret;
}


/** Process
 * 
 */

std::string Translator::getStateInArc(){
    if(in_state_type == PlaceStateType){
        return "s";
    }else if(in_state_type == PlaceStateParType){
        return "sp.state";
    }
    return "";
}

std::string Translator::getParInArc(){
    if(in_state_type == PlaceStateType){
        return "p";
    }else if(in_state_type == PlaceStateParType){
        return "sp.par";
    }
    return "";
}

ArcNodePtr Translator::generateStateOutArc(){
    ArcNodePtr narc = std::make_shared<ArcNode>();
    narc->set_placeName("S");
    narc->set_label("<("+getStateInArc()+")>");
    return narc;
}

ArcNodePtr Translator::generateStateParOutArc(const PlaceNodePtr& _place){
    ArcNodePtr narc = std::make_shared<ArcNode>();
    narc->set_placeName(_place->get_name());
    std::string arc_p;
    if(in_state_type == PlaceStateType){
        arc_p = "{" + getStateInArc() + "," + getParInArc() + "}";
    }else if(in_state_type == PlaceStateParType){
        arc_p = "sp";
    }

    narc->set_label("<("+arc_p+")>");
    return narc;
}

std::string Translator::getPlaceTypeInFlow(const PlaceNodePtr _place){
    std::string domain = _place->get_domain();

    if(domain == "STATE"){
        return PlaceStateType;
    }else if(domain == to_upper_copy(currentFNet->get_name() + "_STATE")){
        return PlaceStateParType;
    }else if(domain == to_upper_copy(currentFNet->get_name()) + "_PAR"){
        return PlaceParType;
    }else{
        std::vector<std::string> temp = split_ex(_place->get_name(),"_",2);
        std::string place_name = temp.back();
        place_name.pop_back();

        if(currentFNet->is_local_variable(place_name)){
            return PlaceVarialeLocalType;
        }
    }

    return "";
}

std::string Translator::generateArcInLabel(const PlaceNodePtr& _place, const std::string& _place_type){
    std::string arc_p; 
    if(_place_type == PlaceStateType){
        arc_p = "s";
    }else if(_place_type == PlaceStateParType){
        arc_p = "sp";
    }else if(_place_type == PlaceParType){
        arc_p = "p";
    }else{
        std::vector<std::string> temp = split_ex(_place->get_name(),"_",2);
        arc_p = temp.back();
    }

    return arc_p;
}

ArcNodePtr Translator::generateArcInByPlace(const PlaceNodePtr& _place,const std::string& _place_type){
    std::string arc_p = generateArcInLabel(_place, _place_type);

    ArcNodePtr arc = std::make_shared<ArcNode>();
    arc->set_placeName(_place->get_name());
    arc->set_label("<("+arc_p+")>");
    return arc;
}

}
