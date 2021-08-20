//Updated on 15/8

#include <iostream>
#include <fstream>
#include <vector>
#include "DCR.cpp"
#include "CLI11.hpp"
#include "rapidxml.hpp"
#include <set>


using namespace std;
using namespace rapidxml;
xml_document<> doc;
xml_node<> * root_node = NULL;
using namespace DCR;
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
int main(int argc, char** argv)
{
    
    CLI::App app{"Solidity2CPN tool"};

    std::string DCR_XML_FILE;
    app.add_option("--xml", DCR_XML_FILE, "DCR Graph")
        ->required()
        ->check(CLI::ExistingFile);
     CLI11_PARSE(app, argc, argv);  

    vector<Event> listEvent;
    vector<Relation> listRelation;
    cout << "\nParsing my students data (sample.xml)....." << endl;
   
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
    //        std::cout<<"Relation :"<<rel.getType()<<" "<<rel.getSource()<<" "<<rel.getTarget()<<" "<<rel.getGuard()<<" "<<rel.getDE()<<"\n"; 
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
                cout<<"}\n"; 
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

    // for(auto itr = listERE.begin(); itr != listERE.end(); itr++){
    //     Event s = itr->getSource();
    //     Event t = itr->getTarget();
    //     if(itr->getTest()==""){
    //         continue;
    //     }
        
    //     std::cout<<s.getID()<<" "<<t.getID();
    //     vector<string> rel = itr->getLisRelation();
    //     for(auto itr2 = rel.begin(); itr2!=rel.end(); itr2++){
    //             string a = *itr2;
    //             cout<<"~~"<<a;
    //     }
    //     // cout<<" Rel : "<<itr->getTest();
    //     cout<<"\n";
    // }
    vector<Event> Exclude;
    vector<Event> Response;
    Marking initMarking(Exclude,listEvent,Response); 
    DCRClass myDCRClass(listEvent,initMarking,listERE);
    
    Marking mark = myDCRClass.getMarking();
    Exclude = mark.getExclude();
    Response = mark.getReponse();
    vector<Event> Include = mark.getInclude();
    std::cout<<"=========================Initial Marking====================\n";
    cout<<"Exclude { \n";
    for( auto itr = Exclude.begin();itr != Exclude.end(); itr++){
        cout<<"      "<<itr->getID()<<"\n";
    }
    cout<<"   }\n";
    cout<<"Include { \n";
    for( auto itr = Include.begin();itr != Include.end(); itr++){
        cout<<"      "<<itr->getID()<<"\n";
    }
    cout<<"   }\n";
    cout<<"Reponse { \n";
    for( auto itr = Response.begin();itr != Response.end(); itr++){
        cout<<"      "<<itr->getID()<<"\n";
    }
    cout<<"   }\n";
    std::cout<<"=========================List Event====================\n";
    vector<Event> EventInDCR = myDCRClass.getListEvent();
    cout<<"Event { \n";
    for( auto itr = EventInDCR.begin();itr != EventInDCR.end(); itr++){
        cout<<"      "<<itr->getID()<<"\n";
    }
    cout<<"  }\n";
    

    std::cout<<"=========================E  R  E====================\n";
    vector<ERE> EREinDCR = myDCRClass.getERE();
    cout<<"ERE { \n";
    for(auto itr = EREinDCR.begin(); itr!=EREinDCR.end() ; itr++){
        if(itr->getTest() != "")
        {
            cout<<itr->getSource().getID()<<"-------> "<<itr->getTarget().getID()<<" HAVE : [";
            vector<string> rel = itr->getLisRelation();
            for(auto itr2 = rel.begin(); itr2!=rel.end(); itr2++){
                string a = *itr2;
                if(a!="") cout<<a<<", ";
        }
        cout<<" ]\n";
        }
    }
    cout<<"}";
    
}