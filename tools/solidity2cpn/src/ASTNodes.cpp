#include "../include/ASTNodes.hpp"

namespace SOL2CPN {

/* ------- Indentation ------- */
Indentation::Indentation(const Indentation& _indentation) {
    tab_width = _indentation.tab_width;
    use_spaces = _indentation.use_spaces;
    current_tab_width = _indentation.current_tab_width;
}

Indentation& Indentation::operator++() {
    current_tab_width += tab_width;
    return *this;
}

Indentation Indentation::operator++(int) {
    Indentation result(*this);
    ++(*this);
    return result;
}

Indentation& Indentation::operator--() {
    current_tab_width -= tab_width;
    if (current_tab_width < 0) current_tab_width = 0;
    return *this;
}

Indentation Indentation::operator--(int) {
    Indentation result(*this);
    --(*this);
    return result;
}

Indentation& Indentation::operator=(const Indentation& _indentation ) {
    tab_width = _indentation.tab_width;
    use_spaces = _indentation.use_spaces;
    current_tab_width = _indentation.current_tab_width;
    return *this;
}

std::string Indentation::str() const {
    std::string result;
    for (int i = 0; i < current_tab_width; ++i) {
        result = result + (use_spaces? ' ': '\t');
    }
    return result;
}

/*  */
std::ostream& operator<<(std::ostream& _os, const Indentation& _indentation) {
    _os << _indentation.str();
    return _os;
}

std::string operator+(const std::string& _str, const Indentation& _indentation) {
    std::string result = _str + _indentation.str();
    return result;
}

std::string operator+(const Indentation& _indentation, const std::string& _str) {
    std::string result = _indentation.str() + _str;
    return result;
}

/* ------- ASTNode ------- */
NodeType ASTNode::get_node_type() const {
    return node_type;
}

void ASTNode::append_sub_node(const ASTNodePtr& _node) {
    ast_nodes.push_back(_node);
}

void ASTNode::delete_sub_node(const unsigned int& x) {
    ast_nodes.erase(ast_nodes.begin() + x);
}

void ASTNode::update_sub_node(const unsigned int& x, const ASTNodePtr _node) {
    ast_nodes[x] = _node;
}

ASTNodePtr ASTNode::get_sub_node(const unsigned int& x) const {
    return ast_nodes[x];
}

size_t ASTNode::size() {
    return ast_nodes.size();
}

ASTNodePtr ASTNode::operator[] (const unsigned int& x) {
    return ast_nodes[x];
}


/* ------- RootNode ------- */
void RootNode::add_field(const ASTNodePtr& _node) {
    append_sub_node(_node);
}

size_t RootNode::num_fields() {
    return size();
}

ASTNodePtr RootNode::operator[] (const unsigned int& x) {
    return get_sub_node(x);
}

void RootNode::update_field(const unsigned int& x, const ASTNodePtr& _node) {
    update_sub_node(x, _node);
}

void RootNode::delete_field(const unsigned int& x) {
    delete_sub_node(x);
}

ASTNodePtr RootNode::get_field(const unsigned int& x) {
    return get_sub_node(x);
}


void PragmaDirectiveNode::set_literals(const Literals& _literals) {
    literals = _literals;
}

Literals PragmaDirectiveNode::get_literals() {
    return literals;
}

void ImportDirectiveNode::set_file(const std::string& _file) {
    file = _file;
}

void ImportDirectiveNode::set_symbol_aliases(const std::string& _symbol_aliases) {
    symbol_aliases = _symbol_aliases;
}

void ImportDirectiveNode::set_unit_alias(const std::string& _unit_aliases) {
    unit_alias = _unit_aliases;
}

void ImportDirectiveNode::set_original(const std::string& _original) {
    original = _original;
}

std::string ImportDirectiveNode::get_file() {
    return file;
}

std::string ImportDirectiveNode::get_symbol_aliases() {
    return symbol_aliases;
}

std::string ImportDirectiveNode::get_unit_aliases() {
    return unit_alias;
}

std::string ImportDirectiveNode::get_original() {
    return original;
}


void UsingForDirectiveNode::set_using(const std::string& _using) {
    A = _using;
}

void UsingForDirectiveNode::set_for(const std::string& _for) {
    B = _for;
}

std::string UsingForDirectiveNode::get_using() {
    return A;
}

std::string UsingForDirectiveNode::get_for() {
    return B;
}

void VariableDeclarationNode::set_type(const ASTNodePtr& _type) {
    type = _type;
}

void VariableDeclarationNode::set_variable_name(const std::string& _variable_name) {
    variable_name = _variable_name;
}

void VariableDeclarationNode::set_initial_value(const ASTNodePtr& _initial_value) {
    initial_value = _initial_value;
}

ASTNodePtr VariableDeclarationNode::get_type() {
    return type;
}

std::string VariableDeclarationNode::get_variable_name() {
    return variable_name;
}

std::string VariableDeclarationNode::get_type_str() {
    return type_str;
}

void VariableDeclarationNode::set_type_str(const std::string& _type_str) {
    type_str = _type_str;
}

ASTNodePtr VariableDeclarationNode::get_initial_value() {
    return initial_value;
}


VariableDeclarationNodePtr VariableDeclarationStatementNode::get_decl() const {
    return decl;
}

ASTNodePtr VariableDeclarationStatementNode::get_value() const {
    return value;
}

void VariableDeclarationStatementNode::set_decl(const VariableDeclarationNodePtr& _decl) {
    decl = _decl;
}

void VariableDeclarationStatementNode::set_value(const ASTNodePtr& _value) {
    value = _value;
}


std::string IdentifierNode::get_name() const {
    return name;
}

void IdentifierNode::set_name(const std::string& _name) {
    name = _name;
}


std::string StructDefinitionNode::get_name() const {
    return name;
}

void StructDefinitionNode::set_name(const std::string& _name) {
    name = _name;
}

void StructDefinitionNode::add_field(const ASTNodePtr& _node) {
    append_sub_node(_node);
}

size_t StructDefinitionNode::num_fields() {
    return size();
}

ASTNodePtr StructDefinitionNode::operator[] (const unsigned int& x) {
    return get_sub_node(x);
}

void StructDefinitionNode::update_field(const unsigned int& x, const ASTNodePtr& _node) {
    update_sub_node(x, _node);
}

void StructDefinitionNode::delete_field(const unsigned int& x) {
    delete_sub_node(x);
}

ASTNodePtr StructDefinitionNode::get_field(const unsigned int& x) {
    return get_sub_node(x);
}


void ParameterListNode::add_parameter(const ASTNodePtr& _node) {
    append_sub_node(_node);
}

void ParameterListNode::delete_parameter(const unsigned int& x) {
    delete_sub_node(x);
}

void ParameterListNode::update_parameter(const unsigned int& x, const ASTNodePtr& _node) {
    update_sub_node(x, _node);
}

ASTNodePtr ParameterListNode::get_parameter(const unsigned int& x) {
    return get_sub_node(x);
}

size_t ParameterListNode::num_parameters() {
    return size();
}

ASTNodePtr ParameterListNode::operator[] (const unsigned int& x) {
    return get_sub_node(x);
}

void EventDefinitionNode::set_argument_list(const ParameterListNodePtr& _node) {
    argument_list = _node;
}

ParameterListNodePtr EventDefinitionNode::get_argument_list() const {
    return argument_list;
}




std::string EventDefinitionNode::get_name() const {
    return name;
}

void EventDefinitionNode::set_name(const std::string& _name) {
    name = _name;
}


ASTNodePtr ExpressionStatementNode::get_expression() const {
    return expression;
}

void ExpressionStatementNode::set_expression(const ASTNodePtr& _expression) {
    expression = _expression;
}



ASTNodePtr EmitStatementNode::get_event_call() const {
    return event_call;
}

void EmitStatementNode::set_event_call(const ASTNodePtr& _event_call) {
    event_call = _event_call;
}


ASTNodePtr IndexAccessNode::get_identifier() const {
    return identifier;
}

ASTNodePtr IndexAccessNode::get_index_value() const {
    return index_value;
}

void IndexAccessNode::set_identifier(const ASTNodePtr& _identifier) {
    identifier = _identifier;
}

void IndexAccessNode::set_index_value(const ASTNodePtr& _index_value) {
    index_value = _index_value;
}


std::string BinaryOperationNode::get_return_type_str() const {
    return return_type_str;
}

void BinaryOperationNode::set_return_type_str(const std::string& _return_type_str) {
    return_type_str = _return_type_str;
}

std::string BinaryOperationNode::get_operator() const {
    return op;
}

void BinaryOperationNode::set_operator(const std::string& _operator) {
    op = _operator;
}

ASTNodePtr BinaryOperationNode::get_left_hand_operand() const {
    return left_hand_operand;    
}

ASTNodePtr BinaryOperationNode::get_right_hand_operand() const {
    return right_hand_operand;
}

void BinaryOperationNode::set_left_hand_operand(const ASTNodePtr& _operand) {
    left_hand_operand = _operand;
}

void BinaryOperationNode::set_right_hand_operand(const ASTNodePtr& _operand) {
    right_hand_operand = _operand;
}


std::string UnaryOperationNode::get_operator() const {
    return op;
}

void UnaryOperationNode::set_operator(const std::string& _operator) {
    op = _operator;
}

ASTNodePtr UnaryOperationNode::get_operand() const {
    return operand;
}

void UnaryOperationNode::set_operand(const ASTNodePtr& _operand) {
    operand = _operand;
}

bool UnaryOperationNode::operation_is_prefix() const {
    return is_prefix;
}

void UnaryOperationNode::operation_is_prefix(bool _boolean) {
    is_prefix = _boolean;
}


void LiteralNode::set_literal(const std::string& _literal) {
    literal = _literal;
}

std::string LiteralNode::get_literal() const {
    return literal;
}


void TupleExpressionNode::add_member(const ASTNodePtr& _node) {
    append_sub_node(_node);
}

void TupleExpressionNode::delete_member(const unsigned int& x) {
    delete_sub_node(x);
}

void TupleExpressionNode::update_member(const unsigned int& x, const ASTNodePtr& _node) {
    update_sub_node(x, _node);
}

ASTNodePtr TupleExpressionNode::get_member(const unsigned int& x) {
    return get_sub_node(x);
}

size_t TupleExpressionNode::num_members() {
    return size();
}

ASTNodePtr TupleExpressionNode::operator[] (const unsigned int& x) {
    return get_sub_node(x);
}


void BlockNode::add_statement(const ASTNodePtr& _node) {
    append_sub_node(_node);
}

void BlockNode::delete_statement(const unsigned int& x) {
    delete_sub_node(x);
}

void BlockNode::update_statement(const unsigned int& x, const ASTNodePtr& _node) {
    update_sub_node(x, _node);
}

ASTNodePtr BlockNode::get_statement(const unsigned int& x) {
    return get_sub_node(x);
}

size_t BlockNode::num_statements() {
    return size();
}

ASTNodePtr BlockNode::operator[] (const unsigned int& x) {
    return get_sub_node(x);
}



ASTNodePtr ReturnNode::get_operand() const {
    return operand;
}

void ReturnNode::set_operand(const ASTNodePtr& _operand) {
    operand = _operand;
}


std::string ModifierDefinitionNode::get_name() const {
    return name;
}

ParameterListNodePtr ModifierDefinitionNode::get_params() const {
    return params;
}

ASTNodePtr ModifierDefinitionNode::get_body() const {
    return body;
}

void ModifierDefinitionNode::set_name(const std::string& _name) {
    name = _name;
}

void ModifierDefinitionNode::set_params(const ParameterListNodePtr& _params) {
    params = _params;
}

void ModifierDefinitionNode::set_body(const ASTNodePtr& _body) {
    body = _body;
}



std::string ModifierInvocationNode::get_name() const {
    return name;
}

void ModifierInvocationNode::set_name(const std::string& _name) {
    name = _name;
}

void ModifierInvocationNode::add_argument(const ASTNodePtr& _node) {
    append_sub_node(_node);
}

void ModifierInvocationNode::delete_argument(const unsigned int& x) {
    delete_sub_node(x);
}

void ModifierInvocationNode::update_argument(const unsigned int& x, const ASTNodePtr& _node) {
    update_sub_node(x, _node);
}

ASTNodePtr ModifierInvocationNode::get_argument(const unsigned int& x) {
    return get_sub_node(x);
}

size_t ModifierInvocationNode::num_arguments() {
    return size();
}

ASTNodePtr ModifierInvocationNode::operator[] (const unsigned int& x) {
    return get_sub_node(x);
}



void FunctionDefinitionNode::add_modifier_invocation(const ModifierInvocationNodePtr& _node) {
    modifier_invocation.push_back(_node);
}

void FunctionDefinitionNode::delete_modifier_invocation(const unsigned int& x) {
    modifier_invocation.erase(modifier_invocation.begin() + x);
}

void FunctionDefinitionNode::update_modifier_invocation(const unsigned int& x, const ModifierInvocationNodePtr& _node) {
    modifier_invocation[x] = _node;
}

ModifierInvocationNodePtr FunctionDefinitionNode::get_modifier_invocation(const unsigned int& x) {
    return modifier_invocation[x];
}

size_t FunctionDefinitionNode::num_modifier_invocations() {
    return modifier_invocation.size();
}

void FunctionDefinitionNode::set_name(const std::string& _name) {
    name = _name;
}

void FunctionDefinitionNode::set_qualifier(const std::string& _qualifier) {
    qualifier = _qualifier;
}

void FunctionDefinitionNode::set_params(const ParameterListNodePtr& _params) {
    params = _params;
}

void FunctionDefinitionNode::set_returns(const ParameterListNodePtr& _returns) {
    returns = _returns;
}

void FunctionDefinitionNode::set_function_body(const BlockNodePtr& _function_body) {
    function_body = _function_body;
}

void FunctionDefinitionNode::set_is_constructor(const bool& _is_constructor) {
    is_constructor = _is_constructor;
}

std::string FunctionDefinitionNode::get_name() const {
    return name;
}

std::string FunctionDefinitionNode::get_qualifier() const {
    return qualifier;
}

ParameterListNodePtr FunctionDefinitionNode::get_params() const {
    return params;
}

ParameterListNodePtr FunctionDefinitionNode::get_returns() const {
    return returns;
}

BlockNodePtr FunctionDefinitionNode::get_function_body() const {
    return function_body;
}

bool FunctionDefinitionNode::function_is_constructor() const {
    return is_constructor;
}



void FunctionCallNode::add_argument(const ASTNodePtr& _node) {
    append_sub_node(_node);
}

void FunctionCallNode::delete_argument(const unsigned int& x) {
    delete_sub_node(x);
}

void FunctionCallNode::update_argument(const unsigned int& x, const ASTNodePtr& _node) {
    update_sub_node(x, _node);
}

ASTNodePtr FunctionCallNode::get_argument(const unsigned int& x) {
    return get_sub_node(x);
}

size_t FunctionCallNode::num_arguments() {
    return size();
}

void FunctionCallNode::set_callee(const ASTNodePtr& _callee) {
    callee = _callee;
}

ASTNodePtr FunctionCallNode::get_callee() const {
    return callee;
}



void MemberAccessNode::set_identifier(const ASTNodePtr& _identifier) {
    identifier = _identifier;
}

ASTNodePtr MemberAccessNode::get_identifier() const {
    return identifier;
}

void MemberAccessNode::set_member(const std::string& _member) {
    member = _member;
}

std::string MemberAccessNode::get_member() const {
    return member;
}



std::string ElementaryTypeNameExpressionNode::get_name() const {
    return name;
}

void ElementaryTypeNameExpressionNode::set_name(const std::string& _name) {
    name = _name;
}



void ContractDefinitionNode::add_inherit_from(const std::string& _inherit_from) {
    inherit_from.push_back(_inherit_from);
}

void ContractDefinitionNode::delete_inherit_from(const unsigned int& x) {
    inherit_from.erase(inherit_from.begin() + x);
}

void ContractDefinitionNode::update_inherit_from(const unsigned int& x, const std::string& _inherit_from) {
    inherit_from[x] = _inherit_from;
}

std::string ContractDefinitionNode::get_inherit_from(const unsigned int& x) {
    return inherit_from[x];
}

size_t ContractDefinitionNode::num_inherit_from() const {
    return inherit_from.size();
}

void ContractDefinitionNode::set_as_library() {
    is_library = true;
}

void ContractDefinitionNode::set_as_non_library() {
    is_library = false;
}

bool ContractDefinitionNode::contract_is_library() const {
    return is_library;
}

void ContractDefinitionNode::set_name(const std::string& _name) {
    name = _name;
}

std::string ContractDefinitionNode::get_name() const {
    return name;
}

void ContractDefinitionNode::add_member(const ASTNodePtr& _node) {
    append_sub_node(_node);
}

void ContractDefinitionNode::delete_member(const unsigned int& x) {
    delete_sub_node(x);
}

void ContractDefinitionNode::update_member(const unsigned int& x, const ASTNodePtr& _node) {
    update_sub_node(x, _node);
}

ASTNodePtr ContractDefinitionNode::get_member(const unsigned int& x) {
    return get_sub_node(x);
}

size_t ContractDefinitionNode::num_members() {
    return size();
}

ASTNodePtr ContractDefinitionNode::operator[] (const unsigned int& x) {
    return get_sub_node(x);
}



void IfStatementNode::set_condition(const ASTNodePtr& _condition){
    condition = _condition;
}

ASTNodePtr IfStatementNode::get_condition() const{
    return condition;
}

void IfStatementNode::set_then(const ASTNodePtr& _then){
    if_then = _then;
}

ASTNodePtr IfStatementNode::get_then() const{
    return if_then;
}

void IfStatementNode::set_else(const ASTNodePtr& _else){
    if_else = _else;
}

ASTNodePtr IfStatementNode::get_else() const{
    return if_else;
}


void DoWhileStatementNode::set_condition(const ASTNodePtr& _condition){
    condition = _condition;
}

ASTNodePtr DoWhileStatementNode::get_condition() const{
    return condition;    
}

void DoWhileStatementNode::set_loop_body(const ASTNodePtr& _loop_body){
    loop_body = _loop_body;
}

ASTNodePtr DoWhileStatementNode::get_loop_body() const{
    return loop_body;
}



void WhileStatementNode::set_condition(const ASTNodePtr& _condition){
    condition = _condition;
}

ASTNodePtr WhileStatementNode::get_condition() const{
    return condition;    
}

void WhileStatementNode::set_loop_body(const ASTNodePtr& _loop_body){
    loop_body = _loop_body;
}

ASTNodePtr WhileStatementNode::get_loop_body() const{
    return loop_body;
}



ASTNodePtr ForStatementNode::get_init() const{
    return init;
}

ASTNodePtr ForStatementNode::get_condition() const{
    return condition;
}

ASTNodePtr ForStatementNode::get_increment() const{
    return increment;
}

ASTNodePtr ForStatementNode::get_body() const{
    return body;
}

void ForStatementNode::set_init(const ASTNodePtr& _init){
    init = _init;
}

void ForStatementNode::set_condition(const ASTNodePtr& _condition){
    condition = _condition;
}

void ForStatementNode::set_increment(const ASTNodePtr& _increment){
    increment = _increment;
}

void ForStatementNode::set_body(const ASTNodePtr& _body){
    body = _body;
}



ASTNodePtr ConditionalNode::get_condition() const{
    return condition;
}

ASTNodePtr ConditionalNode::get_yes() const{
    return yes;
}

ASTNodePtr ConditionalNode::get_no() const{
    return no;
}

void ConditionalNode::set_condition(const ASTNodePtr& _condition){
    condition = _condition;
}

void ConditionalNode::set_yes(const ASTNodePtr& _yes){
    yes = _yes;
}

void ConditionalNode::set_no(const ASTNodePtr& _no){
    no = _no;
}



std::string AssignmentNode::get_operator() const {
    return op;
}

void AssignmentNode::set_operator(const std::string& _operator) {
    op = _operator;
}

ASTNodePtr AssignmentNode::get_left_hand_operand() const {
    return left_hand_operand;    
}

ASTNodePtr AssignmentNode::get_right_hand_operand() const {
    return right_hand_operand;
}

void AssignmentNode::set_left_hand_operand(const ASTNodePtr& _operand) {
    left_hand_operand = _operand;
}

void AssignmentNode::set_right_hand_operand(const ASTNodePtr& _operand) {
    right_hand_operand = _operand;
}



void NewExpresionNode::set_type_name(const ASTNodePtr& _type_name){
    type_name = _type_name;
}

ASTNodePtr NewExpresionNode::get_type_name() const{
    return type_name;
}


void EnumDefinitionNode::add_member(const ASTNodePtr& _node) {
    append_sub_node(_node);
}

void EnumDefinitionNode::delete_member(const unsigned int& x) {
    delete_sub_node(x);
}

void EnumDefinitionNode::update_member(const unsigned int& x, const ASTNodePtr& _node) {
    update_sub_node(x, _node);
}

ASTNodePtr EnumDefinitionNode::get_member(const unsigned int& x) {
    return get_sub_node(x);
}

size_t EnumDefinitionNode::num_members() {
    return size();
}

void EnumDefinitionNode::set_name(const std::string& _name) {
    name = _name;
}

std::string EnumDefinitionNode::get_name() const {
    return name;
}



std::string EnumValueNode::get_name() const {
    return name;
}

void EnumValueNode::set_name(const std::string& _name) {
    name = _name;
}


std::string PlaceHolderStatement::get_placeholder() const {
    return placeholder;
}

void PlaceHolderStatement::set_placeholder(const std::string& _placeholder) {
    placeholder = _placeholder;
}


ASTNodePtr MappingNode::get_key_type() const{
    return key_type;
}

ASTNodePtr MappingNode::get_value_type() const{
    return value_type;
}

void MappingNode::set_key_type(const ASTNodePtr& _key_type){
    key_type = _key_type;
}

void MappingNode::set_value_type(const ASTNodePtr& _value_type){
    value_type = _value_type;
}


void ElementaryTypeNameNode::set_type_name(const std::string& _type_name){
    type_name = _type_name;
}

std::string ElementaryTypeNameNode::get_type_name() const{
    return type_name;
}


void UserDefinedTypeNameNode::set_type_name(const std::string& _type_name){
    type_name = _type_name;
}

std::string UserDefinedTypeNameNode::get_type_name() const{
    return type_name;
}


ASTNodePtr FunctionTypeNameNode::get_params() const{
    return params;
}

ASTNodePtr FunctionTypeNameNode::get_returns() const{
    return returns;
}

void FunctionTypeNameNode::set_params(const ASTNodePtr& _params){
    params = _params;
}

void FunctionTypeNameNode::set_returns(const ASTNodePtr& _returns){
    returns = _returns;
}


ASTNodePtr ArrayTypeNameNode::get_base_type() const{
    return base_type;
}

ASTNodePtr ArrayTypeNameNode::get_size() const{
    return size;
}

void ArrayTypeNameNode::set_base_type(const ASTNodePtr& _base_type){
    base_type = _base_type;
}

void ArrayTypeNameNode::set_size(const ASTNodePtr& _size){
    size = _size;
}


void InlineAssemblyNode::set_source(std::string& _source) {
    source = _source;
    source = source.substr(0, source.find_last_of('}')+1);
}

std::string InlineAssemblyNode::get_source() {
    return source;
}

}