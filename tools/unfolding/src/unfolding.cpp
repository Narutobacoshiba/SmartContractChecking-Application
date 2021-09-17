#include "unfolding.hpp"

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
        return removeNoneAlnum(v_str[_index]);
    } else {
        return "";
    }
}

bool is_defined_string(const std::string& _name){
    auto it = std::find(defined_string.begin(), defined_string.end(), _name);
    if(it != defined_string.end()){
        return true;
    }
    return false;
}

void UnfoldingModel::add_color(const std::string& _color){
    coloursDef.push_back(_color);
}

void UnfoldingModel::add_place(const std::string& _place){
    placesDef.push_back(_place);
}

void UnfoldingModel::add_function(const std::string& _function){
    functionDef.push_back(_function);
}

void UnfoldingModel::add_transition(const std::string& _transition){
    transitionDef.push_back(_transition);
}

std::string UnfoldingModel::source_code(){
    std::stringstream result;

    result << name << "{\n";
    result << "\n/**************************\n" 
           << "*** Colours Definitions ***\n"
           << "**************************/\n\n";
    for (auto it = coloursDef.begin(); it != coloursDef.end(); ++it) {
        result << *it;
    }
    result << "\n/**************************\n" 
           << "*** Functions Definitions ***\n"
           << "**************************/\n\n";
    for (auto it = functionDef.begin(); it != functionDef.end(); ++it) {
        result << *it;
    }
    result << "\n/**************************\n" 
           << "*** PLACES ***\n"
           << "**************************/\n\n";
    for (auto it = placesDef.begin(); it != placesDef.end(); ++it) {
        result << *it;
    }
    result << "\n/**************************\n" 
           << "*** TRANSITIONS ***\n"
           << "**************************/\n\n";
    for (auto it = transitionDef.begin(); it != transitionDef.end(); ++it) {
        result << *it;
    }
    result << "\n/**************************\n" 
           << "*** ANOTHER ***\n"
           << "**************************/\n\n";
    result << "\n}";
    return result.str();
}




Unfolding::Unfolding(const std::string& _context, std::stringstream& _sol_stream, nlohmann::json& _sol_json, std::stringstream& _context_stream, const std::string& param){
    context = _context;

    std::string new_line;
    
    getUnfoldFunction(_sol_json,param);

    while (std::getline(_sol_stream, new_line)) {
        if (!new_line.empty()) {
            _sol_lines.emplace_back(new_line);
        }
    }
    ptr_sol_line = _sol_lines.begin();

    while (std::getline(_context_stream, new_line)) {
        if (!new_line.empty()) {
            _context_lines.emplace_back(new_line);
        }
    }
    ptr_context_line = _context_lines.begin();
}

void Unfolding::getUnfoldFunction(nlohmann::json& _sol_json,const std::string& param){
    /* auto global_variables = _sol_json.at("globalVariables");
    for(size_t i = 0; i < global_variables.size(); i++){
        auto g_variable = global_variables[i];
        if(param == g_variable.at("name")){
            unfold_func = "_all_";
        }
    }

    auto functions = _sol_json.at("functions");
    for(size_t i = 0; i < functions.size(); i++){

    } */
    unfold_func = split(param,"/")[1];
}

std::string TransitionHolder::get_name(){
    return name;
}

void TransitionHolder::add_context(const std::string& _transition){
    context_transition.push_back(_transition);
}

void TransitionHolder::add_sol(const std::string& _transition){
    sol_transition.push_back(_transition);
}

size_t TransitionHolder::num_context(){
    return context_transition.size();
}

size_t TransitionHolder::num_sol(){
    return sol_transition.size();
}

std::string TransitionHolder::get_context(size_t i){
    return context_transition[i];
}

std::string TransitionHolder::get_sol(size_t i){
    return sol_transition[i];
}

TransitionHolderPtr Unfolding::get_transition_hodler_by_name(const std::string& _name){
    for(auto it = transitionHolder.begin(); it != transitionHolder.end(); ++it){
        if((*it)->get_name() == _name){
            return (*it);
        }
    }
    return nullptr;
}

