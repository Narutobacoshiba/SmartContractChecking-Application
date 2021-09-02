#include <fstream>
#include <list>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/ASTAnalyser.hpp"

namespace SOL2CPN {

ASTAnalyser::ASTAnalyser(std::stringstream& _ast_sstream, nlohmann::json& _jsonast, const bool& single_file, const std::string& file_name, const std::string& _visitor_arg) {
    std::string new_line;
    while (std::getline(_ast_sstream, new_line)) {
        //Utils::trim(new_line);
        if (!new_line.empty()) {
            ast_lines.emplace_back(new_line);
        }
    }

    ast_json = _jsonast;
    ptr_ast_line = ast_lines.begin();
    num_functions_current_contract = 0;
    visitor_arg = _visitor_arg;

    if (single_file) {
        while (Utils::substr_by_edge(*ptr_ast_line, "======= ", " =======") != file_name) {
            ++ptr_ast_line;
        }
    }
    do_not_produce_source = false;
}

void ASTAnalyser::set_do_not_produce_source(bool _do_not_produce_source) {
    do_not_produce_source = _do_not_produce_source;
}

RootNodePtr ASTAnalyser::analyse() {
    std::string line;
    while (ptr_ast_line != ast_lines.end()) {
        std::string keyword = Utils::retrieve_string_element(*ptr_ast_line, 0, " ");

        Utils::debug_info("Contract-level ast line handling: " + *ptr_ast_line);
        if (keyword == TokenContractDefinition ) {
            std::string contract_name = Utils::retrieve_string_element(*ptr_ast_line, 1, " ");
            contract_name = Utils::substr_by_edge(contract_name, "\"", "\"");
            ContractDefinitionNodePtr contract(new ContractDefinitionNode(contract_name));
            contracts.push_back(contract);
            current_contract = contract;
            num_functions_current_contract = 0;
            current_contract_name = contract_name;
            get_next_token(TokenSource);
            line = Utils::substr_by_edge(*ptr_ast_line, "Source: \"", "\"");
            if (line.find("library") != std::string::npos) {
                current_contract->set_as_library();
            }
        }else if (keyword == TokenStructDefinition ) {
            std::string struct_name = Utils::retrieve_string_element(*ptr_ast_line, 1, " ");
            struct_name = Utils::substr_by_edge(struct_name, "\"", "\"");
            StructDefinitionNodePtr struct_node = std::make_shared<StructDefinitionNode>(struct_name);
            int indentation = get_current_indentation();

            while (get_next_token() == TokenVariableDeclaration) {   
                if (get_current_indentation() <= indentation) break;
                auto ast_var_decl = std::static_pointer_cast<ASTNode>(handle_variable_declaration());
                struct_node->add_field(ast_var_decl);
            } 

            auto ast_struct_node = std::static_pointer_cast<ASTNode>(struct_node);
            current_contract->add_member(ast_struct_node);
            continue;

        }else if (keyword == TokenVariableDeclaration ) {
            int indentation = get_current_indentation();
            VariableDeclarationNodePtr var_decl = handle_variable_declaration();
            // it might be initialised a value
            std::string token = get_next_token();
            if (indentation < get_current_indentation()) {
                ASTNodePtr value = get_value_equivalent_node(token);
                var_decl->set_initial_value(value);
            } else {
                --ptr_ast_line;
            }
            current_contract->add_member(var_decl);
        }else if (keyword == TokenFunctionDefinition ) {
            FunctionDefinitionNodePtr function_node = std::make_shared<FunctionDefinitionNode>();
            std::string function_name = Utils::retrieve_string_element(*ptr_ast_line, 1, " ");
            function_name = Utils::substr_by_edge(function_name, "\"", "\"");
            function_node->set_name(function_name);

            std::string qualifier = get_function_qualifier(current_contract_name, function_name, "visibility");
            std::string stateMutability = get_function_qualifier(current_contract_name, function_name, "stateMutability");
            
            if (stateMutability != "nonpayable") {
                qualifier = qualifier + " " + stateMutability;
            }
            function_node->set_qualifier(qualifier);

            bool is_constructor = function_is_constructor(current_contract_name, function_name);
            function_node->set_is_constructor(is_constructor);

            get_next_token(TokenParameterList); 
            ParameterListNodePtr params = handle_parameter_list();
            function_node->set_params(params);

            get_next_token(TokenParameterList);
            ParameterListNodePtr returns = handle_parameter_list();
            function_node->set_returns(returns);

            std::string token = get_next_token();
            ModifierInvocationNodePtr modifier_invocation = nullptr;
            while (token == TokenModifierInvocation) {
                modifier_invocation = handle_modifier_invocation();
                function_node->add_modifier_invocation(modifier_invocation);
                token = get_next_token();
            }            
            BlockNodePtr function_body = nullptr;
            if (token == TokenBlock) {
                function_body = handle_block();
            } else {
                --ptr_ast_line;
            }
            function_node->set_function_body(function_body);
            current_contract->add_member(function_node);

            num_functions_current_contract++;
        }

        if (ptr_ast_line == ast_lines.end()) break;
        ++ptr_ast_line;
    } 
    Utils::debug_info("File processing finished");

    RootNodePtr ast_root = std::make_shared<RootNode>();

    if (!do_not_produce_source) {
        for (auto it_contract = contracts.begin(); it_contract != contracts.end(); ++it_contract) {
            ast_root->add_field(*it_contract);
        }

        Utils::debug_info("New code generated");
    }
    
    return ast_root;
}

void ASTAnalyser::get_next_token(const std::string& token) {
    if (ptr_ast_line == ast_lines.end()) return;
    ++ptr_ast_line;
    while (ptr_ast_line != ast_lines.end()) {
        std::string line = *ptr_ast_line;
        Utils::trim(line);
        if (Utils::retrieve_string_element(line, 0, " ") == token) {
            return;
        }
        ++ptr_ast_line;
    }
}

std::string ASTAnalyser::get_next_token() {
    if (ptr_ast_line == ast_lines.end()) return "";
    ++ptr_ast_line;
    while (ptr_ast_line != ast_lines.end()) {
        std::string line = *ptr_ast_line;
        Utils::trim(line);
        std::string keyword = Utils::retrieve_string_element(line, 0, " ");
        if (std::find(TokenList.begin(), TokenList.end(), keyword) != TokenList.end()) {
            return keyword;
        }
        ++ptr_ast_line;
    }
    return "";
}

void ASTAnalyser::remove_escapes(std::string& _str){
    Utils::str_replace_all(_str, "\\\"", "\"");
    Utils::str_replace_all(_str, "\\\'", "\'");
    Utils::str_replace_all(_str, "\\\\", "\\");
    Utils::str_replace_all(_str, "\\\a", "\"");
    Utils::str_replace_all(_str, "\\\b", "\"");
    Utils::str_replace_all(_str, "\\\f", "\"");
    Utils::str_replace_all(_str, "\\\n", "\"");
    Utils::str_replace_all(_str, "\\\r", "\"");
    Utils::str_replace_all(_str, "\\\t", "\"");
    Utils::str_replace_all(_str, "\\\v", "\"");
}

int ASTAnalyser::get_current_indentation() {
    if (ptr_ast_line == ast_lines.end()) return 0;
    return ptr_ast_line->find_first_not_of(' ');
}

VariableDeclarationNodePtr ASTAnalyser::handle_variable_declaration(){
    // get name from the current token
    std::string variable_name = Utils::substr_by_edge(*ptr_ast_line, TokenVariableDeclaration + " \"", "\"");
    ASTNodePtr type;
    std::string type_str;
    // then try to get type
    std::string next_token = get_next_token();
    type = get_type_name(next_token);
  
    return std::make_shared<VariableDeclarationNode>(type, variable_name, type_str); 
}


ASTNodePtr ASTAnalyser::get_type_name(std::string& token) {
    ASTNodePtr type_name;
    std::string type_str;
    Utils::debug_info("token: " + token);

    if (token == TokenElementaryTypeName) {
        Utils::debug_info("elementary");
        ++ptr_ast_line;
        type_str = Utils::substr_by_edge(*ptr_ast_line, "Source: \"", "\"");
        Utils::debug_info("type:" + type_str);
        type_name = std::make_shared<ElementaryTypeNameNode>(type_str);
    } else if (token == TokenFunctionTypeName) {
        get_next_token(TokenParameterList);
        ParameterListNodePtr parameters = handle_parameter_list();
        get_next_token(TokenParameterList);
        ParameterListNodePtr returns = handle_parameter_list();
        type_name = std::make_shared<FunctionTypeNameNode>(parameters, returns);
    } else if (token == TokenArrayTypeName) {
        std::string array_base_type_token = get_next_token();
        ASTNodePtr base_type_node = get_type_name(array_base_type_token);
        ASTNodePtr index = nullptr;
        //try to find out the index of the array
        int indentation = get_current_indentation();
        std::string next_token = get_next_token();
        if (next_token != "" && indentation < get_current_indentation()) {
            index = get_value_equivalent_node(next_token);
        } else {
            --ptr_ast_line;
        } 
        type_name = std::make_shared<ArrayTypeNameNode>(base_type_node, index);
    } else if (token == TokenUserDefinedTypeName) {
        type_str = Utils::substr_by_edge(*ptr_ast_line, TokenUserDefinedTypeName + " \"", "\"");
        type_name = std::make_shared<UserDefinedTypeNameNode>(type_str);
    } else if (token == TokenMapping) {
        std::string next_token = get_next_token();
        ASTNodePtr key_type = get_type_name(next_token);
        next_token = get_next_token();
        ASTNodePtr value_type = get_type_name(next_token);
        type_name = std::make_shared<MappingNode>(key_type, value_type);
    }
    std::cout<<type_str<<" "<<type_name->get_node_type()<<"\n";
    return type_name;
}

std::string ASTAnalyser::get_type_name2(std::string& token) {
    ASTNodePtr type_name;
    std::string type_str;
                    Utils::debug_info("token: " + token);

    if (token == TokenElementaryTypeName) {
                Utils::debug_info("elementary");
        ++ptr_ast_line;
        type_str = Utils::substr_by_edge(*ptr_ast_line, "Source: \"", "\"");
        Utils::debug_info("type:" + type_str);
        type_name = std::make_shared<ElementaryTypeNameNode>(type_str);
    } else if (token == TokenFunctionTypeName) {
        get_next_token(TokenParameterList);
        ParameterListNodePtr parameters = handle_parameter_list();
        get_next_token(TokenParameterList);
        ParameterListNodePtr returns = handle_parameter_list();
        type_name = std::make_shared<FunctionTypeNameNode>(parameters, returns);
        type_str = "FunctionTypeNode";
    } else if (token == TokenArrayTypeName) {
        std::string array_base_type_token = get_next_token();
        ASTNodePtr base_type_node = get_type_name(array_base_type_token);
        ASTNodePtr index = nullptr;
        //try to find out the index of the array
        int indentation = get_current_indentation();
        std::string next_token = get_next_token();
        if (next_token != "" && indentation < get_current_indentation()) {
            index = get_value_equivalent_node(next_token);
        } else {
            --ptr_ast_line;
        }
        type_str = "array";
        type_name = std::make_shared<ArrayTypeNameNode>(base_type_node, index);
    } else if (token == TokenUserDefinedTypeName) {
        type_str = Utils::substr_by_edge(*ptr_ast_line, TokenUserDefinedTypeName + " \"", "\"");
        type_name = std::make_shared<UserDefinedTypeNameNode>(type_str);
    } else if (token == TokenMapping) {
        std::string next_token = get_next_token();
        ASTNodePtr key_type = get_type_name(next_token);
        next_token = get_next_token();
        ASTNodePtr value_type = get_type_name(next_token);
        type_name = std::make_shared<MappingNode>(key_type, value_type);
        type_str = "mapping";
    }
    return type_str;
}


ParameterListNodePtr ASTAnalyser::handle_parameter_list() {
    ParameterListNodePtr parameters = std::make_shared<ParameterListNode>();
    int indentation = get_current_indentation();
    std::string token = get_next_token();
    while (token == TokenVariableDeclaration && indentation < get_current_indentation()) {
        VariableDeclarationNodePtr var_decl = handle_variable_declaration();
        parameters->add_parameter(var_decl);
        token = get_next_token();
    }
    --ptr_ast_line; // if the token cannot enter while, it is outside the parameter list
    return parameters;
}

ASTNodePtr ASTAnalyser::get_value_equivalent_node(std::string& token){
    ASTNodePtr node;
    /* if (token == TokenBinaryOperation) {
        node = handle_binary_operation();
    } else if (token == TokenLiteral) {
        node = handle_literal();
    } else if (token == TokenTupleExpression) {
        node = handle_tuple_expression();
    } else if (token == TokenUnaryOperation) {
        node = handle_unary_operation();
    } else if (token == TokenIdentifier) {
        node = handle_identifier();
    } else if (token == TokenFunctionCall) {
        node = handle_function_call();
    } else if (token == TokenMemberAccess) {
        node = handle_member_access();
    } else if (token == TokenIndexAccess) {
        node = handle_index_access();
    } else if (token == TokenElementaryTypeNameExpression) {
        node = handle_elementary_type_name_expression();
    } else if (token == TokenConditional) {
        node = handle_conditional();
    } else if (token == TokenAssignment) {
        node = handle_assignment();
    } else if (token == TokenNewExpression) {
        node = handle_new_expression();
    } */
    return node;
}

BlockNodePtr ASTAnalyser::handle_block() {
    int indentation = get_current_indentation();
    std::string token = get_next_token();
    BlockNodePtr block = std::make_shared<BlockNode>();
    while (token != "" && ptr_ast_line != ast_lines.end() && indentation < get_current_indentation()) {
        if (token == TokenVariableDeclarationStatement) {
            VariableDeclarationStatementNodePtr variable_decl_stmt = handle_variable_declaration_statament();
            block->add_statement(variable_decl_stmt);
        }
        /*
        block->append_subnode(get_statement_equivalent_node());
        if (token == TokenExpressionStatement) {
            ExpressionStatementNodePtr expression = handle_expression_statament();
            block->append_subnode(expression);
        } else if (token == TokenEmitStatement) {
            EmitStatementNodePtr emit_stmt = handle_emit_statement();
            block->append_subnode(emit_stmt);
        } else if (token == TokenIfStatement) {
            block->append_subnode(handle_if_statement());
        } else if (token == TokenForStatement) {
            block->append_subnode(handle_for_statement());
        } else if (token == TokenWhileStatement) {
            //block->append_subnode(handle_while_statement());
        } else if (token == TokenDoWhileStatement) {
            //block->append_subnode(handle_do_while_statament());
        } else if (token == TokenVariableDeclarationStatement) {
            VariableDeclarationStatementNodePtr variable_decl_stmt = handle_variable_declaration_statament();
            block->append_subnode(variable_decl_stmt);
        } else if (token == TokenReturn) {
            ReturnNodePtr return_node = handle_return();
            block->append_subnode(return_node);
        }*/
        token = get_next_token();
    }
    --ptr_ast_line;
    return block;
}

ModifierInvocationNodePtr ASTAnalyser::handle_modifier_invocation() {
    std::string modifier_name = Utils::retrieve_string_element(*ptr_ast_line, 1, " ");
    modifier_name = Utils::substr_by_edge(modifier_name, "\"", "\"");
    ModifierInvocationNodePtr modifier_invocation = std::make_shared<ModifierInvocationNode>(modifier_name);
    int indentation = get_current_indentation();
    get_next_token(); // the token right after modifier invocation is an identifier token which is the name of the modifier
    std::string token = get_next_token();
    while (token != "" && indentation < get_current_indentation()) {
        ASTNodePtr subnode = get_value_equivalent_node(token);
        modifier_invocation->add_argument(subnode);
        token = get_next_token();
    }
    --ptr_ast_line;

    return modifier_invocation;
}

VariableDeclarationStatementNodePtr ASTAnalyser::handle_variable_declaration_statament() {
    int indentation = get_current_indentation();
    get_next_token(TokenVariableDeclaration);
    VariableDeclarationNodePtr decl = handle_variable_declaration();
    std::string token = get_next_token();
    VariableDeclarationStatementNodePtr variable_decl_stmt;
    if (indentation < get_current_indentation()) {
        ASTNodePtr value = get_value_equivalent_node(token);
        variable_decl_stmt = std::make_shared<VariableDeclarationStatementNode>(decl, value);
    } else {
        ASTNodePtr value = nullptr;
        variable_decl_stmt = std::make_shared<VariableDeclarationStatementNode>(decl, value);
    }
    --ptr_ast_line;
    return variable_decl_stmt;
}

std::string ASTAnalyser::get_function_qualifier(const std::string& _contract_name, const std::string& _function_name, const std::string& _type) {
    unsigned int num_functions = 0;
    auto root_node = ast_json.at("nodes");
    for (size_t i = 0; i < root_node.size(); ++i) {
        auto contract_node = root_node.at(i);
        if (contract_node.find("name") == contract_node.end()) {
            continue;
        }
        std::string this_contract_name = contract_node.at("name");
        if (this_contract_name == _contract_name) {
            for (size_t j = 0; j < contract_node.at("nodes").size(); ++j) {
                auto sub_node = contract_node.at("nodes").at(j);
                if (sub_node.at("nodeType") == TokenFunctionDefinition) {
                    if (sub_node.at("name") == _function_name && num_functions == num_functions_current_contract) {
                        return sub_node.at(_type);
                    }
                    num_functions++;
                }
            }
        }
    }
    return "";
}

bool ASTAnalyser::function_is_constructor(const std::string& _contract_name, const std::string& _function_name) {
    unsigned int num_functions = 0;
    auto root_node = ast_json.at("nodes");
    for (size_t i = 0; i < root_node.size(); ++i) {
        auto contract_node = root_node.at(i);
        if (contract_node.find("name") == contract_node.end()) {
            continue;
        }
        std::string this_contract_name = contract_node.at("name");
        if (this_contract_name == _contract_name) {
            for (size_t j = 0; j < contract_node.at("nodes").size(); ++j) {
                auto sub_node = contract_node.at("nodes").at(j);
                if (sub_node.at("nodeType") == TokenFunctionDefinition) {
                    if (sub_node.at("name") == _function_name && num_functions == num_functions_current_contract) {
                        return sub_node.at("isConstructor");
                    }
                    num_functions++;
                }
            }
        }
    }
    return false;
}

}