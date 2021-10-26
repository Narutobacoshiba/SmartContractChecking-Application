#ifndef LTL2PROP_H_
#define LTL2PROP_H_

#include<string>
#include<vector>
#include<list>
#include<map>
#include<memory>
#include<sstream>
#include<iostream>
#include "../../include/nlohmann/json.hpp"

const std::string CONST_STRING = "const";
const std::string PROPOSITION_STRING = "proposition";
const std::string PROPERTY_STRING = "property";
const std::list<std::string> TokensDefine = {
    CONST_STRING,
    PROPOSITION_STRING,
    PROPERTY_STRING
};

const std::string GREATER_THAN = ">";
const std::string GREATER_THAN_OR_EQUAL_TO = ">=";
const std::string LESS_THAN = "<";
const std::string LESS_THAN_OR_EQUAL_TO = "<=";
const std::string NOT_EQUAL_TO = "!=";
const std::string EQUAL_TO = "==";
const std::list<std::string> ComparisonOperator = {
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL_TO,
    LESS_THAN,
    LESS_THAN_OR_EQUAL_TO,
    NOT_EQUAL_TO,
    EQUAL_TO
};

const std::string OR_OP = "|";
const std::string AND_OP = "&";
const std::string NOT_OP = "!";
const std::string OPEN_PARENTHESES = "(";
const std::string CLOSE_PARENTHESES = ")";
const std::list<std::string> BooleanOperator = {
    OR_OP,
    AND_OP,
    NOT_OP,
};

const std::string GLOBAL_OP = "G";
const std::string FINNALY_OP = "F";
const std::string UNTIL_OP = "U";
const std::list<std::string> LTLOperator = {
    GLOBAL_OP,
    FINNALY_OP,
    UNTIL_OP
};

const std::string OR_OP_PROP = "or";
const std::string AND_OP_PROP = "and";
const std::string NOT_OP_PROP = "not";
const std::string GLOBAL_OP_PROP = "[]";
const std::string FINNALY_OP_PROP = "<>";
const std::string UNTIL_OP_PROP = "until";

const std::string PROPOSITION_AREA = "proposition";

int precedence_of_op(std::string _op);

class LTLTranslator{
    public:
        LTLTranslator(std::stringstream& _lna_stream, const nlohmann::json& lna_json, std::stringstream& _ltl_stream);
        void handleVariable(const nlohmann::json& lna_json);
        std::map<std::string,std::string>  translate(); 

        void handleConstDefinition();
        void handlePropositionDefinition();
        
        void handlePropertyDefinition();

        std::vector<std::string> infixToPostfixExpression(const std::string& _exp);
        std::vector<std::string> splitExpression(const std::string& _exp);
        
        std::string handleNoNamePropositionDefinition(const std::string& _def);

        std::string analysePropositionExpression(const std::string& _exp);
        bool is_const_definition(const std::string& _name);
        std::string get_const_definition_value(const std::string& _name);

        bool is_global_variable(const std::string& _name);
        std::string get_global_variable_placetype(const std::string& _name);

        bool is_local_variable(const std::string& _name);
        std::string get_local_variable_placetype(const std::string& _name);

        void createMap();
    private:
        std::map<std::string,std::string> MappingOp;
        std::list<std::string> ltl_lines;
        std::list<std::string>::iterator ptr_ltl_line;

        std::list<std::string> lna_lines;
        std::list<std::string>::iterator ptr_lna_line;

        std::map<std::string,std::string> constDefinitions;
        std::map<std::string,std::string> local_variables;
        std::map<std::string,std::string> global_variables;
        std::vector<std::string> propositions;
        std::string property_string;
        int current_noname_proposition = 1;
};

#endif