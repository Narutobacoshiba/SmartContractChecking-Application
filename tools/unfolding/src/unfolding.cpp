#include "unfolding.hpp"
/** Remove the none alphabet or number
 */
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
/** Extract the string by edge 
 */
std::string substr_by_edge(const std::string& _str, const std::string& _left, const std::string& _right) {
    auto left = _str.find(_left);
    auto right = _str.rfind(_right);
    if (left == std::string::npos || right == std::string::npos) {
        return "";
    } else {
        return _str.substr(_left.length() + left, right - _left.length() - left);
    }
}
/** 
 * Split the string by the delimiter
 */
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
/**
 * Cut and copy the string 
 */
std::string trim_copy(const std::string& _str) {
    return _str.substr(_str.find_first_not_of(' '), _str.find_last_not_of(' ') - _str.find_first_not_of(' ') + 1);
}
/**
 * Retrieve an element of the string by delimiter
 */
std::string retrieve_string_element(const std::string& _str, const unsigned int& _index, const std::string& _delimiter) {
    std::string new_str= trim_copy(_str);
    std::vector<std::string> v_str = split(new_str, _delimiter);
    if (_index < v_str.size()) {
        return removeNoneAlnum(v_str[_index]);
    } else {
        return "";
    }
}
/**
 * Check whether it is a defined string
 */
bool is_defined_string(const std::string& _name){
    auto it = std::find(defined_string.begin(), defined_string.end(), _name);
    if(it != defined_string.end()){
        return true;
    }
    return false;
}
/**
 * Add colours to the model
 */
void UnfoldingModel::add_color(const std::string& _color){
    coloursDef.push_back(_color);
}
/**
 * Add places to the model
 */
void UnfoldingModel::add_place(const std::string& _place){
    placesDef.push_back(_place);
}
/**
 * Add functions to the model
 */
void UnfoldingModel::add_function(const std::string& _function){
    functionDef.push_back(_function);
}
/**
 * Add transition to the model
 */
void UnfoldingModel::add_transition(const std::string& _transition){
    transitionDef.push_back(_transition);
}
/**
 * Create the comments inside the output file
 * get source code of model
 */
std::string UnfoldingModel::source_code(){
    std::stringstream result;

    result << name << "{\n";
    result << "\n/**************************\n" 
           <<   "*** Colours Definitions ***\n"
           <<   "**************************/\n\n";
    for (auto it = coloursDef.begin(); it != coloursDef.end(); ++it) {
        result << *it;
    }
    result << "\n/****************************\n" 
           <<   "*** Functions Definitions ***\n"
           <<   "****************************/\n\n";
    for (auto it = functionDef.begin(); it != functionDef.end(); ++it) {
        result << *it;
    }
    result << "\n/*************\n" 
           <<   "*** PLACES ***\n"
           <<   "*************/\n\n";
    for (auto it = placesDef.begin(); it != placesDef.end(); ++it) {
        result << *it;
    }
    result << "\n/******************\n" 
           <<   "*** TRANSITIONS ***\n"
           <<   "******************/\n\n";
    for (auto it = transitionDef.begin(); it != transitionDef.end(); ++it) {
        result << *it;
    }
    result << "\n/**************\n" 
           <<   "*** ANOTHER ***\n"
           <<   "**************/\n\n";
    result << "\n}";
    return result.str();
}


/**
 * The main function to process and read the input files (,lna and JSON)
 */
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
/**
 * Get the unfolding
 */
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
/**
 * Get name of the Transition
 */
std::string TransitionHolder::get_name(){
    return name;
}
/**
 * Add contexts to the Transition holder
 */
void TransitionHolder::add_context(const std::string& _transition){
    context_transition.push_back(_transition);
}
/**
 * Add transition from solidity to the collection
 */
void TransitionHolder::add_sol(const std::string& _transition){
    sol_transition.push_back(_transition);
}
/**
 * Get quantity of the context
 */
size_t TransitionHolder::num_context(){
    return context_transition.size();
}
/**
 * Get quantity of the transitions in solidity 
 */
size_t TransitionHolder::num_sol(){
    return sol_transition.size();
}
/**
 * Get context
 */
std::string TransitionHolder::get_context(size_t i){
    return context_transition[i];
}
/**
 * Get transition from solidity
 */
std::string TransitionHolder::get_sol(size_t i){
    return sol_transition[i];
}

