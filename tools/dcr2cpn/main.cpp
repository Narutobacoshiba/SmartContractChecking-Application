#include <iostream>
#include <fstream>
#include <vector>
#include "DCR.cpp"
#include "CLI11.hpp"
#include "rapidxml.hpp"
#include <set>
#include "LNA.cpp"

using namespace std;
using namespace rapidxml;
xml_document<> doc;
xml_node<> * root_node = NULL;
using namespace DCR;
using namespace LNA;
bool isSubOf2(string ParentNameInput, string EventNameInput, vector<Event> listEvent);
//This function return if a Event is a sub Event of A Nesting Event
// This function using basic Backtracking Algorithm
bool isSubOf2(string ParentNameInput, string EventNameInput, vector<Event> listEvent){
  
    string ParentName = ParentNameInput;
    string EventName = EventNameInput;
    if(ParentNameInput=="") return false;
    else{
    for(auto itrEvent = listEvent.begin() ; itrEvent != listEvent.end(); itrEvent++){
                    Event e = *itrEvent;
                    if(e.getID() == EventName){
                           if(e.getParent() == ParentNameInput){
                               return true;
                           }else{
                             return (isSubOf2(ParentNameInput,e.getParent(),listEvent));
                           } 

                    }

            }
    }
    return false;
};


string removeNoneAlnum(string inp_string)
{
    string s = inp_string;
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] < 'A' || s[i] > 'Z') &&
            (s[i] < 'a' || s[i] > 'z') && 
            (s[i] < '0' || s[i] > '9'))
        {  
            s.erase(i, 1);
            i--;
        }
    }
    return s;
}

class TranslatorDCR2LNA{
    private:
        vector<Event> EventInDCR;
        vector<ERE> EREinDCR;
        string name;

    public:
        TranslatorDCR2LNA(vector<Event> EventInDCR, vector<ERE> EREinDCR, string name){
            this->EventInDCR = EventInDCR;
            this->EREinDCR = EREinDCR;
            this->name = name;
        }

        map<string, string> translate(){
            map<string, string> ret;

            LNABodyCode* lbcode = new LNABodyCode(this->name,this->EventInDCR.size());
            FixedDcr2LnaCode fxcode(this->EventInDCR.size());

            int id = 0;
            for(auto it = this->EventInDCR.begin(); it != this->EventInDCR.end(); it++) {
                lbcode->addTransition(removeNoneAlnum(it->getID()),id);
                id++;
            }
            
            this->translateRelation2LNA(lbcode);
            
            string cdeadloc = this->generateCDeadlockLNA(lbcode,fxcode);
            ret["deadlock"] = cdeadloc;

            return ret;
        }

        void translateRelation2LNA(LNABodyCode *lbcode) {
            map<string, bool> events_self_response;
            for(auto it = this->EventInDCR.begin(); it != this->EventInDCR.end(); it++) {
                events_self_response[removeNoneAlnum(it->getID())] = false;
            }

            for(auto it = this->EREinDCR.begin(); it != this->EREinDCR.end(); it++) {
                string eventSource = removeNoneAlnum(it->getSource().getID());
                string eventDest = removeNoneAlnum(it->getTarget().getID());
                vector<string> listRelation = it->getLisRelation();
                for(auto rel = listRelation.begin(); rel != listRelation.end(); rel++){
                    string param = "{";
                    if((*rel).compare("include") == 0){
                        param = param + lbcode->getEventId(eventDest)+",1}";
                        lbcode->getTransition(eventSource)->addOutArcsParams("marking","include",param);
                    }
                    if((*rel).compare("exclude") == 0){
                        param = param + lbcode->getEventId(eventDest)+",0}";
                        lbcode->getTransition(eventSource)->addOutArcsParams("marking","include",param);
                    }
                    if((*rel).compare("response") == 0){
                        if(eventSource.compare(eventDest) == 0){
                            events_self_response[eventSource] = true;
                        }
                        param = param + lbcode->getEventId(eventDest)+",1}";
                        lbcode->getTransition(eventSource)->addOutArcsParams("marking","response",param);
                    }
                    if((*rel).compare("condition") == 0){
                        param = param + "include[" + lbcode->getEventId(eventSource) + "],execute[" + lbcode->getEventId(eventSource) + "]}";
                        lbcode->getTransition(eventDest)->addConditionGuard(param);
                    }
                    if((*rel).compare("milestone") == 0){
                        param = param + "include[" + lbcode->getEventId(eventSource) + "],response[" + lbcode->getEventId(eventSource) + "]}";
                        lbcode->getTransition(eventDest)->addMilestoneGuard(param);
                    }
                }
            }

            for(auto it = events_self_response.begin(); it != events_self_response.end(); it++){
                if(!(it->second)){
                    string param = "{";
                    param = param + lbcode->getEventId(it->first)+",0}";
                    lbcode->getTransition(it->first)->addOutArcsParams("marking","response",param);
                }
            }
        }

