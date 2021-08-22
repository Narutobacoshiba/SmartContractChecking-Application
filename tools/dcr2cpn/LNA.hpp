#ifdef LNA_HPP
#define LNA_HPP
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <sstream> 

namespace LNA{
string vector2string(vector<string> vec, string separator);
class FixedDcr2LnaCode {
    private:
        int event_num_int;
        string event_num_str;
        string generateListChar(char t);
    
    public:
        FixedDcr2LnaCode(int event_num);
        string getDefaultTypeCode();
        string getAcceptingStateTypeCode();
        string getAcceptingStatePlaceCode();
        string getMarkingPlaceCode();
        string getDefaultFunctionsCode();
        string getResponseExistFunctionCode();
        string getCalAcceptingStateFunctionCode();
        string getLivenessProp();
        string getDeadlockFreeProp();
};

class ArcsParams {
    private:
        map<string, vector<string>> params;
    public:
        ArcsParams();
        bool isKeyExists(string key);
        void addKey(string key_name);
        void addParam(string key_name, string param);
        string getKeyAsListIn();
        string getKeyAsListOut(string func_name);
};

class LNATransition {
    private:
        string name;
        map<string, ArcsParams*> inArcs;
        map<string, vector<string>> guardCondition;
        string priority;

    public:
        LNATransition(string name, int id);
        bool isKeyExists(string key);
        void generateInArcsParams(string name, vector<string> params);
        void addOutArcsParams(string arc_name, string type_name, string param);
        void addConditionGuard(string condition);
        void addMilestoneGuard(string milestone);
        void addNormalGuard(string conditon);
        string getCode();
};

class LNABodyCode {
    private:
        map<string, string> events_id;
        map<string, LNATransition*> events_transition;
        string name;
        vector<string> types;
        vector<string> places;
        vector<string> functions;
        vector<string> proposition;

    public:
        LNABodyCode(string name);
        void addTransition(string transition_name, int transition_id);
        LNATransition* getTransitionName(string transition_name);
        string getEventId(string event_name);
        void addType(string type_code);
        void addPlace(string place_code);
        void addProposition(string proposition_code);
        void addFunction(string function_code);
        string getCode();
};

}
#endif