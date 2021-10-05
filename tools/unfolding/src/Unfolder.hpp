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
#include "../../include/LNAAnalyser.hpp"
#include "../../include/Utils.hpp"
#include "../../include/Helena.hpp"

using namespace HELENA;

/** @class SubmodelHolder
 * 
 *  hold code for a submodel in context and sol file
 */
class SubmodelHolder{
    public:
        SubmodelHolder(const std::string& _name): name(_name){}
        std::string get_name();

        void add_context_transition(TransitionNodePtr _transition);
        TransitionNodePtr get_context_transition(size_t i);
        size_t num_context_transitions();

        void add_solidity_transition(TransitionNodePtr _transition);
        TransitionNodePtr get_solidity_transition(size_t i);
        size_t num_solidity_transitions();

        void add_context_place(PlaceNodePtr _place);
        PlaceNodePtr get_context_place(size_t i);
        size_t num_context_places();

        void add_solidity_place(PlaceNodePtr _place);
        PlaceNodePtr get_solidity_place(size_t i);
        size_t num_solidity_places();
        

    private:
        std::string name;

        std::vector<PlaceNodePtr> context_places;
        std::vector<PlaceNodePtr> solidity_places;
        std::vector<TransitionNodePtr> context_transitions;
        std::vector<TransitionNodePtr> solidity_transitions;
};
typedef std::shared_ptr<SubmodelHolder> SubmodelHolderPtr;

// context
const std::string DCRContext = "dcr";
const std::string FreeContext = "free";

// Static string in .lna file
const std::string ColoursDefinitions = " Colours Definitions ";
const std::string FunctionsDefinitions = " Functions Definitions ";
const std::string PLACES = " PLACES ";
const std::string TRANSITIONS = " TRANSITIONS ";

const std::list<std::string> DefinitionsList = {
    ColoursDefinitions,
    FunctionsDefinitions,
    PLACES,
    TRANSITIONS
};

class Unfolding{
    public:
        Unfolding(const std::string& _context, std::stringstream& _sol_stream, std::stringstream& _context_stream, const std::string& param);
        NetNodePtr unfolding();

        void unfolding_dcr_context();
        void unfolding_free_context();

        void analyseLnaFile(const std::string type);
        
        void add_context_transition_to_submodel(const std::string& _name, TransitionNodePtr _transition);
        void add_solidity_transition_to_submodel(const std::string& _name, TransitionNodePtr _transition);

        void add_solidity_place_to_submodel(const std::string& _name, PlaceNodePtr _place);
        void add_context_place_to_submodel(const std::string& _name, PlaceNodePtr _place);

        SubmodelHolderPtr get_submodel_holder_by_name(const std::string& _name);

    private:
        std::string context;
        std::vector<std::string> unfold_func;

        NetNodePtr model;

        std::vector<SubmodelHolderPtr>  submodelHolders;

        std::list<std::string> _sol_lines;
        std::list<std::string> _context_lines;

        std::list<std::string>::iterator ptr_pointer_end;
        std::list<std::string>::iterator ptr_pointer_line;
};

#endif