#ifndef DCR2CPN_TRANSLATOR_H_
#define DCR2CPN_TRANSLATOR_H_

#include "DCR.hpp"
#include "Helena.hpp"
#include <string>

namespace DCR2CPN {

DCRClass readDCRFromXML(const std::string& DCR_XML_FILE);

class SubNet {
    public:
        SubNet(const std::string& _name, const std::string& _id): name(_name), id(_id) {}
        
        std::string get_name();
        std::string get_id();

        void add_executecvparams(const std::string& param);
        void add_includecvparams(const std::string& param);
        void add_responsecvparams(const std::string& param);

        void add_cmilestone(const std::string& param);
        void add_ccondition(const std::string& param);

        TransitionNodePtr createTransition();

    private:
        std::string name;
        std::string id;

        std::vector<std::string> executeCVParams;
        std::vector<std::string> includeCVParams;
        std::vector<std::string> responseCVParams;

        std::vector<std::string> cMilestone;
        std::vector<std::string> cCondition;
};
typedef std::shared_ptr<SubNet> SubNetPtr;

class Translator {
    public:
        Translator(DCRClass _dcrClass): dcrClass(_dcrClass) {}

        void add_subnet(const std::string& subnet_name, SubNetPtr _subnet);
        SubNetPtr get_subnet_by_name(const std::string& subnet_name);
        std::string get_subnet_id(const std::string& subnet_name );

        NetNodePtr translate();

        void generateInitColours();
        void generateInitPlaces();
        void generateInitFunctions();

    private:
        DCRClass dcrClass;
        NetNodePtr net;
        std::map<std::string, SubNetPtr> subnets;
        std::vector<SubNetPtr> vsubnets;
};

}

#endif