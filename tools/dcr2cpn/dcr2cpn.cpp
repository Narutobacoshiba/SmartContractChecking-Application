#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "../../include/cli11/CLI11.hpp"
#include "include/translator.hpp"
#include "include/DCR.hpp"

using namespace std;
using namespace DCR2CPN;

int main(int argc, char** argv)
{   
    CLI::App app{"DCR2CPN tool"}; 
    string DCR_XML_FILE;
    string OUT_FILE_NAME = "";
    app.add_option("--xml", DCR_XML_FILE, "DCR Graph path")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--out_file", OUT_FILE_NAME, "Output file path");
     CLI11_PARSE(app, argc, argv); 

    DCRClass dcrClass =  readDCRFromXML(DCR_XML_FILE);
    Translator translator = Translator(dcrClass);
    NetNodePtr net = translator.translate();
    
    ofstream myfile;
    if(OUT_FILE_NAME.compare("") == 0){
        myfile.open (DCR_XML_FILE.substr(0, DCR_XML_FILE.find('.'))+".lna");
    }else{
        myfile.open (OUT_FILE_NAME+".lna");
    }
    
    myfile << net->source_code();
    myfile.close();
    return 0;
}