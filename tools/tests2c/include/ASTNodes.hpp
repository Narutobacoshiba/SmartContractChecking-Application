#ifndef SOL2CPN_ASTNODES_H_
#define SOL2CPN_ASTNODES_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace SOL2CPN {
const std::string TokenSourceUnit = "SourceUnit";
const std::string TokenPragmaDirective = "PragmaDirective";
const std::string TokenImportDirective = "ImportDirective";
const std::string TokenContractDefinition = "ContractDefinition";
const std::string TokenInheritanceSpecifier = "InheritanceSpecifier";
const std::string TokenUsingForDirective = "UsingForDirective";
const std::string TokenStructDefinition = "StructDefinition";
const std::string TokenEnumDefinition = "EnumDefinition";
const std::string TokenEnumValue = "EnumValue";
const std::string TokenParameterList = "ParameterList";
const std::string TokenFunctionDefinition = "FunctionDefinition";
const std::string TokenVariableDeclaration = "VariableDeclaration";
const std::string TokenModifierDefinition = "ModifierDefinition";
const std::string TokenModifierInvocation = "ModifierInvocation";
const std::string TokenEventDefinition = "EventDefinition";
const std::string TokenElementaryTypeName = "ElementaryTypeName";
const std::string TokenUserDefinedTypeName = "UserDefinedTypeName";
const std::string TokenFunctionTypeName = "FunctionTypeName";
const std::string TokenMapping = "Mapping";
const std::string TokenArrayTypeName = "ArrayTypeName";
const std::string TokenInlineAssembly = "InlineAssembly";
const std::string TokenBlock = "Block";
const std::string TokenPlaceholderStatement = "PlaceholderStatement";
const std::string TokenIfStatement = "IfStatement";
const std::string TokenDoWhileStatement = "DoWhileStatement";
const std::string TokenWhileStatement = "WhileStatement";
const std::string TokenForStatement = "ForStatement";
const std::string TokenContinue = "Continue";
const std::string TokenBreak = "Break";
const std::string TokenReturn = "Return";
const std::string TokenThrow = "Throw";
const std::string TokenEmitStatement = "EmitStatement";
const std::string TokenVariableDeclarationStatement = "VariableDeclarationStatement";
const std::string TokenExpressionStatement = "ExpressionStatement";
const std::string TokenConditional = "Conditional";
const std::string TokenAssignment = "Assignment";
const std::string TokenTupleExpression = "TupleExpression";
const std::string TokenUnaryOperation = "UnaryOperation";
const std::string TokenBinaryOperation = "BinaryOperation";
const std::string TokenFunctionCall = "FunctionCall";
const std::string TokenNewExpression = "NewExpression";
const std::string TokenMemberAccess = "MemberAccess";
const std::string TokenIndexAccess = "IndexAccess";
const std::string TokenIdentifier = "Identifier";
const std::string TokenElementaryTypeNameExpression = "ElementaryTypeNameExpression";
const std::string TokenLiteral = "Literal,";
const std::string TokenLiterals = "Literals";
const std::string TokenSource = "Source:";
const std::string TokenType = "Type:";

const std::list<std::string> TokenList{
    TokenSourceUnit,
    TokenPragmaDirective,
    TokenImportDirective,
    TokenContractDefinition,
    TokenInheritanceSpecifier,
    TokenUsingForDirective,
    TokenStructDefinition,
    TokenEnumDefinition,
    TokenEnumValue,
    TokenParameterList,
    TokenFunctionDefinition,
    TokenVariableDeclaration,
    TokenModifierDefinition,
    TokenModifierInvocation,
    TokenEventDefinition,
    TokenElementaryTypeName,
    TokenUserDefinedTypeName,
    TokenFunctionTypeName,
    TokenMapping,
    TokenArrayTypeName,
    TokenInlineAssembly,
    TokenBlock,
    TokenPlaceholderStatement,
    TokenIfStatement,
    TokenDoWhileStatement,
    TokenWhileStatement,
    TokenForStatement,
    TokenContinue,
    TokenBreak,
    TokenReturn,
    TokenThrow,
    TokenEmitStatement,
    TokenVariableDeclarationStatement,
    TokenExpressionStatement,
    TokenConditional,
    TokenAssignment,
    TokenTupleExpression,
    TokenUnaryOperation,
    TokenBinaryOperation,
    TokenFunctionCall,
    TokenNewExpression,
    TokenMemberAccess,
    TokenIndexAccess,
    TokenIdentifier,
    TokenElementaryTypeNameExpression,
    TokenLiteral,
    TokenLiterals,
    //TokenSource,
    //TokenType
};