void Unfolding::add_context_transition(const std::string& _name, const std::string& _transition){
    TransitionHolderPtr temp = get_transition_hodler_by_name(_name);
    if(temp != nullptr){
        temp->add_context(_transition);
    }else{
        TransitionHolderPtr new_th = std::make_shared<TransitionHolder>(_name);
        new_th->add_context(_transition);
        transitionHolder.push_back(new_th);
    }
}

void Unfolding::add_sol_transition(const std::string& _name, const std::string& _transition){
    TransitionHolderPtr temp = get_transition_hodler_by_name(_name);
    if(temp != nullptr){
        temp->add_sol(_transition);
    }else{
        TransitionHolderPtr new_th = std::make_shared<TransitionHolder>(_name);
        new_th->add_sol(_transition);
        transitionHolder.push_back(new_th);
    }
}



UnfoldingModelPtr Unfolding::unfolding(){
    if(context == "dcr"){
        unfolding_dcr_context();
    }else{
        unfolding_free_context();
    }
    return model;
}

void Unfolding::unfolding_free_context(){

}

void Unfolding::unfolding_dcr_context(){
    model = std::make_shared<UnfoldingModel>("test");
    
    while (ptr_context_line != _context_lines.end()){
        std::string keyword = substr_by_edge(*ptr_context_line,"***","***");
        if(is_defined_string(keyword)){
            (ptr_context_line++)++;
            if(keyword == ColoursDefinitions){
                std::string def = getContextStaticDefinition();
                model->add_color(def);
            }else if(keyword == FunctionsDefinitions){
                std::string def = getContextStaticDefinition();
                model->add_function(def);
            }else if(keyword == PLACES){
                std::string def = getContextStaticDefinition();
                model->add_place(def);
            }else if(keyword == TRANSITIONS){
                handleDCRContextTransitionDefinitions();
            }
        }
        ++ptr_context_line;
    }

    while (ptr_sol_line != _sol_lines.end()){
        std::string keyword = substr_by_edge(*ptr_sol_line,"***","***");
        if(is_defined_string(keyword)){
            (ptr_sol_line++)++;
            if(keyword == ColoursDefinitions){
                std::string def = getSolStaticDefinition();
                model->add_color(def);
            }else if(keyword == FunctionsDefinitions){
                std::string def = getSolStaticDefinition();
                model->add_function(def);
            }else if(keyword == PLACES){
                std::string def = getSolStaticDefinition();
                model->add_place(def);
            }else if(keyword == TRANSITIONS){
                handleSolTransitionDefinitionsDCR();
            }
        }
        ++ptr_sol_line;
    }

    unfoldingTransitionInDCR();
}

void Unfolding::unfoldingTransitionInDCR(){
    for(auto it = transitionHolder.begin(); it != transitionHolder.end(); ++it){
        model->add_transition("/*\n * Function: "+(*it)->get_name()+"\n */\n");
        for(size_t i = 0; i < (*it)->num_context(); i++){
            std::vector<std::string> temp = split((*it)->get_context(i),"\n");
            std::stringstream _str;
            auto st = temp.begin();
                
            _str << "\t" << *st << "\n";
            while(retrieve_string_element(*(++st),0," ") != "out"){
                _str << "\t" << *st << "\n";
            }
            _str << "\t" << *st << "\n";
            while(retrieve_string_element(*(++st),0," ") != "cflow"){
                _str << "\t" << *st << "\n";
            }
            if((*it)->get_name() == unfold_func){
                st++;
                _str << "\t" << "\t\t" << (*it)->get_name() + "_cflow : epsilon;" << "\n";
            }else{
                _str << "\t" << *st << "\n";
                st++;
            }
            while(st != temp.end()){
                _str << "\t" << *st << "\n";
                st++;
            }
                
            model->add_transition(_str.str());
        
        }

        bool first_require = true;
        bool first_n_require = true;
        for(size_t i = 0; i < (*it)->num_sol(); i++){
            std::vector<std::string> temp = split((*it)->get_sol(i),"\n");
            std::stringstream _str;
            auto st = temp.begin();
            
            if((*st).find("_n_revert") != std::string::npos){
                if(first_require){
                    _str <<  *st << "\n";
                    while(retrieve_string_element(*(st++),0," ") != "in"){
                        _str <<  *st << "\n";
                    }
                    _str << "\t\t\t" << (*it)->get_name() + "_cflow : epsilon;" << "\n";
                    while(st != temp.end()){
                        _str << *st << "\n";
                        st++;
                    }
                    first_require = false;
                }else{
                    while(st != temp.end()){
                        _str <<  *st << "\n";
                        st++;
                    }
                }
            }else if((*st).find("_revert") != std::string::npos){
                _str <<  *st << "\n";
                if(first_n_require){
                    while(retrieve_string_element(*(st++),0," ") != "in"){
                         _str <<  *st << "\n";
                    }
                    _str << "\t\t\t" << (*it)->get_name() + "_cflow : epsilon;" << "\n";
                    first_n_require = false;
                }
                while(retrieve_string_element(*(st++),0," ") != "out"){
                    _str <<  *st << "\n";
                }
                _str << "\t\t\t" << "cflow : epsilon;" << "\n";
                while(st != temp.end()){
                    _str << *st << "\n";
                    st++;
                }
            }else if(i == (*it)->num_sol() - 1){
                _str <<  *st << "\n";
                while(retrieve_string_element(*(st++),0," ") != "out"){
                    _str <<  *st << "\n";
                }
                _str << "\t\t\t" << "cflow : epsilon;" << "\n";
                while(st != temp.end()){
                    _str <<  *st << "\n";
                    st++;
                }
            }else{
                while(st != temp.end()){
                    _str <<  *st << "\n";
                    st++;
                }
            }

            model->add_transition(_str.str());
        }
    }
}

