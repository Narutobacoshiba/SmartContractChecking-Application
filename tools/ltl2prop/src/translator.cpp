#include "./translator.hpp"
#include "../../include/Utils.hpp"


int precedence_of_op(std::string _op){
    if(_op == NOT_OP || _op == GLOBAL_OP || _op == FINNALY_OP){
        return 2;
    }else if(_op == OR_OP || _op == AND_OP || _op == UNTIL_OP || 
            std::find(ComparisonOperator.begin(), ComparisonOperator.end(), _op) != ComparisonOperator.end()){
        return 1;
    }
    return 0;
}

/** The main function to process and read the input files (lna,json,ltl)
 */
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

/** Create a map to map between the ltl formula and the helena ltl prop formula
 */
void LTLTranslator::createMap(){
    MappingOp[OR_OP] = OR_OP_PROP;
    MappingOp[AND_OP] = AND_OP_PROP;
    MappingOp[NOT_OP] = NOT_OP_PROP;
    MappingOp[GLOBAL_OP] = GLOBAL_OP_PROP;
    MappingOp[FINNALY_OP] = FINNALY_OP_PROP;
    MappingOp[UNTIL_OP] = UNTIL_OP_PROP;
}

/** Read variable information from json file and store
 */
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

/** Check if _name is defined as const
 */
bool LTLTranslator::is_const_definition(const std::string& _name){
    if(constDefinitions.find(_name) != constDefinitions.end()){
        return true;
    }
    return false;
}
/** Get value of _name (_name is defined as const)
 */
std::string LTLTranslator::get_const_definition_value(const std::string& _name){
    if(is_const_definition(_name)){
        return constDefinitions[_name];
    }
    return "";
}
/** Check if _name is  global variable
 */
bool LTLTranslator::is_global_variable(const std::string& _name){
    if(global_variables.find(_name) != global_variables.end()){
        return true;
    }
    return false;
}
/** Get global variable placetype by input
 */
std::string LTLTranslator::get_global_variable_placetype(const std::string& _name){
    if(is_global_variable(_name)){
        return global_variables[_name];
    }
    return "";
}
/** Check if _name is local variable
 */
bool LTLTranslator::is_local_variable(const std::string& _name){
    if(local_variables.find(_name) != local_variables.end()){
        return true;
    }
    return false;
}
/** Get local variable placetype by input
 */
std::string LTLTranslator::get_local_variable_placetype(const std::string& _name){
    if(is_local_variable(_name)){
        return local_variables[_name];
    }
    return "";
}

/** Read ltl,lna,json file as input and output lna and prop.lna file
 */
