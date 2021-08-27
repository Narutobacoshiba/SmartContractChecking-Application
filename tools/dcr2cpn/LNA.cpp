#include "LNA.hpp"
using namespace std;
namespace LNA {
class FixedDcr2LnaCode {
    private:
        int event_num_int;
        std::string event_num_str;

        std::string generateListChar(char t) {
            std::string ret = "";
            if(this->event_num_int > 0){
                ret += t;
                for(int i=0; i<(this->event_num_int-1); i++){
                    ret = ret+','+t;
                } 
            }
            return ret;
        }

    public:
        FixedDcr2LnaCode(int event_num) {
            this->event_num_int = event_num;
            this->event_num_str = std::to_string(event_num);
        }

        std::string getDefaultTypeCode() {
            std::string source_code = "";
            source_code = source_code + "\n\ttype bools: range 0 .. 1;" +
                                        "\n\ttype count: range 0 .. N;"+
                                        "\n\tsubtype event_id: count range 0 .. (count'last-1);"+
                                        "\n\ttype marking_value: list [event_id] of bools with capacity N;"+
                                        "\n\ttype mvalue: struct {event_id id; bools vl;};"+
                                        "\n\ttype vchange: list [event_id] of mvalue with capacity N;"+
                                        "\n\ttype cvalue: struct {bools cv1; bools cv2;};"+
                                        "\n\ttype vcondition: list [event_id] of cvalue with capacity N;";
            return source_code;
        }

        std::string getAcceptingStateTypeCode() {
            std::string source_code = "\n\ttype as_type: struct {event_id state; bools value;};";
            return source_code;
        }

        std::string getAcceptingStatePlaceCode() {
            std::string source_code = "";
            source_code = source_code + "\n\tplace accepting_state{"+
		                                "\n\t\tdom: as_type;"+
		                                "\n\t\tinit: <({0,0})>;"+
		                                "\n\t}";
		    return source_code;
        }

        std::string getMarkingPlaceCode() {
            std::string source_code = "";
            source_code = source_code + "\n\tplace marking{"+
		                                "\n\t\tdom: marking_value*marking_value*marking_value;"+
		                                "\n\t\tinit: <(|"+this->generateListChar('0')+"|,|"+this->generateListChar('1')+"|,|"+this->generateListChar('0')+"|)>;"+
		                                "\n\t}";
		    return source_code;
        }

        std::string getDefaultFunctionsCode() {
            std::string source_code = "";
            source_code = source_code + "\n\tfunction cvalue(marking_value mv, vchange lc) -> marking_value{"+
                                        "\n\t\tmarking_value m := empty;"+
                                        "\n\t\tfor(v in mv){"+
                                        "\n\t\t\tm := m & v;"+
                                        "\n\t\t}"+
                                        "\n\t\tfor(v in lc){"+
                                        "\n\t\t\tm[v.id] := v.vl;"+
                                        "\n\t\t}"+
                                        "\n\t\treturn m;"+
                                        "\n\t}"+
                                        "\n\tfunction confirm_condition(vcondition vc) -> bools{"+
                                        "\n\t\tbools ret := 1;"+
                                        "\n\t\tfor(v in vc){"+
                                        "\n\t\t\tif(v.cv1 = 1 and v.cv2 = 0) ret := 0;"+
                                        "\n\t\t}"+
                                        "\n\t\treturn ret;"+
                                        "\n\t}"+
                                        "\n\tfunction confirm_milestone(vcondition vc) -> bools{"+
                                        "\n\t\tbools ret := 1;"+
                                        "\n\t\tfor(v in vc){"+
                                        "\n\t\t\tif(v.cv1 = 1 and v.cv2 = 1) ret := 0;"+
                                        "\n\t\t}"+
                                        "\n\t\treturn ret;"+
                                        "\n\t}";
            return source_code;
        }

