#include "../include/Utils.hpp"

namespace DCR2CPN {
namespace Utils {

bool isSubOf2(const std::string& ParentNameInput, const std::string& EventNameInput, std::vector<DCR2CPN::Event> listEvent){
    std::string ParentName = ParentNameInput;
    std::string EventName = EventNameInput;
    if(ParentNameInput=="") return false;
    else{
    for(auto itrEvent = listEvent.begin() ; itrEvent != listEvent.end(); itrEvent++){
                    DCR2CPN::Event e = *itrEvent;
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
}

std::string removeNoneAlnum(const std::string& inp_string)
{
    std::string s = inp_string;
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

}
}