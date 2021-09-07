#ifndef SOL2CPN_TRANSLATOR_H_
#define SOL2CPN_TRANSLATOR_H_

#include "Helena.hpp"
#include "nlohmann/json.hpp"
#include "ASTNodes.hpp"
#include <set>

namespace SOL2CPN {

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

    void generatePredefinedColors();
    bool is_in_function;
    SubNetNodePtr current_subnet;

    StructColorNodePtr translateStruct(StructDefinitionNodePtr struct_node);
    ListColorNodePtr translateMapping(ASTNodePtr _node);
    ListColorNodePtr translateArray(ArrayTypeNameNodePtr array_node);
    void generateFunctionColor(FunctionDefinitionNodePtr func);
    PlaceNodePtr createParFuncPlace(std::string func_name);
    void translateBlock(BlockNodePtr block);
    void translateForStatement(ForStatementNodePtr forStatement);
    void translateExpressionStatement(ExpressionStatementNodePtr statement);
    void translateVariableDeclarationStatement(VariableDeclarationStatementNodePtr statement);
    void translateVariableDeclaration(ASTNodePtr _var);
    void translate_value_equivalent_node(ASTNodePtr _node);
    void translateFunctionCall(FunctionCallNodePtr func_call);
    void translateRequireFunctionCall(ASTNodePtr _arg);
    void translateIfStatement(IfStatementNodePtr statement);
    void translateAssignment(AssignmentNodePtr assignment);
    std::string translateRequireExpressionToString(ASTNodePtr _arg);
    std::string translateMemberAcess(std::string _member);
    std::string translateOperator(std::string _operator);
    FunctionNodePtr createGetMappingIndexFunction(std::string name, std::vector<ParamNodePtr> params);
    
    std::map<std::string,std::string> DataTypeRange{
        {"uint","range 0 .. (int'last)"},
        {"uint8","range 0 .. 10"},
        {"bytes32","range 0 .. 1000"},
        {"address","range 0 .. 100"}
    };
};

}

#endif //SOL2CPN_TRANSLATOR_H_