        std::string getResponseExistFunctionCode() {
		    std::string source_code = "";
            source_code = source_code + "\n\tfunction response_exists(marking_value m) -> bool {"+
			                            "\n\t\tfor(v in m){"+
			                            "\n\t\t\tif(v = 1) return true;"+
			                            "\n\t\t}"+
			                            "\n\t\treturn false;"+
			                            "\n\t}";
		    return source_code;
        }

        std::string getCalAcceptingStateFunctionCode() {
            std::string excode = this->generateListChar('0');
            std::string source_code = "";
            source_code = source_code + "\n\tfunction calculate_accepting_state(as_type ast,event_id cid,marking_value current_include, marking_value current_response, marking_value next_include, marking_value next_response) -> as_type {"+\
                                        "\n\t\tmarking_value include_response_current := |"+excode+"|;"+
                                        "\n\t\tmarking_value include_response_next := |"+excode+"|;"+
                                        "\n\t\tmarking_value acceptable_set := |"+excode+"|;"+
                                        "\n\t\tmarking_value m_set := |"+excode+"|;"+
                                        "\n\t\tcount min_m_set := "+this->event_num_str+";"+
                                        "\n\t\tcount min_include_response_current := "+this->event_num_str+";"+
                                        "\n\t\tcount index := "+this->event_num_str+";"+
                                        "\n\t\tcount m_set_count := 0;"+
                                        "\n\t\tcount include_response_current_set_count := 0;"+
                                        "\n\t\tcount include_response_next_set_count := 0;"+
                                        "\n\t\tbools ret_value := 0;"+
                                        "\n\t\tevent_id ret_state := ast.state;"+
                                        "\n\t\tfor(idx in event_id){"+
                                        "\n\t\t\tif(current_include[idx] = 1 and current_response[idx] = 1) include_response_current[idx] := 1;"+
                                        "\n\t\t\tif(next_include[idx] = 1 and next_response[idx] = 1) include_response_next[idx] := 1;"+
                                        "\n\t\t\tif(idx > ast.state and include_response_current[idx] = 1) m_set[idx] := 1;"+
                                        "\n\t\t\tif(include_response_current[idx] = 1 and include_response_next[idx] = 0) acceptable_set[idx] := 1;"+
                                        "\n\t\t}"+
                                        "\n\t\tacceptable_set[cid] := 1;"+
                                        "\n\t\twhile(index > 0){"+
                                        "\n\t\t\tif(m_set[index-1] = 1){"+
                                        "\n\t\t\t\tmin_m_set := (index-1);"+
                                        "\n\t\t\t\tm_set_count := (m_set_count+1);"+
                                        "\n\t\t\t}"+
                                        "\n\t\t\tif(include_response_current[index-1] = 1){"+
                                        "\n\t\t\t\tmin_include_response_current := (index-1);"+
                                        "\n\t\t\t\tinclude_response_current_set_count := (include_response_current_set_count+1);"+
                                        "\n\t\t\t}" +
                                        "\n\t\t\tif(include_response_next[index-1] = 1) include_response_next_set_count := (include_response_next_set_count+1);"+
                                        "\n\t\t\t\tindex := (index-1);"+
                                        "\n\t\t}"+
                                        "\n\t\tif(include_response_next_set_count = 0) ret_value := 1;"+
                                        "\n\t\tif((m_set_count>0) and (acceptable_set[min_m_set]=1)){"+
                                        "\n\t\t\tret_value := 1;"+
                                        "\n\t\t\tret_state := min_m_set;"+
                                        "\n\t\t}"+
                                        "\n\t\tif((m_set_count=0) and (min_include_response_current<4)and(acceptable_set[min_include_response_current]=1)){"+
                                        "\n\t\t\tret_value := 1;"+
                                        "\n\t\t\tret_state := min_include_response_current;"+
                                        "\n\t\t}"+
                                        "\n\t\treturn {ret_state,ret_value};"+
                                        "\n\t}";
            return source_code;
        }

        std::string getLivenessProp() {
            std::string source_code = "";
            source_code = source_code + "\n\tproposition is_accepting_state:"+
                                        "\n\t\texists (p in accepting_state | p->1.value = 1);";
            return source_code;
        }

