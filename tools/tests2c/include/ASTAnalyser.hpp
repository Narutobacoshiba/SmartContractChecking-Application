#ifndef SOL2CPN_ASTANALYSER_H_
#define SOL2CPN_ASTANALYSER_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "nlohmann/json.hpp"

#include "Utils.hpp"
#include "ASTNodes.hpp"

namespace SOL2CPN {

class ASTAnalyser {
public:
    ASTAnalyser(std::stringstream& _ast_sstream, nlohmann::json& _jsonast, const bool& single_file, const std::string& file_name, const std::string& _visitor_arg);
    RootNodePtr analyse();
    void set_do_not_produce_source(bool _do_not_produce_source = true);

private:
    std::list<std::string> ast_lines;
    std::list<std::string>::iterator ptr_ast_line;
    nlohmann::json ast_json;
    std::vector<ContractDefinitionNodePtr> contracts;
    ContractDefinitionNodePtr current_contract;
    std::string current_contract_name;
    unsigned int num_functions_current_contract;
    std::string visitor_arg;
    bool do_not_produce_source;
    
    VariableDeclarationNodePtr handle_variable_declaration();
    ParameterListNodePtr handle_parameter_list();
    ASTNodePtr get_value_equivalent_node(std::string& token);
    BlockNodePtr handle_block();
    ModifierInvocationNodePtr handle_modifier_invocation();
    VariableDeclarationStatementNodePtr handle_variable_declaration_statament();
    
    void get_next_token(const std::string& token);
    std::string get_next_token();
    void remove_escapes(std::string& _str);
    ASTNodePtr get_type_name(std::string& token);
    std::string get_type_name2(std::string& token);
    int get_current_indentation();

    std::string get_function_qualifier(const std::string& contract_name, const std::string& _function_name, const std::string& _type);
    bool function_is_constructor(const std::string& _contract_name, const std::string& _function_name);
};

}

#endif