const std::list<std::string> ExpressionTokenList{
    TokenConditional,
    TokenAssignment,
    TokenTupleExpression,
    TokenUnaryOperation,
    TokenBinaryOperation,
    TokenFunctionCall,
    TokenNewExpression,
    TokenMemberAccess,
    TokenIndexAccess,
    TokenIdentifier,
    TokenElementaryTypeNameExpression,
    TokenLiteral
};

const std::list<std::string> StatementTokenList{
    TokenBlock,
    TokenPlaceholderStatement,
    TokenIfStatement,
    TokenDoWhileStatement,
    TokenWhileStatement,
    TokenForStatement,
    TokenContinue,
    TokenBreak,
    TokenReturn,
    TokenThrow,
    TokenEmitStatement,
    TokenVariableDeclarationStatement,
    TokenExpressionStatement,
    TokenInlineAssembly
};

enum NodeType {
    NodeTypeSourceUnit,
    NodeTypeRoot,
    NodeTypePragmaDirective,
    NodeTypeImportDirective,
    NodeTypeUsingForDirective,
    NodeTypeVariableDeclaration,
    NodeTypeStructDefinition,
    NodeTypeParameterList,
    NodeTypeEventDefinition,
    NodeTypeBlockNode,
    NodeTypeFunctionDefinition,
    NodeTypeContractDefinition,
    NodeTypeFunctionCall,
    NodeTypeEnumDefinition,
    NodeTypeEnumValue,
    NodeTypeModifierDefinition,
    NodeTypeModifierInvocation,
    NodeTypeMapping,
    NodeTypeInlineAssembly,
    NodeTypePlaceholderStatement,
    NodeTypeIfStatement,
    NodeTypeDoWhileStatement,
    NodeTypeWhileStatement,
    NodeTypeForStatement,
    NodeTypeContinue,
    NodeTypeBreak,
    NodeTypeReturn,
    NodeTypeThrow,
    NodeTypeEmitStatement,
    NodeTypeVariableDeclarationStatement,
    NodeTypeExpressionStatement,
    NodeTypeConditional,
    NodeTypeAssignment,
    NodeTypeTupleExpression,
    NodeTypeUnaryOperation,
    NodeTypeBinaryOperation,
    NodeTypeNewExpression,
    NodeTypeMemberAccess,
    NodeTypeIndexAccess,
    NodeTypeIdentifier,
    NodeTypeElementaryTypeNameExpression,
    NodeTypeLiteral,
    NodeTypeElementaryTypeName,
    NodeTypeUserDefinedTypeName,
    NodeTypeFunctionTypeName,
    NodeTypeArrayTypeName
};
typedef std::vector<std::string> Literals;

class Indentation {
public:
    Indentation() : tab_width(4), use_spaces(true), current_tab_width(0) {}
    explicit Indentation(const int& _tab_width) : tab_width(_tab_width), use_spaces(true), current_tab_width(0) {}
    Indentation(const int& _tab_width, const bool& _use_spaces) : tab_width(_tab_width), use_spaces(_use_spaces), current_tab_width(0) {}
    Indentation(const int& _tab_width, const bool& _use_spaces, const int& _current_tab_width) : tab_width(_tab_width), use_spaces(_use_spaces), current_tab_width(_current_tab_width) {}
    Indentation(const Indentation& _indentation);
    std::string str() const;
    Indentation& operator++();
    Indentation operator++(int);
    Indentation& operator--();
    Indentation operator--(int);
    Indentation& operator=(const Indentation& _indentation );
private:
    int tab_width;
    bool use_spaces;
    int current_tab_width;
};
typedef std::shared_ptr<Indentation> IndentationPtr;

std::ostream& operator<<(std::ostream& _os, const Indentation& _indentation);
std::string operator+(const std::string& _str, const Indentation& _indentation);
std::string operator+(const Indentation& _indentation, const std::string& _str);

