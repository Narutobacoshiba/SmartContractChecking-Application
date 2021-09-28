#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include<vector>
#include "./src/ltl2prop.hpp"
#include "../include/cli11/CLI11.hpp"
#include "../include/nlohmann/json.hpp"

using namespace std;


int main(int argc, char** argv){
    CLI::App app{"Unfolding tool"};
    string LNA_FILE_NAME;
    string JSON_FILE_NAME;
    string LTL_FILE_NAME;
    string OUT_FILE_NAME = "";
    app.add_option("--lna", LNA_FILE_NAME, "Lna file")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--json", JSON_FILE_NAME, "Json file")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--ltl", LTL_FILE_NAME, "LTL file")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--out_file", OUT_FILE_NAME, "Output file path");
    CLI11_PARSE(app, argc, argv);

    ifstream lna_file_stream(LNA_FILE_NAME);
    ifstream json_file_stream(JSON_FILE_NAME);
    ifstream ltl_file_stream(LTL_FILE_NAME);

    stringstream lna_stream;
    stringstream ltl_text_stream;

    string json_content;
    string new_line;

    while (getline(lna_file_stream, new_line)) {
        lna_stream << new_line << "\n";
    }

    while (getline(ltl_file_stream, new_line)) {
        ltl_text_stream << new_line << "\n";
    }
    
    while (getline(json_file_stream, new_line)) {
        json_content = json_content + new_line + "\n";
    }

    nlohmann::json lna_json = nlohmann::json::parse(json_content);

    LTLTranslator translator = LTLTranslator(lna_stream,lna_json,ltl_text_stream);
    std::map<std::string,std::string> out = translator.translate();

    std::string outfile_name;
    if(OUT_FILE_NAME.compare("") == 0){
        outfile_name = LNA_FILE_NAME.substr(0, LNA_FILE_NAME.find('.'));
    }else{
        outfile_name = OUT_FILE_NAME;
    }

    ofstream lna_file;
    lna_file.open("./output/"+outfile_name+".lna");
    lna_file << out["lna"];
    lna_file.close();

    ofstream prop_file;
    prop_file.open("./output/"+outfile_name+".prop.lna");
    prop_file << out["prop"];
    prop_file.close();

    return 0;
}