        std::string getDeadlockFreeProp() {
            std::string source_code = "";
            source_code = source_code + "\n\tproposition deadlock_free:"+
                                        "\n\t\texists (v in marking | response_exists(v->3)) = false;";
            return source_code;
        }
};

std::string vector2string(std::vector<std::string> vec, std::string separator) {
    std::vector<std::string>::iterator begin = vec.begin();
    std::vector<std::string>::iterator end = vec.end();
    std::ostringstream result;
    if (begin != end)
        result << *begin++;
    while (begin != end)
        result << separator << *begin++;
    return result.str();
}

class ArcsParams {
    private:
        std::map<std::string, std::vector<std::string>> params;

    public:
        ArcsParams(){}

        bool isKeyExists(std::string key) {
            if ( this->params.find(key) == this->params.end() ) {
                return false;
            } else {
                return true;
            }
        }

        void addKey(std::string key_name) {
            std::vector<std::string> vec;
            this->params.insert(std::make_pair(key_name, vec));
        }

        void addParam(std::string key_name, std::string param) {
            if(this->isKeyExists(key_name))
            {
                this->params[key_name].push_back(param);
            }
        }
        
        std::string getKeyAsListIn() {
            std::map<std::string, std::vector<std::string>>::iterator it_begin = this->params.begin();
            std::ostringstream code;
            if(it_begin != this->params.end()){
                code << it_begin->first;
                it_begin++;
            }
            while(it_begin != this->params.end()){
                code << ',' << it_begin->first;
                it_begin++;
            }
            return code.str();
        }

        std::string getKeyAsListOut(std::string func_name) {
            std::map<std::string, std::vector<std::string>>::iterator it_begin = this->params.begin();
            std::ostringstream code;

            if(it_begin != this->params.end()){
                if(it_begin->second.empty()){
                    code << it_begin->first;
                } else{
                    code << func_name << "(" << it_begin->first << ",|" << vector2string(it_begin->second,",") << "|)";
                }
                it_begin++;
            }
            while(it_begin != this->params.end()){
                if(it_begin->second.empty()){
                    code << "," << it_begin->first;
                } else{
                    code << "," << func_name << "(" << it_begin->first << ",|" << vector2string(it_begin->second,",") << "|)";
                }
                it_begin++;
            }
            return code.str();
        }
};

class LNATransition {
    private:
        std::string name;
        std::map<std::string, ArcsParams*> inArcs;
        std::map<std::string, std::vector<std::string>> guardCondition;
        std::string priority;

    public:
        LNATransition(std::string name, int id) {
            this->name = name;

            std::string init_inarc = "marking";
            std::vector<std::string> init_inarc_params = {"execute","include","response"};
            this->generateInArcsParams(init_inarc,init_inarc_params);

            std::string init_outarc_param = "{";
            init_outarc_param = init_outarc_param + std::to_string(id) + ",1}";
            this->addOutArcsParams(init_inarc,"execute", init_outarc_param);

            std::string init_guard = "";
            init_guard = init_guard + "(include[" + std::to_string(id) + "] = 1)";
            this->guardCondition["normal"] = std::vector<std::string>{init_guard};
            this->guardCondition["condition"] = std::vector<std::string>();
            this->guardCondition["milestone"] = std::vector<std::string>();
        }

        bool isKeyExists(std::string key) {
            if ( this->inArcs.find(key) == this->inArcs.end() ) {
                return false;
            } else {
                return true;
            }
        }

        void generateInArcsParams(std::string name, std::vector<std::string> params){
            this->inArcs.insert(std::make_pair(name, new ArcsParams()));
            for (auto i = params.begin(); i != params.end(); ++i){
                this->inArcs[name]->addKey(*i);
            }
        }

        void addOutArcsParams(std::string arc_name, std::string type_name, std::string param){
            if(isKeyExists(arc_name)){
                this->inArcs[arc_name]->addParam(type_name, param);
            }
        }

