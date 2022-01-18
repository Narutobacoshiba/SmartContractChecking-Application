#ifndef SOL2CPN_TRANSLATOR_H_
#define SOL2CPN_TRANSLATOR_H_

#include "../../include/Helena.hpp"
#include "../../include/nlohmann/json.hpp"
#include "ASTNodes.hpp"
#include <set>

using namespace HELENA;
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

class FunctionNet{
public:
    FunctionNet(std::string _name): name(_name) {}
    std::string get_name();

    void add_color(const ColorNodePtr& _color);
    ColorNodePtr get_color(const unsigned int& x);
    size_t num_colors();

    void add_local_variable(const std::string& _name, const PlaceNodePtr& _place);
    bool is_local_variable(const std::string& _name);
    PlaceNodePtr get_local_variable_by_name(const std::string& _name);

    void set_param_place(const PlaceNodePtr& _place);

    void add_place(const PlaceNodePtr& _place);
    PlaceNodePtr get_place(const unsigned int& x);
    size_t num_places();

    void add_transition(const TransitionNodePtr& _trans);
    TransitionNodePtr get_transition(const unsigned int& x);
    size_t num_transitions();


    PlaceNodePtr generateControlFlowPlace(const std::string& _str);
    std::string generateTransitionName(const std::string& _str);
private:
    std::vector<ColorNodePtr> color_nodes;

    std::vector<PlaceNodePtr> place_nodes;
    std::map<std::string, int> place_node_names;

    std::map<std::string, PlaceNodePtr> local_variables;
    PlaceNodePtr param_place;

    std::vector<TransitionNodePtr> transition_nodes;
    std::map<std::string, int> transition_node_names;

    std::string name;
};
typedef std::shared_ptr<FunctionNet> FunctionNetPtr;

class SmartContractNet{
public:    
    SmartContractNet(std::string _name);

    std::string get_name();

    void add_color(const ColorNodePtr& _color);
    ColorNodePtr get_color(const unsigned int& x);
    ColorNodePtr get_color_by_name(const std::string& _name);
    size_t num_colors();

    void add_state_color(const ColorNodePtr& _color,const std::string& _var_name);
    bool is_state_color(const std::string& _name);
    ColorNodePtr get_state_color_by_name(const string& _name);

    void add_function(const FunctionNetPtr& _func);
    FunctionNetPtr get_function_by_name(const std::string& _func_name);

    void add_function_node(const FunctionNodePtr& _func);
    FunctionNodePtr get_function_node(const unsigned int& x);
    size_t num_function_nodes();

    std::string convertColorInit(const ColorNodePtr& _color);
    std::string source_code();
private:
    std::string name;

    std::vector<ColorNodePtr> default_color_nodes;
    std::vector<ColorNodePtr> color_nodes;
    std::map<std::string, ColorNodePtr> stateColor;
    std::vector<FunctionNodePtr> function_nodes;
    std::vector<FunctionNetPtr> functionNets;
};
typedef std::shared_ptr<SmartContractNet> SmartContractNetPtr;

const std::string PlaceParType = "place_par";
const std::string PlaceStateType = "place_state";
const std::string PlaceStateParType = "place_state_par";
const std::string PlaceVarialeLocalType = "place_local_var";


const std::string VariableGlobalType = "global";
const std::string VariableLocalType = "local";
const std::string VariableNonType = "";

class Translator {
public:
    Translator(RootNodePtr _rootNode) : rootNode(_rootNode) {}
    std::string translate();
    

private:
    RootNodePtr rootNode;
    NetNodePtr net;
    SmartContractNetPtr currentCNet;
    FunctionNetPtr currentFNet;
    std::vector<PlaceNodePtr> in_places;
    std::string in_state_type; 

    std::string getStateInArc();
    std::string getParInArc();
    ArcNodePtr generateStateOutArc();
    ArcNodePtr generateStateParOutArc(const PlaceNodePtr& _place);
    std::string getPlaceTypeInFlow(const PlaceNodePtr _place);
    std::string generateArcInLabel(const PlaceNodePtr& _place,const std::string& _place_type);
    ArcNodePtr generateArcInByPlace(const PlaceNodePtr& _place,const std::string& _place_type);




    StructColorNodePtr translateStruct(const StructDefinitionNodePtr& struct_node);
    ListColorNodePtr translateMapping(const ASTNodePtr& _node);
    ListColorNodePtr translateArray(const ArrayTypeNameNodePtr& array_node);
    PlaceNodePtr translateVariableDeclaration(const ASTNodePtr& _var,const std::string& _type);
    FunctionNodePtr createGetMappingIndexFunction(const std::string& name, const ParamNodePtr& param1, const ParamNodePtr& param2);
    
    void createFunctionColorPlace(const FunctionDefinitionNodePtr& _func);
    void translateBlock(const BlockNodePtr& block);
    void translateExpressionStatement(const ExpressionStatementNodePtr& statement);
    void translate_equivalent_node(const ASTNodePtr& _node);
    void translateFunctionCall(const FunctionCallNodePtr& func_call);
    void translateRequireFunctionCall(const ASTNodePtr& _arg);
    void translateVariableDeclarationStatement(const VariableDeclarationStatementNodePtr& statement);
    void translateIfStatement(const IfStatementNodePtr& statement);
    void translateAssignment(const AssignmentNodePtr& assignment);
    /* void translateTransferFunctionCall(const ASTNodePtr& identifier, const ASTNodePtr& argument);
    void translatePushFunctionCall(const ASTNodePtr& identifier, const ASTNodePtr& argument);
    void translateForStatement(const ForStatementNodePtr& forStatement); */

    std::string translateRequireExpressionToString(const ASTNodePtr& _arg);
    std::string translateOperator(const std::string& _operator, const std::string& member);
    std::string translateMemberToString(const ASTNodePtr& _arg);
    std::string translateMemberAcess(const std::string& _member);
    std::vector<std::string> createChangeValueLet(const std::string& name, const std::string& left_member, const std::string& right_member, const std::string& op);


    std::map<std::string,std::string> DataTypeRange{
        {"UINT","range 0 .. 1000"},
        {"UINT8","range 0 .. 10"},
        {"BYTES32","range 0 .. 1000"},
        {"ADDRESS","range 0 .. 100"},
        {"BOOL","enum(true,false)"},
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