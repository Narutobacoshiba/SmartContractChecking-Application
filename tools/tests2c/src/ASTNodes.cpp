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


/* ------- ContractDefinitionNode ------- */
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

/* ------- VariableDeclarationNode ------- */
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

/* ------- StructDefinitionNode ------- */
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


/* ------- ElementaryTypeNameNode ------- */
void ElementaryTypeNameNode::set_type_name(const std::string& _type_name){
    type_name = _type_name;
}

std::string ElementaryTypeNameNode::get_type_name() const{
    return type_name;
}


/* ------- UserDefinedTypeNameNode ------- */
void UserDefinedTypeNameNode::set_type_name(const std::string& _type_name){
    type_name = _type_name;
}

std::string UserDefinedTypeNameNode::get_type_name() const{
    return type_name;
}

/* ------- FunctionTypeNameNode ------- */
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


/* ------- ArrayTypeNameNode ------- */
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

/* ------- ParameterListNode ------- */
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

/* ------- MappingNode ------- */
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


/* ------- BlockNode ------- */
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


/* ------- ReturnNode ------- */
ASTNodePtr ReturnNode::get_operand() const {
    return operand;
}

void ReturnNode::set_operand(const ASTNodePtr& _operand) {
    operand = _operand;
}


/* ------- ModifierDefinitionNode ------- */
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



/* ------- ModifierInvocationNode ------- */
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


/* ------- FunctionDefinitionNode ------- */
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

/* ------- VariableDeclarationStatementNode ------- */
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

}