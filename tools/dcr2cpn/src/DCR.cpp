#include "../include/DCR.hpp"

namespace DCR2CPN{
    

std::string Event::getID(){
    return id;
};
std::string Event::getRoles(){
    return roles;
};
std::string Event::getDataType(){
    return dataType;
};
std::string Event::getParent(){
    return parent;
};
std::string Event::getLabel(){
    return label;
};
std::string Event::getType(){
    return type;
}
        
std::string Relation::getType(){
    return type;
}
std::string Relation::getSource(){
    return source;
}
std::string Relation::getTarget(){
    return target;
}
std::string Relation::getGuard(){
    return guard;
}
std::string Relation::getDE(){
    return durationExpression;
}
    

Event  ERE::getSource(){
    return source;
}
Event ERE::getTarget(){
    return target;
}
std::vector<std::string> ERE::getLisRelation(){
    return listRelation;
}
void ERE::addRelation(std::string i){
    listRelation.push_back(i);   
};
void ERE::addToTest(int i ){
    test = test + std::to_string(i);
}
std::string ERE::getTest(){
    return test;
}
void ERE::setText(std::string t){
    test = t;
}
void ERE::setListRelation(std::vector<std::string> ListRelation){
    listRelation = ListRelation;
}

std::vector<Event> Marking::getExclude(){
    return Exclude;
}
std::vector<Event> Marking::getInclude(){
    return Include;
}
std::vector<Event> Marking::getResponse(){
    return Response;
}
void Marking::setExclude(std::vector<Event> exclude){
    Exclude = exclude;
}
void Marking::setInclude(std::vector<Event> include){
    Include = include;
}
void Marking::setResponse(std::vector<Event> response){
    Response = response;
}

void DCRClass::setEvent(std::vector<Event> ListEvent){
    listEvent = ListEvent;
}
void DCRClass::setMarking(Marking InitMarking){
    initMarking = InitMarking;
}
void DCRClass::setERE(std::vector<ERE> ListERE){
    listERE = ListERE;
}
std::vector<Event> DCRClass::getListEvent(){
    return listEvent;
}
Marking DCRClass::getMarking(){
    return initMarking;
}
std::vector<ERE> DCRClass::getERE(){
    return listERE;
}
std::string DCRClass::description(){
    return  "";
}

}