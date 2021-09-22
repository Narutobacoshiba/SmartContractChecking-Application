#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "../cli11/CLI11.hpp"

using namespace std;

map<char,string> createAMap(){
    map<char,string> m;

    m['G'] = "[]";
    m['F'] = "<>";
    m['U'] = "until";

    return m;
}

map<char,string> createNAMap(){
    map<char,string> m;

    m['^'] = "or";
    m['&'] = "and";
    m['!'] = "not";

    return m;
}

map<char,string> specAMap = createAMap();
map<char,string> specNAMap = createNAMap();

bool isSpecAChar(char a){
    if ( specAMap.find(a) == specAMap.end() ) {
        return false;
    } else {
        return true;
    }
}
bool isSpecNAChar(char a){
    if ( specNAMap.find(a) == specNAMap.end() ) {
        return false;
    } else {
        return true;
    }
}

/** convert LTL format to .prop.lna file format 
 * LTL        ->  .prop.lna
 * G(global)  ->  []
 * F(finally) ->  <>
 * U(until)   ->  until
 * ^(or)      ->  or
 * &(and)     ->  and
 * |(not)     ->  not
 * 
 */
string converLTL2LNAProp(string str){
    vector<string> ret;
    string temp = "";
    int strLength = str.length();
    for(int i = 0; i < strLength; i++){
        if(isSpecAChar(str[i]) && (str[i+1] == ' ' || str[i+1] == '(')){
            ret.push_back(specAMap[str[i]]+' ');
        }else if(isSpecNAChar(str[i])){
            ret.push_back(specNAMap[str[i]]+' ');
            if(temp.length() > 0){
                ret.push_back(temp+' ');
                temp = "";
            }
        }else if(str[i] == ' ' || str[i] == ')' || str[i] == '(' || i == strLength){
            ret.push_back(temp+str[i]+' ');
            temp = "";
        }else{
            temp = temp + str[i];
        }
    }

    stringstream s;
    for(auto it = ret.begin(); it != ret.end(); it++){
        s << *it;
    }
    return s.str();
}

int main(int argc, char** argv){
    CLI::App app{"Solidity2CPN tool"}; 
    string LTL_FILE;
    string OUT_FILE_NAME = "";
    app.add_option("--ltl", LTL_FILE, "LTL File")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--out_file", OUT_FILE_NAME, "Ouput File");
    CLI11_PARSE(app, argc, argv); 

    ifstream t(LTL_FILE);
    stringstream buffer;
    buffer << t.rdbuf();

    string stringTokens = converLTL2LNAProp(buffer.str());
    ofstream myfile;
    if(OUT_FILE_NAME.compare("") == 0){
        myfile.open (LTL_FILE.substr(0, LTL_FILE.find('.'))+".prop.lna");
    }else{
        myfile.open (OUT_FILE_NAME+".prop.lna");
    }
    myfile << "ltl property prop:\n\t";
    myfile << stringTokens;
    myfile.close();
    return 0;
}