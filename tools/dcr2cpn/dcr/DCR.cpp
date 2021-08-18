#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace DCR{
    enum EnumRelations{
    condition,
    response,
    include,
    exclude,
    milestone
};

class Event{
    public:
        Event(){};
        Event(string ID,string Label, string Roles, string Datatype, string Parent ,string Type){
            id = ID;
            label = Label;
            roles = Roles;
            dataType = Datatype;
            parent = Parent;
            type = Type;
             
        };
        string getID(){
            return id;
        };
        string getRoles(){
            return roles;
        };
        string getDataType(){
            return dataType;
        };
        string getParent(){
            return parent;
        };
        string getLabel(){
            return label;
        };
        string getType(){
            return type;
        }
        
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
    Relation(string Type,string Source, string Target, string Guard, string DurationExpression){
        type=Type;
        source = Source;
        target = Target;
        guard = Guard;
        durationExpression = DurationExpression;
    }
    string getType(){
        return type;
    }
    string getSource(){
        return source;
    }
    string getTarget(){
        return target;
    }
    string getGuard(){
        return guard;
    }
    string getDE(){
        return durationExpression;
    }
    
};


class ERE{
    public:
        ERE(){};
        ERE(Event Source, Event Target, vector<string> Relation){
            source = Source;
            target = Target;
            listRelation = Relation;
        }
        Event  getSource(){
            return source;
        }
        Event getTarget(){
            return target;
        }
        vector<string> getLisRelation(){
            return listRelation;
        }
        void addRelation(string i){
             listRelation.push_back(i);   
        };
        void addToTest(int i ){
            test = test + to_string(i);
        }
        string getTest(){
            return test;
        }
        void setText(string t){
            test = t;
        }
        void setListRelation(vector<string> ListRelation){
            listRelation = ListRelation;
        }
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
    Marking(vector<Event> exclude, vector<Event> include, vector<Event> reponse){
        Exclude = exclude;
        Include = include;
        Reponse = reponse;
    }
    vector<Event> getExclude(){
        return Exclude;
    }
    vector<Event> getInclude(){
        return Include;
    }
    vector<Event> getReponse(){
        return Reponse;
    }
    void setExclude(vector<Event> exclude){
        Exclude = exclude;
    }
    void setInclude(vector<Event> include){
        Include = include;
    }
    void setReponse(vector<Event> reponse){
        Reponse = reponse;
    }
};
class DCRClass{
    public:
        DCRClass();
        DCRClass(vector<Event> ListEvent, Marking InitMarking, vector<ERE> ListERE){
               listERE = ListERE;
               listEvent = ListEvent;
               initMarking = InitMarking; 
        }
        void setEvent(vector<Event> ListEvent){
            listEvent = ListEvent;
        }
        void setMarking(Marking InitMarking){
            initMarking = InitMarking;
        }
        void setERE(vector<ERE> ListERE){
            listERE = ListERE;
        }
        vector<Event> getListEvent(){
            return listEvent;
        }
        Marking getMarking(){
            return initMarking;
        }
        vector<ERE> getERE(){
            return listERE;
        }
        string description(){
            return  "";
        }
    private:
        vector<Event> listEvent;
        Marking initMarking;
        vector<ERE> listERE;
        
};
}