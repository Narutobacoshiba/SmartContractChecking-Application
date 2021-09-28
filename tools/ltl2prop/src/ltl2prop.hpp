#ifndef LTL2PROP_H_
#define LTL2PROP_H_

#include<string>
#include<vector>
#include<list>
#include<map>
#include<memory>
#include<sstream>
#include<iostream>
#include "../../nlohmann/json.hpp"

const std::string CONST_STRING = "const";
const std::string PROPOSITION_STRING = "proposition";
const std::string PROPERTY_STRING = "property";
const std::list<std::string> defined_string = {
    CONST_STRING,
    PROPOSITION_STRING,
    PROPERTY_STRING
};
bool is_defined_string(const std::string& _name);

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

const std::string ANOTHER_STRING = " ANOTHER ";

class LTLTranslator{
    public:
        LTLTranslator(std::stringstream& _lna_stream, const nlohmann::json& lna_json, std::stringstream& _ltl_stream);
        void handleVariable(const nlohmann::json& lna_json);
        std::map<std::string,std::string>  translate(); 

        void handleConst();
        void handleProposition();
        std::string handleExpression(std::string _exp);
        std::vector<std::string> splitExpression(std::string _exp);

        bool is_const_definition(const std::string& _name);
        std::string get_const_definition_value(const std::string& _name);

        bool is_global_variable(const std::string& _name);
        std::string get_global_variable_placetype(const std::string& _name);

        bool is_local_variable(const std::string& _name);
        std::string get_local_variable_placetype(const std::string& _name);
    private:
        std::list<std::string> ltl_lines;
        std::list<std::string>::iterator ptr_ltl_line;

        std::list<std::string> lna_lines;
        std::list<std::string>::iterator ptr_lna_line;

        std::map<std::string,std::string> constDefinitions;
        std::map<std::string,std::string> local_variables;
        std::map<std::string,std::string> global_variables;
        std::vector<std::string> propositions;
};

#endif