std::map<std::string,std::string> LTLTranslator::translate(){
    while (ptr_ltl_line != ltl_lines.end()){
        std::string keyword = retrieve_string_element(*ptr_ltl_line,0," ");
        if(std::find(TokensDefine.begin(), TokensDefine.end(), keyword) != TokensDefine.end()){
            if(keyword == CONST_STRING){
                handleConstDefinition();
            }else if(keyword == PROPOSITION_STRING){
                handlePropositionDefinition();
            }else if(keyword == PROPERTY_STRING){
                handlePropertyDefinition();
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
    result["prop"] = property_string;
    return result;
}
/** Analyse const definition
 */
void LTLTranslator::handleConstDefinition(){
    std::string definition = split_ex(*ptr_ltl_line," ",2)[1];
    
    std::string variable = removeNoneAlnum(retrieve_string_element(definition,0,"="));
    std::string value = removeNoneAlnum(retrieve_string_element(definition,1,"="));

    constDefinitions[variable] = value;
}

/** Analyse proposition definition
 */
void LTLTranslator::handlePropositionDefinition(){
    std::string definition = split_ex(*ptr_ltl_line," ",2)[1];

    std::string prop_name = removeNoneAlnum(retrieve_string_element(definition,0,":"));
    std::string prop_def = retrieve_string_element(definition,1,":");
    
    std::string finnal_expression = analysePropositionExpression(prop_def);

    propositions.push_back("proposition " + prop_name + ":\n\t" + finnal_expression + ";\n");
}

std::string LTLTranslator::handleNoNamePropositionDefinition(const std::string& _def){
    std::string proposition_name = "proposition_number_" + std::to_string(current_noname_proposition);
    current_noname_proposition++;

    std::string expression = substr_by_edge(_def,"{","}");
    std::string finnal_expression = analysePropositionExpression(expression);

    propositions.push_back("proposition " + proposition_name + ":\n\t" + finnal_expression + ";\n");
    return proposition_name;
}

std::string LTLTranslator::analysePropositionExpression(const std::string& _exp){
    std::vector<std::string> expression = infixToPostfixExpression(_exp);

    std::vector<std::string> opr;
    for(auto it = expression.begin(); it != expression.end(); ++it){
        std::string op = *it;
        if(MappingOp.find(op) != MappingOp.end()){
            op = MappingOp[op];
        }

        if(std::find(ComparisonOperator.begin(), ComparisonOperator.end(), *it) != ComparisonOperator.end()){
            if(opr.size() >= 2){
                std::stringstream temp_exp;
                std::string first_opr = opr.back();
                opr.pop_back();
                std::string second_opr = opr.back();
                opr.pop_back();
                
                if(first_opr.find("'") != std::string::npos){
                    std::string first_opr_name = substr_by_edge(first_opr,"'","'");
                    trim_ex(first_opr_name);
                    std::string first_v;
                    if(is_global_variable(first_opr_name)){
                        std::string v = get_global_variable_placetype(first_opr_name);
                        temp_exp << "exists (t1 in S | ";
                        first_v = "(t1->1)." + split(v,".")[1];
                    }else if(is_local_variable(first_opr_name)){
                        std::string v = get_local_variable_placetype(first_opr_name);
                        temp_exp << "exists (t1 in " + v +" | ";
                        first_v = "t1->1";
                    }
                
                    if(second_opr.find("'") != std::string::npos){
                        std::string second_opr_name = substr_by_edge(second_opr,"'","'");
                        trim_ex(second_opr);

                        if(is_global_variable(second_opr_name)){
                            std::string v = get_global_variable_placetype(second_opr_name);
                            temp_exp << "exists (t2 in S | (t2->1)." << split(v,".")[1] << " " + op << " " + first_v << "))";
                        }else if(is_local_variable(second_opr_name)){
                            std::string v = get_local_variable_placetype(second_opr_name);
                            temp_exp << "exists (t in " + v +" | t->1" << " " + op << " " + first_v << "))";
                        }
                    }else if(is_const_definition(second_opr)){
                        temp_exp << get_const_definition_value(second_opr) << " " + op << " " + first_v << ")";
                    }else{
                        temp_exp << second_opr << " " + op << " " + first_v << ")";
                    }
                }else{
                    if(is_const_definition(first_opr)){
                        first_opr = get_const_definition_value(first_opr);
                    }

                    if(second_opr.find("'") != std::string::npos){
                        std::string second_opr_name = substr_by_edge(second_opr,"'","'");
                        trim_ex(second_opr);

                        if(is_global_variable(second_opr_name)){
                            std::string v = get_global_variable_placetype(second_opr_name);
                            temp_exp << "exists (t2 in S | (t2->1)." << split(v,".")[1] << " " + op << " " + first_opr << ")";
                        }else if(is_local_variable(second_opr_name)){
                            std::string v = get_local_variable_placetype(second_opr_name);
                            temp_exp << "exists (t in " + v +" | t->1" << " " + op << " " + first_opr << ")";
                        }
                    }else if(is_const_definition(second_opr)){
                        temp_exp << get_const_definition_value(second_opr) << " " + op << " " + first_opr << ")";
                    }else{
                        temp_exp << second_opr << " " + op << " " + first_opr << ")";
                    }
                }
                opr.push_back(temp_exp.str());
            }else{
                //error
            }
            
        }else if(*it == OR_OP || *it == AND_OP){
            if(opr.size() >= 2){
                std::string first_opr = opr.back();
                opr.pop_back();
                std::string second_opr = opr.back();
                opr.pop_back();

                opr.push_back(second_opr + " " + op + " " + first_opr);
            }else{
                //error
            }
        }else if(*it == NOT_OP){
            if(opr.size() >= 1){
                std::string first_opr = opr.back();
                opr.pop_back();

                opr.push_back(op + " " + first_opr);
            }else{
                //error
            }
        }else{
            opr.push_back(*it);
        }
    }
    if(opr.size() == 1){
        return opr.back();
    }else{
        //error
        return "";
    }
}
/** Analyse property definition
 */
void LTLTranslator::handlePropertyDefinition(){
    std::string definition = split_ex(*ptr_ltl_line," ",2)[1];

    std::string property_name = removeNoneAlnum(split_ex(definition,":",2)[0]);
    std::string property_def = split_ex(definition,":",2)[1];
    std::vector<std::string> els = splitExpression(property_def);

    std::stringstream property;
    for(auto it = els.begin(); it != els.end(); ++it){
      
        if((*it).find("{") != std::string::npos){
            std::string prop_name = handleNoNamePropositionDefinition(*it);
            property << prop_name << " ";
        }else if(MappingOp.find(*it) != MappingOp.end()){
            property << MappingOp[*it] << " ";
        }else{
            property << *it << " ";
        }
    }
    
    property_string = "ltl property " + property_name + ":\n\t" + property.str()+";\n";
}
/** Convert proposition expression to proposition in lna file
 */
std::vector<std::string> LTLTranslator::infixToPostfixExpression(const std::string& _exp){
    std::vector<std::string> els = splitExpression(_exp);
    std::vector<std::string> opt_stack;
    std::vector<std::string> opr_stack;
    int cout = 0;

    while(cout < els.size()){
        if(els[cout] == OPEN_PARENTHESES){
            opr_stack.push_back(els[cout]);
        }else if(els[cout] == CLOSE_PARENTHESES){
            while(opr_stack.back() != OPEN_PARENTHESES){
                opt_stack.push_back(opr_stack.back());
                opr_stack.pop_back();
            }
            opr_stack.pop_back();
        }else if(std::find(ComparisonOperator.begin(), ComparisonOperator.end(), els[cout]) != ComparisonOperator.end() ||
                std::find(BooleanOperator.begin(), BooleanOperator.end(), els[cout]) != BooleanOperator.end() ||
                std::find(LTLOperator.begin(), LTLOperator.end(), els[cout]) != LTLOperator.end()){
            while(opr_stack.size() > 0 && precedence_of_op(els[cout]) <= precedence_of_op(opr_stack.back())){
                opt_stack.push_back(opr_stack.back());
                opr_stack.pop_back();
            }
            opr_stack.push_back(els[cout]);
        }else{
            opt_stack.push_back(els[cout]);
        }
        cout++;
    }
    while(opr_stack.size() > 0){
        opt_stack.push_back(opr_stack.back());
        opr_stack.pop_back();
    }

    return opt_stack;
}

/** Split expression string into list of element
 *      example:
 *          std::string input = "(F(is_valid))";
 *          std::vector<std::string> out = splitExpression(input);
 *          output = {"(","F","(","is_valid",")",")"}
 */
std::vector<std::string> LTLTranslator::splitExpression(const std::string& _exp){
    std::vector<std::string> result;
    std::vector<char> temp;
    int cout = 0;

    while(cout < _exp.length()){
        if(_exp[cout] == '(' || _exp[cout] == ')' || 
        std::find(BooleanOperator.begin(), BooleanOperator.end(), std::string(1,_exp[cout])) != BooleanOperator.end()){
            if(temp.size() > 0){
                result.push_back(std::string(temp.begin(), temp.end()));
                temp.clear();
            }  

            result.push_back(std::string(1,_exp[cout]));
        }else if(_exp[cout] == ' ' || _exp[cout] == ';'){
            if(temp.size() > 0){
                result.push_back(std::string(temp.begin(), temp.end()));
                temp.clear();
            }  
        }else if(_exp[cout] == '{'){
            if(temp.size() > 0){
                result.push_back(std::string(temp.begin(), temp.end()));
                temp.clear();
            }  
            
            while(_exp[cout] != '}' && cout < _exp.length()){
                temp.push_back(_exp[cout]); 
                cout++;
            }

            if(cout < _exp.length()){
                temp.push_back('}');
                result.push_back(std::string(temp.begin(), temp.end()));
                temp.clear();
            }
            
        }else{
            temp.push_back(_exp[cout]);
        }
        cout++;
    }

    if(temp.size() > 0){
        result.push_back(std::string(temp.begin(), temp.end()));
        temp.clear();
    }  

    return result;
}