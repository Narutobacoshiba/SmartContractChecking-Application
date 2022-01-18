#include <fstream>
#include <iostream>
#include <sstream>

#include "../include/nlohmann/json.hpp"
#include "./src/ASTAnalyser.hpp"
#include "./src/Constants.hpp"
#include "../include/Utils.hpp"

#include "../include/Helena.hpp"
#include "./src/Translator.hpp"

using namespace SOL2CPN;
using namespace std;

int main(int argc, char** argv){
    
    string ast_file_name = "./test/test.ast";
    string ast_json_file_name = "./test/test.json";
    string output_file_name = "./output/test.lna";

    ifstream ast_text_file_stream(ast_file_name);
    ifstream ast_json_file_stream(ast_json_file_name);

    stringstream ast_text_stream;



    string new_line;
    string sol_name;
    string ast_json_content;

    while (getline(ast_text_file_stream, new_line)) {
        ast_text_stream << new_line << "\n";
    }

    while (getline(ast_json_file_stream, new_line)) {
        if (new_line.find(".sol =======") != string::npos) {
            sol_name = substr_by_edge(new_line, "======= ", " =======");
            break;
        }
    }

    while (getline(ast_json_file_stream, new_line)) {
        if (new_line.find(".sol =======") == string::npos) {
            ast_json_content = ast_json_content + new_line + "\n";
        } else {
            nlohmann::json ast_json = nlohmann::json::parse(ast_json_content);
            sol_name = substr_by_edge(new_line, "", "");
            ast_json_content = "";
        }
    }


    if (ast_json_content != "") {
        nlohmann::json ast_json = nlohmann::json::parse(ast_json_content);
        
        ASTAnalyser ast_analyser(ast_text_stream, ast_json, true, sol_name, "");

        RootNodePtr root_node = ast_analyser.analyse();
      
        Translator nettranslator(root_node);
        
        string new_source = nettranslator.translate();
        if (output_file_name != "") {
            ofstream output_file_stream(output_file_name);
            output_file_stream<<new_source;
            output_file_stream.close();
            cout << "lna file generated in test_files directory: SUCESS" << endl;
        } else {
            cout << "lna file generated in test_files directory: FAILURE" << endl;
        }
    }
    
    ast_json_file_stream.close();

    exit(ErrorCode::SUCCESS);

    return 0;
}