class ASTNode;
typedef std::shared_ptr<ASTNode> ASTNodePtr;

class ASTNode {
public:
    explicit ASTNode(NodeType _node_type) : node_type(_node_type){}
    NodeType get_node_type() const;
    size_t size();

protected:
    void append_sub_node(const ASTNodePtr& _node);
    void delete_sub_node(const unsigned int& x);
    void update_sub_node(const unsigned int& x, const ASTNodePtr _node);
    ASTNodePtr get_sub_node(const unsigned int& x) const;
    ASTNodePtr operator[] (const unsigned int& x);


    NodeType node_type;
    std::vector<ASTNodePtr> ast_nodes;
};

class RootNode : public ASTNode {
public:
    RootNode() : ASTNode(NodeTypeRoot) {}

    void add_field(const ASTNodePtr& _node);
    void delete_field(const unsigned int& x);
    void update_field(const unsigned int& x, const ASTNodePtr& _node);
    ASTNodePtr get_field(const unsigned int& x);
    size_t num_fields();
    ASTNodePtr operator[] (const unsigned int& x);

};
typedef std::shared_ptr<RootNode> RootNodePtr;


class ContractDefinitionNode : public ASTNode {
public:
    explicit ContractDefinitionNode(std::string& _name) : ASTNode(NodeTypeContractDefinition), name(_name), inherit_from{}, is_library(false) {}
    void add_inherit_from(const std::string& _inherit_from);
    void delete_inherit_from(const unsigned int& x);
    void update_inherit_from(const unsigned int& x, const std::string& _inherit_from);
    std::string get_inherit_from(const unsigned int& x);
    size_t num_inherit_from() const;
    void set_as_library();
    void set_as_non_library();
    bool contract_is_library() const;
    void set_name(const std::string& _name);
    std::string get_name() const; 
    void add_member(const ASTNodePtr& _node);
    void delete_member(const unsigned int& x);
    void update_member(const unsigned int& x, const ASTNodePtr& _node);
    ASTNodePtr get_member(const unsigned int& x);
    size_t num_members();
    ASTNodePtr operator[] (const unsigned int& x);
private:
    std::string name;
    std::vector<std::string> inherit_from;
    bool is_library;
};
typedef std::shared_ptr<ContractDefinitionNode> ContractDefinitionNodePtr;

class VariableDeclarationNode : public ASTNode {
public:
    VariableDeclarationNode() : ASTNode(NodeTypeVariableDeclaration), type(nullptr), initial_value(nullptr) {}
    VariableDeclarationNode(const ASTNodePtr& _type, std::string& _variable_name, std::string& _type_str) : ASTNode(NodeTypeVariableDeclaration), type(_type), variable_name(_variable_name), type_str(_type_str), initial_value(nullptr) {}
    void set_type(const ASTNodePtr& _type);
    void set_variable_name(const std::string& _variable_name);
    void set_initial_value(const ASTNodePtr& _initial_value);
    ASTNodePtr get_type();
    std::string get_variable_name();
    ASTNodePtr get_initial_value();
    std::string get_type_str();
    void set_type_str(const std::string& _type_str);
private:
    ASTNodePtr type;
    std::string variable_name;
    ASTNodePtr initial_value;
    std::string type_str;
};
typedef std::shared_ptr<VariableDeclarationNode> VariableDeclarationNodePtr;


class StructDefinitionNode : public ASTNode {
public:
    explicit StructDefinitionNode(const std::string& _name) : ASTNode(NodeTypeStructDefinition), name(_name) {};
    std::string get_name() const;
    void set_name(const std::string& _name);
    void add_field(const ASTNodePtr& _node);
    void delete_field(const unsigned int& x);
    void update_field(const unsigned int& x, const ASTNodePtr& _node);
    ASTNodePtr get_field(const unsigned int& x);
    size_t num_fields();
    ASTNodePtr operator[] (const unsigned int& x);
private:
    std::string name;
};
typedef std::shared_ptr<StructDefinitionNode> StructDefinitionNodePtr;



