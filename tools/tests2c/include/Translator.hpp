#ifndef SOL2CPN_TRANSLATOR_H_
#define SOL2CPN_TRANSLATOR_H_

#include "Helena.hpp"
#include "nlohmann/json.hpp"
#include "ASTNodes.hpp"

namespace SOL2CPN {

class Translator {
public:
    Translator(RootNodePtr _rootNode) : rootNode(_rootNode) {}
    NetNodePtr translate();

private:
RootNodePtr rootNode;
NetNodePtr net;

void generatePredefinedColors();
StructColorNodePtr translateStruct(StructDefinitionNodePtr struct_node);
ListColorNodePtr translateMapping(ASTNodePtr _node);

};

}

#endif //SOL2CPN_TRANSLATOR_H_