#ifndef UNFOLDER_H_
#define UNFOLDER_H_

#include<string>
#include<list>
#include<vector>
#include<sstream>
#include<memory>
#include<iostream>
#include <cctype>
#include "../../include/LNAAnalyser.hpp"
#include "../../include/nlohmann/json.hpp"
#include "../../include/Utils.hpp"
#include "../../include/Helena.hpp"
#include "./ltl2prop/LTLtranslator.hpp"

using namespace HELENA;

class Unfolder {
    public:
        Unfolder(const StructuredNetNodePtr& _context, std::stringstream& _sol_lna_stream, const nlohmann::json& lna_json,const nlohmann::json& ltl_json);

        std::vector<std::string> FindUnfoldedFunction();

        void analyseLnaFile(std::stringstream& _sol_lna_stream);
        
        StructuredNetNodePtr unfoldModelWithDCRContext();
        std::map<std::string,std::string> UnfoldModel();

        std::string get_model_name_from_comment(const CommentNodePtr& _comment);
        
    private:
        nlohmann::json sol_information;
        nlohmann::json ltl_information;
        std::vector<std::string> unfolded_func;
        StructuredNetNodePtr cpn_model;
        StructuredNetNodePtr cpn_context;
};


#endif