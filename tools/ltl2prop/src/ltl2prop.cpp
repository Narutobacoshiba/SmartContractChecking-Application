#include "./ltl2prop.hpp"

std::string substr_by_edge(const std::string& _str, const std::string& _left, const std::string& _right) {
    auto left = _str.find(_left);
    auto right = _str.rfind(_right);
    if (left == std::string::npos || right == std::string::npos) {
        return "";
    } else {
        return _str.substr(_left.length() + left, right - _left.length() - left);
    }
}
std::vector<std::string> split(const std::string& _str, const std::string& _delimiter) {
    std::vector<std::string> result;
    std::string str = std::string(_str);
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(_delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + _delimiter.length());
    }
    result.push_back(str);
        
    return result;
}

std::string trim_copy(const std::string& _str) {
    return _str.substr(_str.find_first_not_of(' '), _str.find_last_not_of(' ') - _str.find_first_not_of(' ') + 1);
}

std::string retrieve_string_element(const std::string& _str, const unsigned int& _index, const std::string& _delimiter) {
    std::string new_str= trim_copy(_str);
    std::vector<std::string> v_str = split(new_str, _delimiter);
    if (_index < v_str.size()) {
        return v_str[_index];
    } else {
        return "";
    }
}

std::string removeNoneAlnum(const std::string& inp_string){
    std::string s = inp_string;
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] < 'A' || s[i] > 'Z') &&
            (s[i] < 'a' || s[i] > 'z') && 
            (s[i] < '0' || s[i] > '9') && s[i] != '_')
        {  
            s.erase(i, 1);
            i--;
        }
    }
    return s;
}

bool is_defined_string(const std::string& _name){
    auto it = std::find(defined_string.begin(), defined_string.end(), _name);
    if(it != defined_string.end()){
        return true;
    }
    return false;
}

LTLTranslator::LTLTranslator(std::stringstream& _lna_stream, const nlohmann::json& lna_json, std::stringstream& _ltl_stream){
    std::string new_line;

    while (std::getline(_lna_stream, new_line)) {
        if (!new_line.empty()) {
            lna_lines.emplace_back(new_line);
        }
    }
    ptr_lna_line = lna_lines.begin();

    while (std::getline(_ltl_stream, new_line)) {
        if (!new_line.empty()) {
            ltl_lines.emplace_back(new_line);
        }
    }
    ptr_ltl_line = ltl_lines.begin();

    handleVariable(lna_json);
    
}

void LTLTranslator::handleVariable(const nlohmann::json& lna_json){
    auto gvs = lna_json.at("globalVariables");
    for(size_t i = 0; i < gvs.size(); i++){
        auto gv = gvs[i];
        global_variables[gv.at("name")] = gv.at("placeType");
    }

    auto functions = lna_json.at("functions");
    for(size_t i = 0; i < functions.size(); i++){
        auto lvs =  functions[i].at("localVariables");
        for(size_t i = 0; i < lvs.size(); i++){
            auto lv = lvs[i];
            local_variables[lv.at("name")] = lv.at("place");
        }
    }
}


bool LTLTranslator::is_const_definition(const std::string& _name){
    if(constDefinitions.find(_name) != constDefinitions.end()){
        return true;
    }
    return false;
}

std::string LTLTranslator::get_const_definition_value(const std::string& _name){
    if(is_const_definition(_name)){
        return constDefinitions[_name];
    }
    return "";
}

bool LTLTranslator::is_global_variable(const std::string& _name){
    if(global_variables.find(_name) != global_variables.end()){
        return true;
    }
    return false;
}
std::string LTLTranslator::get_global_variable_placetype(const std::string& _name){
    if(is_global_variable(_name)){
        return global_variables[_name];
    }
    return "";
}

bool LTLTranslator::is_local_variable(const std::string& _name){
    if(local_variables.find(_name) != local_variables.end()){
        return true;
    }
    return false;
}
std::string LTLTranslator::get_local_variable_placetype(const std::string& _name){
    if(is_local_variable(_name)){
        return local_variables[_name];
    }
    return "";
}


std::map<std::string,std::string> LTLTranslator::translate(){
    while (ptr_ltl_line != ltl_lines.end()){
        std::string keyword = retrieve_string_element(*ptr_ltl_line,0," ");
        if(is_defined_string(keyword)){
            if(keyword == CONST_STRING){
                handleConst();
            }else if(keyword == PROPOSITION_STRING){
                handleProposition();
            }else if(keyword == PROPERTY_STRING){
                
            }
        }
        ++ptr_ltl_line;
    }
}

void LTLTranslator::handleConst(){
    std::string definition = retrieve_string_element(*ptr_ltl_line,1,CONST_STRING);
    
    std::string variable = removeNoneAlnum(retrieve_string_element(definition,0,"="));
    std::string value = removeNoneAlnum(retrieve_string_element(definition,1,"="));

    constDefinitions[variable] = value;
}


void LTLTranslator::handleProposition(){
    std::string definition = retrieve_string_element(*ptr_ltl_line,1,PROPOSITION_STRING);
    std::string prop_name = removeNoneAlnum(retrieve_string_element(definition,0,":"));
    std::string prop_def = retrieve_string_element(definition,1,":");
    std::string expression = handleExpression(prop_def);
    std::cout << expression << "\n";
}


std::string LTLTranslator::handleExpression(std::string _exp){
    std::vector<std::string> els = splitExpression(_exp);
    std::stringstream result;
    for(size_t i = 0; i < els.size();){
        if(els[i] == "<" || els[i] == ">" || els[i] == "="){
            if(is_global_variable(els[i-1])){
                std::string v = get_global_variable_placetype(els[i-1]);
                result << "exists (t in S|(t->1)." << split(v,".")[1] << " " + els[i] + " " << get_const_definition_value(els[i+1]) << ")";
            }else if(is_local_variable(els[i-1])){

            }
            i+=1;
        }else if (els[i] == "(" || els[i] == ")" || els[i] == "v"){
            result << " " + els[i] + " ";
        }
        i++;
    }
    return result.str();
}

std::vector<std::string> LTLTranslator::splitExpression(std::string _exp){
    std::vector<std::string> result;
    std::vector<char> temp;

    for(int i = 0; i < _exp.length(); i++){
        if(_exp[i] == '(' || _exp[i] == ')'){
            if(temp.size() > 0)   
                result.push_back(std::string(temp.begin(), temp.end()));

            result.push_back(std::string(1,_exp[i]));
            temp.clear();
        }else if(_exp[i] == ' '){
            if(temp.size() > 0)   
                result.push_back(std::string(temp.begin(), temp.end()));
            temp.clear();
        }else{
            temp.push_back(_exp[i]);
        }
    }

    return result;
}