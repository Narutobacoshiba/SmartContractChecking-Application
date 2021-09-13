#ifndef SOL2CPN_TRANSLATOR_H_
#define SOL2CPN_TRANSLATOR_H_

#include "Helena.hpp"
#include "nlohmann/json.hpp"
#include "ASTNodes.hpp"
#include <set>

namespace SOL2CPN {

const string PlusSign = "+";
const string MinusSign = "-";
const string DividerSign = "/";
const string MultiplySign = "*";
const string EqualSign = "=";
const string DoublePlussSign = "++";
const string DoubleMinusSign = "--";
const string DividerAndEqualSign = "/=";
const string PlusAndEqualSign = "+=";
const string MinusAndEqualSign = "-=";
const string MultiplyAndEqualSign = "*=";
const string GreaterSign = ">";
const string LessSign = "<";
const string GreaterOrEqualSign = ">=";
const string LessOrEqualSign = "<=";
const string NotSign = "!";
const string AndSign = "&&";
const string OrSign = "||";
const string NotEqualSign = "!=";
const string DoubleEqualSign = "==";

class SubNetNode{
public:
    int count;

    void set_name(const std::string& _name);
    std::string get_name() const;
    
    void set_in_places(const std::vector<PlaceNodePtr> _places);
    PlaceNodePtr get_in_places(const unsigned int& x);
    size_t num_in_places();

    void add_in_place(const PlaceNodePtr& _place);
    PlaceNodePtr get_in_place_by_name(const string& _name);
    PlaceNodePtr get_in_place_by_domain(const string& _domain);

    void add_tempdata_place(const PlaceNodePtr& _place, const std::string& _name );
    void remove_tempdata_place_bye_name(const string& _name);
    PlaceNodePtr get_place_tempdata_by_name(const string& _name);
    
    void set_wft_transition(const TransitionNodePtr& _trans);
    TransitionNodePtr get_wft_transition();

private:
    std::string name;
    TransitionNodePtr wait_for_let_transition;
    std::vector<PlaceNodePtr> in_places;
    std::map<std::string,PlaceNodePtr> wait_places;
    std::map<std::string,PlaceNodePtr> tempdata_places;
};
typedef std::shared_ptr<SubNetNode> SubNetNodePtr;

class Translator {
public:
    Translator(RootNodePtr _rootNode) : rootNode(_rootNode) {}
    NetNodePtr translate();
    

private:
    RootNodePtr rootNode;
    NetNodePtr net;

    bool is_in_function;
    SubNetNodePtr current_subnet;

    void generatePredefinedColors();
    void createInTransition(FunctionDefinitionNodePtr func);
    StructColorNodePtr translateStruct(StructDefinitionNodePtr struct_node);
    ListColorNodePtr translateMapping(ASTNodePtr _node);
    ListColorNodePtr translateArray(ArrayTypeNameNodePtr array_node);
    void generateFunctionColor(FunctionDefinitionNodePtr func);
    void createParFuncPlace(FunctionDefinitionNodePtr func);
    void translateBlock(BlockNodePtr block);
    void translateForStatement(ForStatementNodePtr forStatement);
    void translateExpressionStatement(ExpressionStatementNodePtr statement);
    void translateVariableDeclarationStatement(VariableDeclarationStatementNodePtr statement);
    void translateVariableDeclaration(ASTNodePtr _var);
    void translate_equivalent_node(ASTNodePtr _node);
    void translateFunctionCall(FunctionCallNodePtr func_call);
    void translateRequireFunctionCall(ASTNodePtr _arg);
    void translateIfStatement(IfStatementNodePtr statement);
    void translateAssignment(AssignmentNodePtr assignment);
    void translateSpecificFunctionCall(std::string func_name, ASTNodePtr identifier, FunctionCallNodePtr func_call);
    void translateTransferFunctionCall(ASTNodePtr identifier, ASTNodePtr argument);
    void translatePushFunctionCall(ASTNodePtr identifier, ASTNodePtr argument);
    void generateKeccak256();
    std::string translateUnknowExpressionToString(std::string _value);
    std::string translateRequireExpressionToString(ASTNodePtr _arg);
    std::string translateMemberAcess(std::string _member);
    std::string translateOperator(std::string _operator, std::string member);
    FunctionNodePtr createGetMappingIndexFunction(std::string name, std::vector<ParamNodePtr> params);
    bool translateUnknowFunction(std::string func_name);

    std::map<std::string,std::string> DataTypeRange{
        {"uint","range 0 .. 1000"},
        {"uint8","range 0 .. 10"},
        {"bytes32","range 0 .. 1000"},
        {"address","range 0 .. 100"}
    };

    std::map<std::string, std::string> NormalSign = {
        {PlusSign,"+"},
        {MinusSign,"-"},
        {DividerSign,"/"},
        {MultiplySign,"*"},
        {EqualSign,":="},
        {DoubleEqualSign,"="},
        {GreaterSign,">"},
        {LessSign,"<"},
        {GreaterOrEqualSign,">="},
        {LessOrEqualSign,"<="},
        {NotSign,"not"},
        {AndSign,"and"},
        {OrSign,"or"},
        {NotEqualSign,"!="}
    };

    std::vector<std::string> SpecialSign = {
        DoublePlussSign,
        DoubleMinusSign,
        DividerAndEqualSign,
        PlusAndEqualSign,
        MinusAndEqualSign,
        MultiplyAndEqualSign
    };

    bool isNormalSign(std::string sign);
    bool isSpecialSign(std::string sign);

};

}

#endif //SOL2CPN_TRANSLATOR_H_