        void addConditionGuard(std::string condition) {
            this->guardCondition["condition"].push_back(condition);
        }

        void addMilestoneGuard(std::string milestone) {
            this->guardCondition["milestone"].push_back(milestone);
        }
        
        void addNormalGuard(std::string conditon) {
            this->guardCondition["normal"].push_back(conditon);
        }

        std::string getCode() {
            std::ostringstream source_code;

            source_code << "\n\n\ttransition " << this->name << "{\n\t\tin {";
            for (auto it = this->inArcs.begin(); it != this->inArcs.end(); it++) {
                source_code << "\n\t\t\t" << it->first << ": <(" << it->second->getKeyAsListIn() << ")>;";
            }
            source_code << "\n\t\t}\n\t\tout {";
            for (auto it = this->inArcs.begin(); it != this->inArcs.end(); it++) {
                source_code << "\n\t\t\t" << it->first << ": <(" << it->second->getKeyAsListOut("cvalue") << ")>;";
            }
            source_code << "\n\t\t}\n\n\t\tguard: ";
            source_code << vector2string(this->guardCondition["normal"]," and ");

            if(this->guardCondition["condition"].size() > 0){
                source_code << " and (confirm_condition(|" << vector2string(this->guardCondition["condition"],",") << "|) = 1)";
            }

            if(this->guardCondition["milestone"].size() > 0){
                source_code << " and (confirm_milestone(|" << vector2string(this->guardCondition["milestone"],",") << "|) = 1)";
            }
            source_code << ";";

            if(this->priority.length()) {
                source_code << "\n\n\t\tpriority: " << this->priority << ";";
            }
            source_code << "\n\t}";

            return source_code.str();
        }
};

class LNABodyCode {
    private:
        int events_num;
        std::map<std::string, std::string> events_id;
        std::map<std::string, LNATransition*> events_transition;
        std::string name;
        std::vector<std::string> types;
        std::vector<std::string> places;
        std::vector<std::string> functions;
        std::vector<std::string> proposition;

    public:
        LNABodyCode(std::string name, int events_num){
            this->name = name;
            this->events_num = events_num;
        }

        void addTransition(std::string transition_name, int transition_id) {
            this->events_id[transition_name] = std::to_string(transition_id);
            this->events_transition[transition_name] = new LNATransition(transition_name,transition_id);
        }

        LNATransition* getTransition(std::string transition_name){
            return this->events_transition[transition_name];
        }

        std::string getEventId(std::string event_name) {
            return this->events_id[event_name];
        }

        void addType(std::string type_code) {
            this->types.push_back(type_code);
        }
        
        void addPlace(std::string place_code) {
            this->places.push_back(place_code);
        }

        void addProposition(std::string proposition_code) {
            this->proposition.push_back(proposition_code);
        }

        void addFunction(std::string function_code) {
            this->functions.push_back(function_code);
        }

        std::string getCode() {
            std::ostringstream code;

            code << this->name << "(N := " << to_string(this->events_num) <<
            << "){" << "\n\n\t/* ------ type definition ------- */";
            for(auto it = this->types.begin(); it != this->types.end(); it++) {
                code << "\n" << *it;
            }

            code << "\n\n\n\t/* ------ place definition ------- */";
            for(auto it = this->places.begin(); it != this->places.end(); it++) {
                code << "\n" << *it;
            }

            code << "\n\n\n\t/* ------ function definition ------- */";
            for(auto it = this->functions.begin(); it != this->functions.end(); it++) {
                code << "\n" << *it;
            }

            code << "\n\n\n\t/* ------ transition definition ------- */";
            for(auto it = this->events_transition.begin(); it != this->events_transition.end(); it++) {
                code << "\n" << it->second->getCode();
            }

            code << "\n\n\n\t/* ------ proposition definition ------- */";
            for(auto it = this->proposition.begin(); it != this->proposition.end(); it++) {
                code << "\n" << *it;
            }

            code << "\n}";

            return code.str();
        }
};

}