        string generateCDeadlockLNA(LNABodyCode* lbcode, FixedDcr2LnaCode fxcode) {
            lbcode->addType(fxcode.getDefaultTypeCode());
            lbcode->addPlace(fxcode.getMarkingPlaceCode());
            lbcode->addFunction(fxcode.getDefaultFunctionsCode());
            lbcode->addFunction(fxcode.getResponseExistFunctionCode());
            lbcode->addProposition(fxcode.getDeadlockFreeProp());

            return lbcode->getCode();    
        }
};

DCRClass readDCRFromXML(string DCR_XML_FILE){


    vector<Event> listEvent;
    vector<Relation> listRelation;
   
    // Read the xml file
    ifstream theFile (DCR_XML_FILE);
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');
   
    // Parse the buffer
    doc.parse<0>(&buffer[0]);
    root_node = doc.first_node("DCRModel");
    int nEvent = 0 ;
    //Take name of attribute of Event by iterator eacch sub_node of node  have name Events in XML
    for(xml_node<>* events_node = root_node->first_node("events") ; events_node; events_node = events_node -> next_sibling()){
        string id,labels,roles,datatype,parent,type;
        if(events_node ->first_node("id")!=nullptr){
            id = events_node ->first_node("id")->value();
        }else{
            id = "";
        }
        if(events_node ->first_node("label")!=nullptr){
            labels = events_node ->first_node("label")->value();
        }else{
            labels = "";
        }
        if(events_node ->first_node("roles")!=nullptr){
            roles = events_node ->first_node("roles")->value();
        }else{
            roles = "";
        }
        if(events_node ->first_node("datatype")!=nullptr){
            datatype = events_node ->first_node("datatype")->value();
        }else{
            datatype = "";
        }
        if(events_node ->first_node("parent")!=nullptr){
            parent = events_node ->first_node("parent")->value();
        }else{
            parent = "";
        }
        if(events_node ->first_node("type")!=nullptr){
            type = events_node ->first_node("type")->value();
        }else{
            type = "";
        }
        if(id!="")
        {
            listEvent.push_back(Event(id,labels,roles,datatype,parent,type));
        }
    }
    int numofEvent =0 ,numOfRalation=0;
    for(auto itr = listEvent.begin(); itr!= listEvent.end();itr++){
        numofEvent++;
    }
    //Take name of attribute of Rules by iterator eacch sub_node of node  have name Rules in XML
    for(xml_node<>* rule_node = root_node->first_node("rules") ; rule_node; rule_node = rule_node -> next_sibling()){
        //Relation(string Type,string Source, string Target, string Guard, string DurationExpression){
        string type,source,target,guard,de;
        if(rule_node->first_node("type")!=nullptr){
            type = rule_node->first_node("type")->value();
        }else{
            type = "";
        }
        if(rule_node->first_node("source")!=nullptr){
            source = rule_node->first_node("source")->value();
        }else{
            source = "";
        }
        if(rule_node->first_node("target")!=nullptr){
            target = rule_node->first_node("target")->value();
        }else{
            target = "";
        }
        if(rule_node->first_node("durationexpression")!=nullptr){
            de = rule_node->first_node("durationexpression")->value();
        }else{
            de = "";
        }
        if(rule_node->first_node("guard")!=nullptr){
            guard = rule_node->first_node("guard")->value();
        }else{
            guard = "";
        }
        if(type!=""){
            listRelation.push_back(Relation(type,source,target,guard,de));
        }
    }
    // for(auto itr = listRelation.begin(); itr!= listRelation.end();itr++){
    //         Relation rel = *itr;
    //        cout<<"Relation :"<<rel.getType()<<" "<<rel.getSource()<<" "<<rel.getTarget()<<" "<<rel.getGuard()<<" "<<rel.getDE()<<"\n"; 
    // };
    vector<ERE> listERE;

    //Add all couple [E-E](Event-i <> Event-J  to  vector (2 Events have to have differents ID)
    for(auto itr1 = listEvent.begin(); itr1 != listEvent.end(); itr1++){
        for(auto itr2 = listEvent.begin(); itr2 != listEvent.end(); itr2++ ){
            
            Event source = *itr1;
            Event target = *itr2;
            if(source.getID() == target.getID()){
                continue;
            }
            else{
                // cout<<"ahihi";
                vector<string> nilVector;
                listERE.push_back(ERE(source,target,nilVector));
            }   
        }
    }

    //Iterator all Relation in vector 
    for(auto itrRelation = listRelation.begin() ; itrRelation != listRelation.end(); itrRelation++){
            Relation rel = *itrRelation;
            string sourceName = rel.getSource();
            string targetName = rel.getTarget();
            Event source,target;
            int count = 0;
            //Iterator all Event of list Events to take Event Source and Event Target
            for(auto itrEvent = listEvent.begin() ; itrEvent!=listEvent.end(); itrEvent++ ){
                if(itrEvent->getID()==targetName){
                    target=*itrEvent;
                    count++;
                }
                if(itrEvent->getID()==sourceName){
                    source=*itrEvent;
                    count++;
                }
                if(count==2){
                    break;
                }
                
            }
            //Iterator all ERE in list ERE 
            for(auto itrERE = listERE.begin(); itrERE!=listERE.end(); itrERE++){
                    ERE ere =*itrERE;
                    //Check if current index ERE have Event-Source and Event-Target same of Relation..
                    if(ere.getSource().getID() == sourceName && ere.getTarget().getID() == targetName){
                        itrERE->setText(itrERE->getTest()+" ; "+itrRelation->getType());
                        vector<string> a = itrERE->getLisRelation();
                        a.push_back(itrRelation->getType());
                        itrERE->setListRelation(a);         
                        break;
                    }
                } 
            //If 2 Events is nesting, add Realtion to all ERE have Event-Soure and Event-Target that is sub Event of this 2 nesting Event
            if(source.getType()=="nesting" && target.getType()=="nesting"){
                // cout<<"2 Nesting"<< sourceName<<" "<<targetName <<"{\n";
                for(auto itrERE = listERE.begin(); itrERE!=listERE.end(); itrERE++){
                    ERE ere =*itrERE;
                    if(isSubOf2(sourceName,ere.getSource().getID(),listEvent) && isSubOf2(targetName,ere.getTarget().getID(),listEvent) ){ 
                        // cout<<"Couple : "<<ere.getSource().getID()<<"~~ "<<ere.getTarget().getID()<<"\n";
                        vector<string> a = itrERE->getLisRelation();
                        a.push_back(itrRelation->getType());
                        itrERE->setListRelation(a); 
                        itrERE->setText(itrERE->getTest()+" ; "+itrRelation->getType());
                    }
                    
                }
            }
            //Check if one of 2 Event is nesting 
            else if(source.getType()=="nesting"){
               for(auto itrERE = listERE.begin(); itrERE!=listERE.end(); itrERE++){
                    ERE ere =*itrERE;
                    if(isSubOf2(sourceName,ere.getSource().getID(),listEvent) && ere.getTarget().getID() == targetName){
                         vector<string> a = itrERE->getLisRelation();
                        a.push_back(itrRelation->getType());
                        itrERE->setListRelation(a); 
                        itrERE->setText(itrERE->getTest()+" ; "+itrRelation->getType());
                    }
                }      
            }else if(target.getType()=="nesting"){
                  for(auto itrERE = listERE.begin(); itrERE!=listERE.end(); itrERE++){
                    ERE ere =*itrERE;
                    if(ere.getSource().getID()==sourceName && isSubOf2(targetName,ere.getTarget().getID(),listEvent)){
                        vector<string> a = itrERE->getLisRelation();
                        a.push_back(itrRelation->getType());
                        itrERE->setListRelation(a); 
                        itrERE->setText(itrERE->getTest()+" ; "+itrRelation->getType()); 
                    }
                }     
            }
    }

    vector<Event> Exclude;
    vector<Event> Response;
    Marking initMarking(Exclude,listEvent,Response); 
    DCRClass myDCRClass(listEvent,initMarking,listERE);
    return myDCRClass;
}


int main(int argc, char** argv)
{   
    CLI::App app{"Solidity2CPN tool"}; 
    string DCR_XML_FILE;
    string OUT_FILE_NAME = "";
    app.add_option("--xml", DCR_XML_FILE, "DCR Graph")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--out_file", OUT_FILE_NAME, "DCR Graph");
     CLI11_PARSE(app, argc, argv); 
    DCRClass dcrClass =  readDCRFromXML(DCR_XML_FILE);
    vector<Event> EventInDCR = dcrClass.getListEvent();
    vector<ERE> EREinDCR = dcrClass.getERE();
    TranslatorDCR2LNA translator(EventInDCR,EREinDCR,"test");
    map<string, string> code = translator.translate();
    
    ofstream myfile;
    if(OUT_FILE_NAME.compare("") == 0){
        myfile.open (DCR_XML_FILE.substr(0, DCR_XML_FILE.find('.'))+".lna");
    }else{
        myfile.open (OUT_FILE_NAME+".lna");
    }
    
    myfile << code["deadlock"];
    myfile.close();
    return 0;
}