class ElementaryTypeNameNode : public ASTNode {
public:
    explicit ElementaryTypeNameNode(const std::string& _type_name) : ASTNode(NodeTypeElementaryTypeName), type_name(_type_name) {}
    void set_type_name(const std::string& _type_name);
    std::string get_type_name() const;
private:
    std::string type_name;
};
typedef std::shared_ptr<ElementaryTypeNameNode> ElementaryTypeNameNodePtr;



class UserDefinedTypeNameNode : public ASTNode {
public:
    explicit UserDefinedTypeNameNode(const std::string& _type_name) : ASTNode(NodeTypeUserDefinedTypeName), type_name(_type_name) {}
    void set_type_name(const std::string& _type_name);
    std::string get_type_name() const;
private:
    std::string type_name;
};
typedef std::shared_ptr<UserDefinedTypeNameNode> UserDefinedTypeNameNodePtr;



class FunctionTypeNameNode : public ASTNode {
public:
    FunctionTypeNameNode(ASTNodePtr _params, ASTNodePtr _returns) : ASTNode(NodeTypeFunctionTypeName), params(_params), returns(_returns) {}
    ASTNodePtr get_params() const;
    ASTNodePtr get_returns() const;
    void set_params(const ASTNodePtr& _params);
    void set_returns(const ASTNodePtr& _returns);
private:
    ASTNodePtr params;
    ASTNodePtr returns;
};
typedef std::shared_ptr<FunctionTypeNameNode> FunctionTypeNameNodePtr;



class ArrayTypeNameNode : public ASTNode {
public:
    ArrayTypeNameNode(ASTNodePtr _base_type, ASTNodePtr _size) : ASTNode(NodeTypeArrayTypeName), base_type(_base_type), size(_size) {}
    ASTNodePtr get_base_type() const;
    ASTNodePtr get_size() const;
    void set_base_type(const ASTNodePtr& _base_type);
    void set_size(const ASTNodePtr& _size);
private:
    ASTNodePtr base_type;
    ASTNodePtr size;
};
typedef std::shared_ptr<ArrayTypeNameNode> ArrayTypeNameNodePtr;

class ParameterListNode : public ASTNode {
public:
    ParameterListNode() : ASTNode(NodeTypeParameterList) {};
    void add_parameter(const ASTNodePtr& _node);
    void delete_parameter(const unsigned int& x);
    void update_parameter(const unsigned int& x, const ASTNodePtr& _node);
    ASTNodePtr get_parameter(const unsigned int& x);
    size_t num_parameters();
    ASTNodePtr operator[] (const unsigned int& x);

    
};
typedef std::shared_ptr<ParameterListNode> ParameterListNodePtr;



class MappingNode : public ASTNode {
public:
    MappingNode(ASTNodePtr _key_type, ASTNodePtr _value_type) : ASTNode(NodeTypeMapping), key_type(_key_type), value_type(_value_type) {}
    ASTNodePtr get_key_type() const;
    ASTNodePtr get_value_type() const;
    void set_key_type(const ASTNodePtr& _key_type);
    void set_value_type(const ASTNodePtr& _value_type);
private:
    ASTNodePtr key_type;
    ASTNodePtr value_type;
};
typedef std::shared_ptr<MappingNode> MappingNodePtr;


class BlockNode : public ASTNode {
public:
    BlockNode() : ASTNode(NodeTypeBlockNode) {}
    void add_statement(const ASTNodePtr& _node);
    void delete_statement(const unsigned int& x);
    void update_statement(const unsigned int& x, const ASTNodePtr& _node);
    ASTNodePtr get_statement(const unsigned int& x);
    size_t num_statements();
    ASTNodePtr operator[] (const unsigned int& x);
private:
};
typedef std::shared_ptr<BlockNode> BlockNodePtr;

class ReturnNode : public ASTNode {
public:
    ReturnNode() : ASTNode(NodeTypeReturn) {}
    explicit ReturnNode(ASTNodePtr _operand) : ASTNode(NodeTypeReturn), operand(_operand) {}
    ASTNodePtr get_operand() const;
    void set_operand(const ASTNodePtr& _operand);
private:
    ASTNodePtr operand;
};
typedef std::shared_ptr<ReturnNode> ReturnNodePtr;