/**
* Add place from solidity
*/
void TransitionHolder::add_sol_place(const std::string& _place){
    sol_places.push_back(_place);
}
/**
* Get place from solidity
*/
std::string TransitionHolder::get_sol_place(size_t i){
    return sol_places[i];
}
/**
* Get quantity of place in solidity
*/
size_t TransitionHolder::num_sol_place(){
    return sol_places.size();
}
/**
 * Get transition holder using its name
 */
TransitionHolderPtr Unfolding::get_transition_hodler_by_name(const std::string& _name){
    for(auto it = transitionHolder.begin(); it != transitionHolder.end(); ++it){
        if((*it)->get_name() == _name){
            return (*it);
        }
    }
    return nullptr;
}
/**
 * Add context to the Transition holder
 */
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
/**
 * Add solidity to the Transition holder
 */
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
/**
 * Add place from the solidity
 */
void Unfolding::add_sol_place(const std::string& _name, const std::string& _place){
    TransitionHolderPtr temp = get_transition_hodler_by_name(_name);
    if(temp != nullptr){
        temp->add_sol_place(_place);
    }else{
        TransitionHolderPtr new_th = std::make_shared<TransitionHolder>(_name);
        new_th->add_sol_place(_place);
        transitionHolder.push_back(new_th);
    }
}


/**
 * Get the string line by line and find if it contains a defined string and then process it
 * 
 */
UnfoldingModelPtr Unfolding::unfolding(){
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
                handleSolPlaces();
            }else if(keyword == TRANSITIONS){
                handleSolTransitionDefinitionsDCR();
            }
        }
        ++ptr_sol_line;
    }
    if(context == "dcr"){
        unfolding_dcr_context();
    }else{
        unfolding_free_context();
    }

    return model;
}
/**
 * Unfolding for the Free-context
 */
void Unfolding::unfolding_free_context(){

}
/**
 * Unfolding for the DCRContext
 */
void Unfolding::unfolding_dcr_context(){
    unfoldingTransitionInDCR();
}

/**
 * read code from all transition holder
 * add cflow of model and of specific submodel to transition of dcr context
 * add cflow of model to input transition, cflow of submodel to output transition of choosen submodel
 */
