#include "StoredString.hpp"
#include <iostream>

namespace WSU {
namespace Model {

    StoredString::Command::factoryMap_t&
    StoredString::Command::_getNameToFactoryMap()
    {
        static StoredString::Command::factoryMap_t map {};

        return map;
    }

    const StoredString::Command::factoryMap_t&
    StoredString::Command::getNameToFactoryMap()
    {
        return StoredString::Command::_getNameToFactoryMap();
    }

    void StoredString::Command::registerFactoryWithName(
        StoredString::Command::factory_t factory, std::string name)
    {
        StoredString::Command::_getNameToFactoryMap()[name] = factory;
    }

    /// \imp \ref R23_0 This is a Factory Method that must be overridden in subclasses. The factory method enables scripts that identify commands by human readable string name to lookup and create instances of the named commands.
    StoredString::Command::command_p_t StoredString::makeCommandWithName(
        std::string name, StoredString::p_t storedString_p, const json& args)
    {
        StoredString::Command::command_p_t result { nullptr };
        auto factoryIt
            = StoredString::Command::getNameToFactoryMap().find(name);
        if (StoredString::Command::getNameToFactoryMap().end() != factoryIt) {
            auto factory = factoryIt->second;
            if (nullptr != factory) {
                result = factory(storedString_p, args);
            }
        }
        return result;
    }

    StoredString::Command::FactoryInstaller::FactoryInstaller(
        const std::string& name, StoredString::Command::factory_t factory)
    {
        StoredString::Command::registerFactoryWithName(factory, name);
    }

} // namespace Model
} // namespace WSU
