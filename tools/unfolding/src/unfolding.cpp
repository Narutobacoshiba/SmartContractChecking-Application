#include "unfolding.hpp"
<<<<<<< HEAD
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
=======

/** The main function to process and read the input files (lna)
 */
Unfolding::Unfolding(const std::string& _context, std::stringstream& _sol_stream, std::stringstream& _context_stream, const std::string& param){
>>>>>>> hadt
    context = _context;

    std::string new_line;
    
    unfold_func = split(param,"/");

    while (std::getline(_sol_stream, new_line)) {
        if (!new_line.empty()) {
            std::string temp = std::string(new_line);
            trim_ex(temp);
            if(temp.length() > 0)
                _sol_lines.emplace_back(new_line);
        }
    }

    while (std::getline(_context_stream, new_line)) {
        if (!new_line.empty()) {
            std::string temp = std::string(new_line);
            trim_ex(temp);
            if(temp.length() > 0)
                _context_lines.emplace_back(new_line);
        }
    }
}
<<<<<<< HEAD
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
=======

/** Get name of Submodel
 */
std::string SubmodelHolder::get_name(){
    return name;
}
/** Add a transition of context file to storage
 */
void SubmodelHolder::add_context_transition(TransitionNodePtr _transition){
    context_transitions.push_back(_transition);
}
/** Add a transition of solidity file to storage
 */
void SubmodelHolder::add_solidity_transition(TransitionNodePtr _transition){
    solidity_transitions.push_back(_transition);
}
/** Get the number of transition in context file 
 */
size_t SubmodelHolder::num_context_transitions(){
    return context_transitions.size();
}
/** Get the number of transition in solidity file 
 */
size_t SubmodelHolder::num_solidity_transitions(){
    return solidity_transitions.size();
}
/** Get transition of context file by index
 */
TransitionNodePtr SubmodelHolder::get_context_transition(size_t i){
    return context_transitions[i];
}
/** Get transition of solidity file by index
 */
TransitionNodePtr SubmodelHolder::get_solidity_transition(size_t i){
    return solidity_transitions[i];
}
/** Add a place of context file to storage
 */
void SubmodelHolder::add_context_place(PlaceNodePtr _place){
    context_places.push_back(_place);
}
/** Get place of context file by index
 */
PlaceNodePtr SubmodelHolder::get_context_place(size_t i){
    return context_places[i];
}
/** Get the number of place in context file 
 */
size_t SubmodelHolder::num_context_places(){
    return context_places.size();
}
/** Add a transition of solidity file to storage
 */
void SubmodelHolder::add_solidity_place(PlaceNodePtr _place){
    solidity_places.push_back(_place);
}
/** Get place of solidity file by index
 */
PlaceNodePtr SubmodelHolder::get_solidity_place(size_t i){
    return solidity_places[i];
}
/** Get the number of place in solidity file 
 */
size_t SubmodelHolder::num_solidity_places(){
    return solidity_places.size();
}
/** Get an object of SubmodelHolder by name
 */
SubmodelHolderPtr Unfolding::get_submodel_holder_by_name(const std::string& _name){
    for(auto it = submodelHolders.begin(); it != submodelHolders.end(); ++it){
>>>>>>> hadt
        if((*it)->get_name() == _name){
            return (*it);
        }
    }
    return nullptr;
}
<<<<<<< HEAD
/**
 * Add context to the Transition holder
 */