class ModifierDefinitionNode : public ASTNode {
public:
    ModifierDefinitionNode() : ASTNode(NodeTypeModifierDefinition), params(nullptr) {}
    ModifierDefinitionNode(std::string& _name, ParameterListNodePtr _params, ASTNodePtr _body) : ASTNode(NodeTypeModifierDefinition), name(_name), params(_params), body(_body) {}
    std::string get_name() const;
    ParameterListNodePtr get_params() const;
    ASTNodePtr get_body() const;
    void set_name(const std::string& _name);
    void set_params(const ParameterListNodePtr& _params);
    void set_body(const ASTNodePtr& _body);
private:
    std::string name;
    ParameterListNodePtr params;
    ASTNodePtr body;
};
typedef std::shared_ptr<ModifierDefinitionNode> ModifierDefinitionNodePtr;



class ModifierInvocationNode : public ASTNode {
public:
    ModifierInvocationNode() : ASTNode(NodeTypeModifierInvocation) {}
    explicit ModifierInvocationNode(const std::string& _name) : ASTNode(NodeTypeModifierInvocation), name(_name) {}
    void add_argument(const ASTNodePtr& _node);
    void delete_argument(const unsigned int& x);
    void update_argument(const unsigned int& x, const ASTNodePtr& _node);
    ASTNodePtr get_argument(const unsigned int& x);
    size_t num_arguments();
    ASTNodePtr operator[] (const unsigned int& x);
    std::string get_name() const;
    void set_name(const std::string& _name);
private:
    std::string name;
};
typedef std::shared_ptr<ModifierInvocationNode> ModifierInvocationNodePtr;



class FunctionDefinitionNode : public ASTNode {
public:
    FunctionDefinitionNode() : ASTNode(NodeTypeFunctionDefinition), is_constructor(false) {};
    FunctionDefinitionNode(std::string& _name, std::string& _qualifier, ParameterListNodePtr _params, ParameterListNodePtr _returns, BlockNodePtr _function_body) : ASTNode(NodeTypeFunctionDefinition), name(_name), qualifier(_qualifier), params(_params), returns(_returns), function_body(_function_body), is_constructor(false) {}
    void add_modifier_invocation(const ModifierInvocationNodePtr& _node);
    void delete_modifier_invocation(const unsigned int& x);
    void update_modifier_invocation(const unsigned int& x, const ModifierInvocationNodePtr& _node);
    ModifierInvocationNodePtr get_modifier_invocation(const unsigned int& x);
    size_t num_modifier_invocations();
    void set_name(const std::string& _name);
    void set_qualifier(const std::string& _qualifier);
    void set_params(const ParameterListNodePtr& _params);
    void set_returns(const ParameterListNodePtr& _returns);
    void set_function_body(const BlockNodePtr& _function_body);
    void set_is_constructor(const bool& _is_constructor);
    std::string get_name() const;
    std::string get_qualifier() const;
    ParameterListNodePtr get_params() const;
    ParameterListNodePtr get_returns() const;
    BlockNodePtr get_function_body() const;
    bool function_is_constructor() const;
private:
    std::string name;
    std::string qualifier;
    ParameterListNodePtr params;
    ParameterListNodePtr returns;
    std::vector<ModifierInvocationNodePtr> modifier_invocation;
    BlockNodePtr function_body;
    bool is_constructor;
};
typedef std::shared_ptr<FunctionDefinitionNode> FunctionDefinitionNodePtr;

class VariableDeclarationStatementNode : public ASTNode {
public:
    VariableDeclarationStatementNode() : ASTNode(NodeTypeVariableDeclarationStatement), decl(nullptr), value(nullptr) {}
    VariableDeclarationStatementNode(const VariableDeclarationNodePtr& _decl, const ASTNodePtr& _value) : ASTNode(NodeTypeVariableDeclarationStatement), decl(_decl), value(_value) {}
    VariableDeclarationNodePtr get_decl() const;
    ASTNodePtr get_value() const;
    void set_decl(const VariableDeclarationNodePtr& _decl);
    void set_value(const ASTNodePtr& _value);
private:
    VariableDeclarationNodePtr decl;
    ASTNodePtr value;
};
typedef std::shared_ptr<VariableDeclarationStatementNode> VariableDeclarationStatementNodePtr;

}
#endif