#ifdef DCR_HPP
#define DCR_HPP
#include<vector>
#include<string>
#include<iostream>
namespace DCR{
class Event{
    public:
        Event();
        Event(string ID,string Label, string Roles, string Datatype, string Parent ,string Type);
        string getID();
        string getRoles();
        string getDataType();
        string getParent();
        string getLabel();
        string getType();
        
    private:
        string id;
        string label;
        string roles;
        string dataType;
        string parent;
        string type;

};
class Relation
{
private:
    string type;
    string source;
    string target;
    string guard;
    string durationExpression;
    
public:
    Relation(){};
    Relation(string Type,string Source, string Target, string Guard, string DurationExpression);
    string getType();
    string getSource();
    string getTarget();
    string getGuard();
    string getDE();
    
};


class ERE{
    public:
        ERE(){};
        ERE(Event Source, Event Target, vector<string> Relation);
        Event  getSource();
        Event getTarget();
        vector<string> getLisRelation();
        void addRelation(string i);
        void addToTest(int i );
        string getTest();
        void setText(string t);
        void setListRelation(vector<string> ListRelation);
    private:
        Event source;
        Event target;
        vector<string> listRelation;
        string test="";

};
class Marking{
private:
    vector<Event> Exclude;
    vector<Event> Include;
    vector<Event> Reponse;
public:
    Marking(){};
    Marking(vector<Event> exclude, vector<Event> include, vector<Event> reponse);
    vector<Event> getExclude();
    vector<Event> getInclude();
    vector<Event> getReponse();
    void setExclude(vector<Event> exclude);
    void setInclude(vector<Event> include);
    void setReponse(vector<Event> reponse);
};
class DCRClass{
    public:
        DCRClass();
        DCRClass(vector<Event> ListEvent, Marking InitMarking, vector<ERE> ListERE);
        void setEvent(vector<Event> ListEvent);
        void setMarking(Marking InitMarking);
        void setERE(vector<ERE> ListERE);
        vector<Event> getListEvent();
        Marking getMarking();
        vector<ERE> getERE();
        string description();
    private:
        vector<Event> listEvent;
        Marking initMarking;
        vector<ERE> listERE;
        
};
}

#endif
