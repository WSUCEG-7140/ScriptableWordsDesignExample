#include "StoredString.hpp"

WSU::Model::StoredString::Command::factoryMap_t&
WSU::Model::StoredString::Command::_getNameToFactoryMap()
{
    static WSU::Model::StoredString::Command::factoryMap_t map {};

    return map;
}

const WSU::Model::StoredString::Command::factoryMap_t&
WSU::Model::StoredString::Command::getNameToFactoryMap()
{
    return WSU::Model::StoredString::Command::_getNameToFactoryMap();
}

void WSU::Model::StoredString::Command::registerFactoryWithName(
    WSU::Model::StoredString::Command::factory_t factory, std::string name)
{
    WSU::Model::StoredString::Command::_getNameToFactoryMap()[name] = factory;
}

/// \imp \ref R3_0 This is a Factory Method that must be overridden in subclasses
WSU::Model::StoredString::Command::command_p_t
WSU::Model::StoredString::makeCommandWithName(std::string name,
    WSU::Model::StoredString::p_t storedString_p, const json& args)
{
    StoredString::Command::command_p_t result { nullptr };
    auto factoryIt = StoredString::Command::getNameToFactoryMap().find(name);
    if (StoredString::Command::getNameToFactoryMap().end() != factoryIt) {
        auto factory = factoryIt->second;
        if (nullptr != factory) {
            result = factory(storedString_p, args);
        }
    }
    return result;
}