void Unfolding::unfoldingTransitionInDCR(){
    model->add_place("\n\tplace cflow {\n\t\tdom : epsilon;\n\t\tinit : epsilon;\n\t}");

    for(auto it = transitionHolder.begin(); it != transitionHolder.end(); ++it){ // loop through list of transition holder
        model->add_transition("/*\n * Function: "+(*it)->get_name()+"\n */\n");
        if((*it)->get_name() == unfold_func){ // if transition holder name == submodel that need unfolding name
            model->add_place("\n\tplace "+(*it)->get_name()+"_cflow {\n\t\tdom : epsilon;\n\t}");
            model->add_place("/*\n * Function: "+(*it)->get_name()+"\n */\n");
            for(size_t i = 0; i < (*it)->num_sol_place(); i++){
                model->add_place((*it)->get_sol_place(i));
            }

            for(size_t i = 0; i < (*it)->num_context(); i++){
                std::vector<std::string> temp = split((*it)->get_context(i),"\n");
                std::stringstream _str;
                auto st = temp.begin();
                
                _str << "\t" << *st << "\n";
                while(retrieve_string_element(*(++st),0," ") != "in"){
                    _str << "\t" << *st << "\n";
                }
                _str << "\t" << *st << "\n";
                _str << "\t\t\t" << "cflow : epsilon;" << "\n";
                while(retrieve_string_element(*(++st),0," ") != "out"){
                    _str << "\t" << *st << "\n";
                }
                _str << "\t" << *st << "\n";
                _str << "\t\t\t" << (*it)->get_name() + "_cflow : epsilon;" << "\n";
                st++;
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
        }else{
            for(size_t i = 0; i < (*it)->num_context(); i++){
                std::vector<std::string> temp = split((*it)->get_context(i),"\n");
                std::stringstream _str;
                auto st = temp.begin();
                
                _str << "\t" << *st << "\n";
                while(retrieve_string_element(*(++st),0," ") != "in"){
                    _str << "\t" << *st << "\n";
                }
                _str << "\t" << *st << "\n";
                _str << "\t\t\t" << "cflow : epsilon;" << "\n";
                while(retrieve_string_element(*(++st),0," ") != "out"){
                    _str << "\t" << *st << "\n";
                }
                _str << "\t" << *st << "\n";
                _str << "\t\t\t" << "cflow : epsilon;" << "\n";
                st++;
                while(st != temp.end()){
                    _str << "\t" << *st << "\n";
                    st++;
                } 

                model->add_transition(_str.str());
            }
        }
    }
}
/**
 * Get the definition of the static context
 */
std::string Unfolding::getContextStaticDefinition(){
    std::stringstream _str;
    while(((++ptr_context_line) != _context_lines.end()) && ((*ptr_context_line).find("/***") == std::string::npos)){
        _str << "\t" << *ptr_context_line << "\n";
    }
    return _str.str();
}
/**
 * Get the definition of the static solidity
 */
std::string Unfolding::getSolStaticDefinition(){
    std::stringstream _str;
    while(((++ptr_sol_line) != _sol_lines.end()) && ((*ptr_sol_line).find("/***") == std::string::npos)){
        _str << *ptr_sol_line << "\n";
    }
    return _str.str();
}
/**
 * Handle the solidity transition
 */
std::vector<std::string> Unfolding::handleElement(std::string _element, std::list<std::string>::iterator& _pointer ){
    std::vector<std::string> ret;
    while ((_pointer != _sol_lines.end() && _pointer != _context_lines.end()) && ((*_pointer).find("/*") == std::string::npos)){
        if((*_pointer).size() > 3 && retrieve_string_element(*_pointer,0," ") == _element){
            int level = 0;
            bool st_level = true;

            std::stringstream _str;
            while(st_level || (level > 0)){
                if((*_pointer).find("{") != std::string::npos){
                    level++;
                    st_level = false;
                }
                if((*_pointer).find("}") != std::string::npos){
                    level--;
                }
                _str << *_pointer <<"\n";
                _pointer++;
            }          
            ret.push_back(_str.str());
            _pointer--;
        }
        _pointer++;
    }
    _pointer--;
    return ret;
}

/**
 * Get the code of transition and the name of submodel then store it to transition holder
 * 
 */
void Unfolding::handleSolTransitionDefinitionsDCR(){
    while ((ptr_sol_line != _sol_lines.end()) && ((*ptr_sol_line).find("/***") == std::string::npos)){
        if((*ptr_sol_line).find("Function:") != std::string::npos){ // if line contain "Function:" string then
            std::string function_name = retrieve_string_element(*ptr_sol_line,1,"Function:"); // get submodel name
            std::vector<std::string> transitions = handleElement("transition",ptr_sol_line); // get all transitions code of submodel
            for(auto it = transitions.begin(); it != transitions.end(); ++it){
                add_sol_transition(function_name,*it); // add transition code to transition holder
            }
        }
        ptr_sol_line++;
    }
    ptr_sol_line--;
}  

/**
 * get code of transition and name of submodel then store it to transition holder
 * 
 */
void Unfolding::handleDCRContextTransitionDefinitions(){
    while ((ptr_context_line != _context_lines.end()) && ((*ptr_context_line).find("/***") == std::string::npos)){
        if((*ptr_context_line).find("Function:") != std::string::npos){ // if line contain "Function:" string then
            std::string function_name = retrieve_string_element(*ptr_context_line,1,"Function:");// get submodel name
            std::vector<std::string> transitions = handleElement("transition",ptr_context_line);// get all transitions code of submodel
            for(auto it = transitions.begin(); it != transitions.end(); ++it){
                add_context_transition(function_name,*it); // add transition code to transition holder
            }
        }
        ptr_context_line++;
    }
    ptr_context_line--;
}

/**
 * Get code of place and name of submodel then store it to transition holder
 * 
 */
void Unfolding::handleSolPlaces(){
    while ((ptr_sol_line != _sol_lines.end()) && ((*ptr_sol_line).find("/***") == std::string::npos)){
        if((*ptr_sol_line).find("Function:") != std::string::npos){ // if line contain "Function:" string then
            std::string function_name = retrieve_string_element(*ptr_sol_line,1,"Function:");// get submodel name
            std::vector<std::string> transitions = handleElement("place",ptr_sol_line);// get all places code of submodel
            for(auto it = transitions.begin(); it != transitions.end(); ++it){
                add_sol_place(function_name,*it);// add places code to transition holder
            }
        }else if((*ptr_sol_line).find("Init:") != std::string::npos){// if line contain "Init:" string then
            std::string function_name = retrieve_string_element(*ptr_sol_line,1,"Init:");// get submodel name
            std::vector<std::string> transitions = handleElement("place",ptr_sol_line);// get all places code of submodel
            for(auto it = transitions.begin(); it != transitions.end(); ++it){
                if(function_name == "state"){ // if it is the place for the state, add it directly to the model
                    model->add_place(*it);
                }else{  // else place to transition holder
                    add_sol_place(function_name,*it);
                }
            }
        }
        ptr_sol_line++;
        
    }
}