void Unfolding::add_context_transition(const std::string& _name, const std::string& _transition){
    TransitionHolderPtr temp = get_transition_hodler_by_name(_name);
=======
/** Add transition of context file to specific submodel indicated by the name
 */
void Unfolding::add_context_transition_to_submodel(const std::string& _name, TransitionNodePtr _transition){
    SubmodelHolderPtr temp = get_submodel_holder_by_name(_name);
>>>>>>> hadt
    if(temp != nullptr){
        temp->add_context_transition(_transition);
    }else{
        SubmodelHolderPtr new_th = std::make_shared<SubmodelHolder>(_name);
        new_th->add_context_transition(_transition);
        submodelHolders.push_back(new_th);
    }
}
<<<<<<< HEAD
/**
 * Add solidity to the Transition holder
 */
void Unfolding::add_sol_transition(const std::string& _name, const std::string& _transition){
    TransitionHolderPtr temp = get_transition_hodler_by_name(_name);
=======
/** Add transition of solidity file to specific submodel indicated by the name
 */
void Unfolding::add_solidity_transition_to_submodel(const std::string& _name, TransitionNodePtr _transition){
    SubmodelHolderPtr temp = get_submodel_holder_by_name(_name);
>>>>>>> hadt
    if(temp != nullptr){
        temp->add_solidity_transition(_transition);
    }else{
        SubmodelHolderPtr new_th = std::make_shared<SubmodelHolder>(_name);
        new_th->add_solidity_transition(_transition);
        submodelHolders.push_back(new_th);
    }
}
<<<<<<< HEAD
/**
 * Add place from the solidity
 */
void Unfolding::add_sol_place(const std::string& _name, const std::string& _place){
    TransitionHolderPtr temp = get_transition_hodler_by_name(_name);
=======
/** Add place of solidity file to specific submodel indicated by the name
 */
void Unfolding::add_solidity_place_to_submodel(const std::string& _name, PlaceNodePtr _place){
    SubmodelHolderPtr temp = get_submodel_holder_by_name(_name);
>>>>>>> hadt
    if(temp != nullptr){
        temp->add_solidity_place(_place);
    }else{
        SubmodelHolderPtr new_th = std::make_shared<SubmodelHolder>(_name);
        new_th->add_solidity_place(_place);
        submodelHolders.push_back(new_th);
    }
}
/** Add place of context file to specific submodel indicated by the name
 */
void Unfolding::add_context_place_to_submodel(const std::string& _name, PlaceNodePtr _place){
    SubmodelHolderPtr temp = get_submodel_holder_by_name(_name);
    if(temp != nullptr){
        temp->add_context_place(_place);
    }else{
        SubmodelHolderPtr new_th = std::make_shared<SubmodelHolder>(_name);
        new_th->add_context_place(_place);
        submodelHolders.push_back(new_th);
    }
}

<<<<<<< HEAD

/**
 * Get the string line by line and find if it contains a defined string and then process it
 * 
=======
/** Read code in lna file and convert to object
>>>>>>> hadt
 */
void Unfolding::analyseLnaFile(const std::string type){
    if(type == "context"){
        ptr_pointer_end = _context_lines.end();
        ptr_pointer_line = _context_lines.begin();
    }else if(type == "solidity"){
        ptr_pointer_end = _sol_lines.end();
        ptr_pointer_line = _sol_lines.begin();
    }
    
    std::string current_submodel_name;
    while (ptr_pointer_line != ptr_pointer_end){       
        if(retrieve_string_element(*ptr_pointer_line,1," ") == "Function:"){ 
            current_submodel_name = retrieve_string_element(*ptr_pointer_line,2," ");
        }else{
            std::string keyword = get_first_alpha_only_string(*ptr_pointer_line);
            if(keyword == TRANSITION_TOKEN){
                TransitionNodePtr transition = handleTransition(ptr_pointer_line,ptr_pointer_end);
                if(type == "context"){
                    add_context_transition_to_submodel(current_submodel_name,transition);
                }else if(type == "solidity"){
                    add_solidity_transition_to_submodel(current_submodel_name,transition);
                }
            }else if(keyword == PLACE_TOKEN){
                PlaceNodePtr place = handlePlace(ptr_pointer_line,ptr_pointer_end);
                if(type == "context"){
                    add_context_place_to_submodel(current_submodel_name,place);
                }else if(type == "solidity"){
                    add_solidity_place_to_submodel(current_submodel_name,place);
                }
            }else if(keyword == TYPE_TOKEN){
                ColorNodePtr color = handleColor(ptr_pointer_line,ptr_pointer_end);
                model->add_member(color);
            }else if(keyword == FUNCTION_TOKEN){
                FunctionNodePtr function = handleFunction(ptr_pointer_line,ptr_pointer_end);
                model->add_member(function);
            }
        }

        ptr_pointer_line++;
    }
}
/** Unfolding the solidity file by instructions in the context file  
 */
NetNodePtr Unfolding::unfolding(){
    model = std::make_shared<NetNode>("test");

    analyseLnaFile("context");

    analyseLnaFile("solidity");

    if(context == DCRContext){
        unfolding_dcr_context();
    }else if(context == FreeContext){
        unfolding_free_context();
    }

    return model;
}
/**
 * Unfolding for the Free-context
 */
void Unfolding::unfolding_free_context(){

}
<<<<<<< HEAD
/**
 * Unfolding for the DCRContext
=======
/** Unfolding the solidity file by instructions in the DCR context file  
>>>>>>> hadt
 */
void Unfolding::unfolding_dcr_context(){
    for(auto it = submodelHolders.begin(); it != submodelHolders.end(); ++it){
        string submodel_name = (*it)->get_name();
        model->add_member(make_shared<CommentNode>("\n/*\n * Function: " + submodel_name + "\n */\n"));
        if(submodel_name == "state"){
            for(size_t i = 0; i < (*it)->num_context_places(); i++){
                model->add_member((*it)->get_context_place(i));
            }

            PlaceNodePtr state_cflow = std::make_shared<PlaceNode>();
            state_cflow->set_name("cflow");
            state_cflow->set_domain("epsilon");
            state_cflow->set_init("epsilon");
            model->add_member(state_cflow);

            for(size_t i = 0; i < (*it)->num_solidity_places(); i++){
                model->add_member((*it)->get_solidity_place(i));
            }
            for(size_t i = 0; i < (*it)->num_context_transitions(); i++){
                model->add_member((*it)->get_context_transition(i));
            }
            for(size_t i = 0; i < (*it)->num_solidity_transitions(); i++){
                model->add_member((*it)->get_solidity_transition(i));
            }
        }else if(std::find(unfold_func.begin(), unfold_func.end(), submodel_name) != unfold_func.end()){
            PlaceNodePtr cflow = std::make_shared<PlaceNode>();
            cflow->set_name(submodel_name+"_cflow");
            cflow->set_domain("epsilon");
            model->add_member(cflow);
            
            for(size_t i = 0; i < (*it)->num_context_places(); i++){
                model->add_member((*it)->get_context_place(i));
            }
            for(size_t i = 0; i < (*it)->num_solidity_places(); i++){
                model->add_member((*it)->get_solidity_place(i));
            }
            for(size_t i = 0; i < (*it)->num_context_transitions(); i++){
                TransitionNodePtr temp = (*it)->get_context_transition(i);

                ArcNodePtr cflow_arc_in = std::make_shared<ArcNode>();
                cflow_arc_in->set_placeName("cflow");
                cflow_arc_in->set_label("epsilon");
                temp->add_inArc(cflow_arc_in);

                ArcNodePtr cflow_arc_out = std::make_shared<ArcNode>();
                cflow_arc_out->set_placeName(cflow->get_name());
                cflow_arc_out->set_label("epsilon");
                temp->add_outArc(cflow_arc_out);

                model->add_member(temp);
            }
            for(size_t i = 0; i < (*it)->num_solidity_transitions(); i++){
                TransitionNodePtr temp = (*it)->get_solidity_transition(i);
                if(temp->get_in_arc_by_name("S") != nullptr){
                    ArcNodePtr cflow_arc_in = std::make_shared<ArcNode>();
                    cflow_arc_in->set_placeName(cflow->get_name());
                    cflow_arc_in->set_label("epsilon");
                    temp->add_inArc(cflow_arc_in);
                }

                if(temp->get_out_arc_by_name("S") != nullptr){
                    ArcNodePtr cflow_arc_out = std::make_shared<ArcNode>();
                    cflow_arc_out->set_placeName("cflow");
                    cflow_arc_out->set_label("epsilon");
                    temp->add_outArc(cflow_arc_out);
                }

                model->add_member(temp);
            }
        }else{
            for(size_t i = 0; i < (*it)->num_context_places(); i++){
                model->add_member((*it)->get_context_place(i));
            }
<<<<<<< HEAD
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
=======
            for(size_t i = 0; i < (*it)->num_context_transitions(); i++){
                TransitionNodePtr temp = (*it)->get_context_transition(i);
>>>>>>> hadt

                ArcNodePtr cflow_arc_in = std::make_shared<ArcNode>();
                cflow_arc_in->set_placeName("cflow");
                cflow_arc_in->set_label("epsilon");
                temp->add_inArc(cflow_arc_in);

<<<<<<< HEAD
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
=======
                ArcNodePtr cflow_arc_out = std::make_shared<ArcNode>();
                cflow_arc_out->set_placeName("cflow");
                cflow_arc_out->set_label("epsilon");
                temp->add_outArc(cflow_arc_out);
>>>>>>> hadt

                model->add_member(temp);
            }
        }
    }
}

<<<<<<< HEAD
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
=======
>>>>>>> hadt
