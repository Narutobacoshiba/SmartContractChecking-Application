#include "./LNAAnalyser.hpp"
#include "../Utils/Utils.hpp"

namespace HELENA{

TransitionNodePtr handleTransition(list<string>::iterator& _iter, list<string>::iterator& _end_iter){
    string keyword = retrieve_string_element(*_iter,0," ");
    if(keyword == TRANSITION_TOKEN){
        TransitionNodePtr transition = make_shared<TransitionNode>();

        string transition_name = removeNoneAlnum(retrieve_string_element(*_iter,1," "));
        transition->set_name(transition_name);

        while(_iter != _end_iter && (*_iter).find("{") == string::npos){
            ++_iter;           
        }

        int level = 0;

        do{
            if((*_iter).find("{") != string::npos){
                level++;
            }
            if((*_iter).find("}") != string::npos){
                level--;
            }

            
        }while(_iter != _end_iter && level != 0);

        return transition;
    }
    return nullptr;
}


} 
