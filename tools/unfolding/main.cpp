#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include<vector>
#include "./src/unfolding.hpp"
#include "../include/cli11/CLI11.hpp"

using namespace std;


int main(int argc, char** argv){
    CLI::App app{"Unfolding tool"};
    string SOL_LNA_FILE_NAME;
    string CONTEXT_FILE_NAME;
    string PARAM_NAME; 
    string OUT_FILE_NAME = "";
    app.add_option("--lna", SOL_LNA_FILE_NAME, "Lna file")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--context", CONTEXT_FILE_NAME, "Context file")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--param", PARAM_NAME, "Param file")
        ->required();
    app.add_option("--out_file", OUT_FILE_NAME, "Output file path");
    CLI11_PARSE(app, argc, argv);

    ifstream sol_lna_file_stream(SOL_LNA_FILE_NAME);
    ifstream context_file_stream(CONTEXT_FILE_NAME);

    stringstream sol_lna_stream;
    stringstream context_text_stream;

    string sol_json_content;
    string new_line;

    while (getline(sol_lna_file_stream, new_line)) {
        sol_lna_stream << new_line << "\n";
    }

    while (getline(context_file_stream, new_line)) {
        context_text_stream << new_line << "\n";
    }



    Unfolding unfold = Unfolding("dcr",sol_lna_stream,context_text_stream,PARAM_NAME);
    NetNodePtr model = unfold.unfolding();

    ofstream myfile;
    if(OUT_FILE_NAME.compare("") == 0){
        myfile.open ("./output/"+SOL_LNA_FILE_NAME.substr(0, SOL_LNA_FILE_NAME.find('.'))+".lna");
    }else{
        myfile.open ("./output/"+OUT_FILE_NAME+".lna");
    }
    myfile << model->source_code();
    myfile.close();

    return 0;
}