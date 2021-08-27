#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

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

string converLTL2LNAProp(string str){
    vector<string> ret;
    string temp = "";
    int strLength = str.length();
    for(int i = 0; i < strLength; i++){
        if(isSpecAChar(str[i]) && (str[i+1] == ' ' || str[i+1] == '(')){
            ret.push_back(specAMap[str[i]]);
        }else if(isSpecNAChar(str[i])){
            ret.push_back(specNAMap[str[i]]+' ');
            if(temp.length() > 0){
                ret.push_back(temp+' ');
                temp = "";
            }
        }else if(str[i] == ' ' || str[i] == ')' || str[i] == '(' || i == strLength){
            ret.push_back(temp+str[i]);
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

int main(){
    string test = "G(F  (uchiha ^  !   bedia))U((!ulata))";
    string stringTokens = converLTL2LNAProp(test);
    cout << stringTokens <<"\n";
    return 0;
}