std::string Unfolding::getContextStaticDefinition(){
    std::stringstream _str;
    while(((++ptr_context_line) != _context_lines.end()) && ((*ptr_context_line).find("/***") == std::string::npos)){
        _str << "\t" << *ptr_context_line << "\n";
    }
    return _str.str();
}

std::string Unfolding::getSolStaticDefinition(){
    std::stringstream _str;
    while(((++ptr_sol_line) != _sol_lines.end()) && ((*ptr_sol_line).find("/***") == std::string::npos)){
        _str << *ptr_sol_line << "\n";
    }
    return _str.str();
}

void Unfolding::handleSolTransitionDefinitionsDCR(){
    while ((ptr_sol_line != _sol_lines.end()) && ((*ptr_sol_line).find("/***") == std::string::npos)){
        if((*ptr_sol_line).find("Function:") != std::string::npos){
            std::string function_name = retrieve_string_element(*ptr_sol_line,1,"Function:");
            while (((*(ptr_sol_line))[0] != '}') && ((*ptr_sol_line).find("/*") == std::string::npos)){
                if(retrieve_string_element(*ptr_sol_line,0," ") == "transition"){
                    int level = 0;
                    bool st_level = true;

                    std::stringstream _str;
                    while(st_level || (level > 0)){
                        if((*ptr_sol_line).find("{") != std::string::npos){
                            level++;
                            st_level = false;
                        }
                        if((*ptr_sol_line).find("}") != std::string::npos){
                            level--;
                        }
                        _str << *ptr_sol_line <<"\n";
                        ptr_sol_line++;
                    }          
                    add_sol_transition(function_name,_str.str());
                    ptr_sol_line--;
                }
                ptr_sol_line++;
            }
        }
        ptr_sol_line++;
    }
    ptr_sol_line--;
}

void Unfolding::handleDCRContextTransitionDefinitions(){
    while ((ptr_context_line != _context_lines.end()) && ((*ptr_context_line).find("/***") == std::string::npos)){
        if(retrieve_string_element(*ptr_context_line,0," ") == "transition"){
            std::string transition_name = retrieve_string_element(*ptr_context_line,1," ");
            int level = 0;
            bool st_level = true;

            std::stringstream _str;
            while(st_level || (level > 0)){
                if((*ptr_context_line).find("{") != std::string::npos){
                    level++;
                    st_level = false;
                }
                if((*ptr_context_line).find("}") != std::string::npos){
                    level--;
                }
                _str << *ptr_context_line << "\n";
                ptr_context_line++;
            }   
            add_context_transition(transition_name,_str.str());
        }      
        ptr_context_line++;
    }
    ptr_context_line--;
}

