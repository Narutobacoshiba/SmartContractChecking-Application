#include "./ltl2prop.hpp"
#include "../../include/Utils.hpp"



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
    createMap();
}

void LTLTranslator::createMap(){
    MappingOp[OR_OP] = OR_OP_PROP;
    MappingOp[AND_OP] = AND_OP_PROP;
    MappingOp[NOT_OP] = NOT_OP_PROP;
    MappingOp[GLOBAL_OP] = GLOBAL_OP_PROP;
    MappingOp[FINNALY_OP] = FINNALY_OP_PROP;
    MappingOp[UNTIL_OP] = UNTIL_OP_PROP;
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
    std::string propety;

    while (ptr_ltl_line != ltl_lines.end()){
        std::string keyword = retrieve_string_element(*ptr_ltl_line,0," ");
        if(std::find(TokensDefine.begin(), TokensDefine.end(), keyword) != TokensDefine.end()){
            if(keyword == CONST_STRING){
                handleConst();
            }else if(keyword == PROPOSITION_STRING){
                handleProposition();
            }else if(keyword == PROPERTY_STRING){
                propety = handleProperty();
            }
        }
        ++ptr_ltl_line;
    }

    std::stringstream lna_result;
    while (ptr_lna_line != lna_lines.end()){
        if(substr_by_edge(*ptr_lna_line,"/*** "," ***/") == PROPOSITION_AREA){
            lna_result << *ptr_lna_line << "\n"; 
            for(auto it = propositions.begin(); it != propositions.end(); ++it){
                lna_result << (*it) << "\n";
            }
        }else{
            lna_result << *ptr_lna_line << "\n";
        }
        ++ptr_lna_line;
    }

    std::map<std::string, std::string> result;
    result["lna"] = lna_result.str();
    result["prop"] = propety;
    return result;
}

void LTLTranslator::handleConst(){
    std::string definition = split_ex(*ptr_ltl_line," ",2)[1];
    
    std::string variable = removeNoneAlnum(retrieve_string_element(definition,0,"="));
    std::string value = removeNoneAlnum(retrieve_string_element(definition,1,"="));

    constDefinitions[variable] = value;
}


void LTLTranslator::handleProposition(){
    std::string definition = split_ex(*ptr_ltl_line," ",2)[1];

    std::string prop_name = removeNoneAlnum(retrieve_string_element(definition,0,":"));
    std::string prop_def = retrieve_string_element(definition,1,":");
    std::string expression = handleExpression(prop_def);
    
    propositions.push_back("proposition " + prop_name + ":\n\t" + expression + ";\n");
}

std::string LTLTranslator::handleProperty(){
    std::string definition = split_ex(*ptr_ltl_line," ",2)[1];

    std::string property_name = removeNoneAlnum(split_ex(definition,":",2)[0]);
    std::string property_def = split_ex(definition,":",2)[1];
    std::vector<std::string> els = splitExpression(property_def);

    std::stringstream property;
    for(auto it = els.begin(); it != els.end(); ++it){
        if(MappingOp.find(*it) != MappingOp.end()){
            property << MappingOp[*it] << " ";
        }else{
            property << *it << " ";
        }
    }
    
    return "ltl property " + property_name + ":\n\t" + property.str()+";\n";
}

std::string LTLTranslator::handleExpression(std::string _exp){
    std::vector<std::string> els = splitExpression(_exp);
    std::stringstream result;
    for(size_t i = 0; i < els.size();){
        if(std::find(ComparisonOperator.begin(), ComparisonOperator.end(), els[i]) != ComparisonOperator.end()){
            if(is_global_variable(els[i-1])){
                std::string v = get_global_variable_placetype(els[i-1]);
                result << "exists (t in S | (t->1)." << split(v,".")[1] << " " + els[i] + " " << get_const_definition_value(els[i+1]) << ")";
            }else if(is_local_variable(els[i-1])){
                std::string v = get_local_variable_placetype(els[i-1]);
                result << "exists (t in " + v +"| t->1 " << " " + els[i] + " " << get_const_definition_value(els[i+1]) << ")";
            }
            i+=1;
        }else if (std::find(BooleanOperator.begin(), BooleanOperator.end(), els[i]) != BooleanOperator.end() || els[i] == OPEN_PARENTHESES || els[i] == CLOSE_PARENTHESES){
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
        if(_exp[i] == '(' || _exp[i] == ')' || 
        std::find(BooleanOperator.begin(), BooleanOperator.end(), std::string(1,_exp[i])) != BooleanOperator.end()){
            if(temp.size() > 0)   
                result.push_back(std::string(temp.begin(), temp.end()));

            result.push_back(std::string(1,_exp[i]));
            temp.clear();
        }else if(_exp[i] == ' ' || _exp[i] == ';'){
            if(temp.size() > 0)   
                result.push_back(std::string(temp.begin(), temp.end()));
            temp.clear();
        }else{
            temp.push_back(_exp[i]);
        }
    }

    return result;
}