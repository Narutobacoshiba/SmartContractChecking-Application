#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <vector>
#include "../include/cli11/CLI11.hpp"
#include "../include/nlohmann/json.hpp"
#include "../include/Helena.hpp"
#include "./src/dcr2cpn/translator.hpp"
#include "./src/dcr2cpn/DCR.hpp"
#include "./src/Unfolder.hpp"

using namespace std;
using namespace HELENA;
using namespace DCR2CPN;

int main(int argc, char** argv){
    CLI::App app{"Unfolding tool"};
    /**
     * Declare the input parameters
     */
    string MODEL_LNA_FILE_PATH;
    string CONTEXT_FILE_PATH;
    string LTL_FILE_PATH; 
    string AST_FILE_PATH; 
    string LNA_JSON_FILE_PATH;

    string OUT_FILE_PATH = "";
    string OUT_FILE_NAME = "";
    /**
     * Check the exist of the input arguments
     */
    app.add_option("--lna", MODEL_LNA_FILE_PATH, "LNA file (.lna), output of solidity2cpn tools")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--context", CONTEXT_FILE_PATH, "CONTEXT file (.xml), context of model")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--ltl", LTL_FILE_PATH, "LTL file (.json), Vulnerabilities to check")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--sol-ast", AST_FILE_PATH, "AST file (.ast), output of solidity compiler in mode --ast-json")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--lna-json", LNA_JSON_FILE_PATH, "JSON file (.json), output of solidity2cpn tool")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--output_path", OUT_FILE_PATH, "Output file path");
    app.add_option("--output_name", OUT_FILE_NAME, "Output file name");
    CLI11_PARSE(app, argc, argv);
    /**
     * Read files 
     */
    ifstream model_lna_file_stream(MODEL_LNA_FILE_PATH);

    ifstream ltl_file_stream(LTL_FILE_PATH);
    ifstream ast_file_stream(AST_FILE_PATH);
    ifstream lna_json_file_stream(LNA_JSON_FILE_PATH);

    stringstream model_lna_text_stream;
    stringstream ast_text_stream;

    string sol_json_content;
    string ltl_json_content;

    string new_line;
    /** 
     * Process .lna file
     */
    while (getline(model_lna_file_stream, new_line)) {
        model_lna_text_stream << new_line << "\n";
    }

    while (getline(ast_file_stream, new_line)) {
        ast_text_stream << new_line << "\n";
    }

    
    while (getline(ltl_file_stream, new_line)) {
        ltl_json_content = ltl_json_content + new_line + "\n";
    }

    while (getline(lna_json_file_stream, new_line)) {
        sol_json_content = sol_json_content + new_line + "\n";
    }

    nlohmann::json ltl_json = nlohmann::json::parse(ltl_json_content);
    nlohmann::json sol_json = nlohmann::json::parse(sol_json_content);

    DCRClass dcrClass =  readDCRFromXML(CONTEXT_FILE_PATH);
    Dcr2CpnTranslator contextTranslator = Dcr2CpnTranslator(dcrClass);
    StructuredNetNodePtr context_net =  contextTranslator.translate();
    
    Unfolder unfolder = Unfolder(context_net,model_lna_text_stream,sol_json,ltl_json);
    std::map<std::string,std::string> unfold_model = unfolder.UnfoldModel();

    std::string outfile_name;
    if(OUT_FILE_NAME.compare("") == 0){
        std::vector<std::string> t = split(MODEL_LNA_FILE_PATH,"/");
        outfile_name = split_ex(t[t.size()-1],".",2)[0];
    }else{
        outfile_name = OUT_FILE_NAME;
    }

    std::string outfile_path;
    if(OUT_FILE_NAME.compare("") == 0){
        outfile_path = "./";
    }else{
        outfile_path = OUT_FILE_PATH;
    }

    std::string full_outpath = outfile_path+outfile_name; 
    ofstream lna_file;
    lna_file.open(full_outpath+".lna");
    lna_file << unfold_model["lna"];
    lna_file.close();

    ofstream prop_file;
    prop_file.open(full_outpath+".prop.lna");
    prop_file << unfold_model["prop"];
    prop_file.close();

    return 0;
}
