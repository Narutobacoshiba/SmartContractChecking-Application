#include "../include/Translator.hpp"
#include "../include/Utils.hpp"
#include "../include/ASTNodes.hpp"

namespace SOL2CPN {

NetNodePtr Translator::translate() {
    net = std::make_shared<NetNode>();
    for (int i = 0; i < rootNode->num_fields(); i++)
            if (rootNode->get_field(i)->get_node_type() == NodeTypeContractDefinition) {
                //create the net
                auto contractNode = std::static_pointer_cast<ContractDefinitionNode>(rootNode->get_field(i));
                net->set_name(contractNode->get_name());
                generatePredefinedColors();

                for (int i = 0; i < contractNode->num_members(); i++){
                    auto member = contractNode->get_member(i);
                    if (member->get_node_type() == NodeTypeStructDefinition) {
                        auto structNode = std::static_pointer_cast<StructDefinitionNode>(contractNode->get_member(i));
                        
                        net->add_color(translateStruct(structNode));
                    }
                    else if (member->get_node_type() == NodeTypeVariableDeclaration) {
                        auto varNode = std::static_pointer_cast<VariableDeclarationNode>(member);
                        std::cout<<varNode->get_variable_name()<<" "<<varNode->get_type()->get_node_type()<<"\n";
                        if (varNode->get_type()->get_node_type() == NodeTypeMapping) {
                            net->add_color(translateMapping(member));
                        }
                    }
                    else if (member->get_node_type() == NodeTypeFunctionDefinition) {
                        auto func = std::static_pointer_cast<FunctionDefinitionNode>(member);
                        //parameters are handled as variable declarations..
                        
                    }
                }
            }
    return net;
}

void Translator::generatePredefinedColors() {
    ColorNodePtr address (new ColorNode());
    address->set_name("ADDRESS");
    address->set_typeDef("range 0 .. 100");
    net->add_color(address);
    
    ColorNodePtr eth (new ColorNode());
    eth->set_name("ETH");
    eth->set_typeDef("range 0 .. 1000");
    net->add_color(eth);

    ColorNodePtr user (new ColorNode());
    user->set_name("USER");
    user->set_typeDef("struct { ADDRESS adr;ETH balance;}");
    net->add_color(user);
}

StructColorNodePtr Translator::translateStruct(StructDefinitionNodePtr struct_node) {
    StructColorNodePtr struct_color = std::make_shared<StructColorNode>();
    struct_color->set_name(struct_node->get_name());
            
    for (int i = 0; i < struct_node->num_fields(); i++) {
        VariableDeclarationNodePtr variable = std::static_pointer_cast<VariableDeclarationNode>(struct_node->get_field(i));
        ComponentNodePtr component = std::make_shared<ComponentNode>();
        component->set_name(variable->get_variable_name());
        component->set_type(std::static_pointer_cast<ElementaryTypeNameNode>(variable->get_type())->get_type_name());
        struct_color->add_component(component);
    }
    return struct_color;
}

ListColorNodePtr Translator::translateMapping(ASTNodePtr _node) {
    ListColorNodePtr list_color = std::make_shared<ListColorNode>();
    StructColorNodePtr struct_color = std::make_shared<StructColorNode>();
    auto var_node = std::static_pointer_cast<VariableDeclarationNode>(_node);
    auto mapNode = std::static_pointer_cast<MappingNode>(var_node->get_type());
    struct_color->set_name("struct_" + var_node->get_variable_name());
    ComponentNodePtr key = std::make_shared<ComponentNode>();
    key->set_name("key");
    if (mapNode->get_key_type()->get_node_type() == NodeTypeElementaryTypeName) {
        auto key_type = std::static_pointer_cast<ElementaryTypeNameNode>(mapNode->get_key_type());
        key->set_type(key_type->get_type_name());
    }
    else {
        auto key_type = std::static_pointer_cast<UserDefinedTypeNameNode>(mapNode->get_key_type());
        key->set_type(key_type->get_type_name());
    }
    ComponentNodePtr value = std::make_shared<ComponentNode>();



    value->set_name("value");
    if (mapNode->get_value_type()->get_node_type() == NodeTypeElementaryTypeName) {
        auto value_type = std::static_pointer_cast<ElementaryTypeNameNode>(mapNode->get_value_type());
        value->set_type(value_type->get_type_name());
    }
    else if (mapNode->get_value_type()->get_node_type() == NodeTypeArrayTypeName) {
        auto value_type = std::static_pointer_cast<ArrayTypeNameNode>(mapNode->get_value_type());
        auto base_type = std::static_pointer_cast<UserDefinedTypeNameNode>(value_type->get_base_type());
        value->set_type(base_type->get_type_name()+"[]");
    }
    struct_color->add_component(key);
    struct_color->add_component(value);
    net->add_color(struct_color);
    list_color->set_name("list_"+ var_node->get_variable_name());
    list_color->set_index_type("nat");
    list_color->set_element_type(struct_color->get_name());
    list_color->set_capacity("100");

    return list_color;
}

}
