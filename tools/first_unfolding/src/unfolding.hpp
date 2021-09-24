#ifndef UNFOLDING_H_
#define UNFOLDING_H_

#include<string>
#include<list>
#include<vector>
#include<sstream>
#include<memory>
#include<map>
#include<iostream>
#include<algorithm>
#include <cctype>
#include "../../nlohmann/json.hpp"

// takes a string in the given string that is bounded by 2 strings _left and _right
std::string substr_by_edge(const std::string& _str, const std::string& _left, const std::string& _right); 
// split a string into a vector<string> based on _delimiter
std::vector<std::string> split(const std::string& _str, const std::string& _delimiter);
// trim from both sides but no overwrite
std::string trim_copy(const std::string& _str);
// Get the _index[th] element from a string split by _c
std::string retrieve_string_element(const std::string& _str, const unsigned int& _index, const std::string& _delimiter);
// Remove none alpha or number or '_' characters from a given string and return
std::string removeNoneAlnum(const std::string& inp_string);

/** @class UnfoldingModel
 * 
 * hold all information about model in form of .lna code
 */ 
class UnfoldingModel{
    public:
        UnfoldingModel(const std::string& _name): name(_name){}

        void add_color(const std::string& _color);
        void add_place(const std::string& _place);
        void add_function(const std::string& _function);
        void add_transition(const std::string& _transition);

        std::string source_code();    
    private:
        std::string name;

        std::vector<std::string> parameterDef;
        std::vector<std::string> coloursDef;
        std::vector<std::string> placesDef;
        std::vector<std::string> functionDef;
        std::vector<std::string> transitionDef;
};
typedef std::shared_ptr<UnfoldingModel> UnfoldingModelPtr;

/** @class TransitionHolder
 * 
 *  hold code for transition in context and sol file
 */
class TransitionHolder{
    public:
        TransitionHolder(const std::string& _name): name(_name){}
        std::string get_name();

        void add_context(const std::string& _transition);
        std::string get_context(size_t i);
        size_t num_context();

        void add_sol(const std::string& _transition);
        std::string get_sol(size_t i);
        size_t num_sol();

        void add_sol_place(const std::string& _transition);
        std::string get_sol_place(size_t i);
        size_t num_sol_place();

    private:
        std::string name;

        std::vector<std::string> sol_places;
        std::vector<std::string> context_transition;
        std::vector<std::string> sol_transition;
};
typedef std::shared_ptr<TransitionHolder> TransitionHolderPtr;

// Static string in .lna file
const std::string ColoursDefinitions = " Colours Definitions ";
const std::string FunctionsDefinitions = " Functions Definitions ";
const std::string PLACES = " PLACES ";
const std::string TRANSITIONS = " TRANSITIONS ";

const std::list<std::string> defined_string = {
    ColoursDefinitions,
    FunctionsDefinitions,
    PLACES,
    TRANSITIONS
};
bool is_defined_string(const std::string& _name);

class Unfolding{
    public:
        Unfolding(const std::string& _context, std::stringstream& _sol_stream, nlohmann::json& _sol_json, std::stringstream& _context_stream, const std::string& param);
        UnfoldingModelPtr unfolding();
        void getUnfoldFunction(nlohmann::json& _sol_json,const std::string& param);
        void unfolding_dcr_context();
        void unfolding_free_context();

        std::string getContextStaticDefinition();
        std::string getSolStaticDefinition();

        void handleDCRContextTransitionDefinitions();
        void handleSolTransitionDefinitionsDCR();

        void handleDCRContextPlaces();
        void handleSolPlaces();
        
        void add_context_transition(const std::string& _name, const std::string& _transition);
        void add_sol_transition(const std::string& _name, const std::string& _transition);

        void add_sol_place(const std::string& _name, const std::string& _place);

        std::vector<std::string> handleElement(std::string _element, std::list<std::string>::iterator& _pointer );

        TransitionHolderPtr get_transition_hodler_by_name(const std::string& _name);

        void unfoldingTransitionInDCR();
    private:
        std::string context;
        std::string unfold_func;

        UnfoldingModelPtr model;

        std::vector<TransitionHolderPtr>  transitionHolder;

        std::list<std::string> _sol_lines;
        std::list<std::string>::iterator ptr_sol_line;

        std::list<std::string> _context_lines;
        std::list<std::string>::iterator ptr_context_line;
};

#endif