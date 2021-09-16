#ifndef DCR2CPN_UTILS_H_
#define DCR2CPN__UTILS_H_

#include <string>
#include <vector>
#include "DCR.hpp"

namespace DCR2CPN {
namespace Utils{

bool isSubOf2(const std::string& ParentNameInput, const std::string& EventNameInput, std::vector<Event> listEvent);

std::string removeNoneAlnum(const std::string& inp_string);

}
}

#endif