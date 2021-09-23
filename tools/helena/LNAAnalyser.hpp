#ifndef HELENA_LNAANALYSER_H_
#define HELENA_LNAANALYSER_H_

#include "./Helena.hpp"
#include <list>
#include <string>

using namespace std;

namespace HELENA{

const string TRANSITION_TOKEN = "transition";
const string PLACE_TOKEN = "place";
const string FUNCTION_TOKEN = "function";
const string COLOR_TOKEN = "type"; 

const list<string> TokenList {
    TRANSITION_TOKEN,
    PLACE_TOKEN,
    FUNCTION_TOKEN,
    COLOR_TOKEN
};

ParameterNodePtr handleParameter(list<string>::iterator& _iter, list<string>::iterator& _end_iter);

TransitionNodePtr handleTransition(list<string>::iterator& _iter, list<string>::iterator& _end_iter);

PlaceNodePtr handlePlace(list<string>::iterator& _iter, list<string>::iterator& _end_iter);

ColorNodePtr handleColor(list<string>::iterator& _iter, list<string>::iterator& _end_iter);

FunctionNodePtr handleFunction(list<string>::iterator& _iter, list<string>::iterator& _end_iter);

} // namespace HELENA

#endif