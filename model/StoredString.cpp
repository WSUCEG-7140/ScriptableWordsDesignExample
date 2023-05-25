#include "StoredString.hpp"

/// \imp \ref R3_0 This is a Factory Method that must be overridden in subclasses
WSU::Model::StoredString::command_p_t
WSU::Model::StoredString::makeCommandWithName(
    std::string name, p_t storedString_p, std::string args)
{
    StoredString::command_p_t result { nullptr };
    auto factoryIt = getNameToFactoryMap().find(name);
    if (getNameToFactoryMap().end() != factoryIt) {
        auto factory = factoryIt->second;
        if (nullptr != factory) {
            result = factory(storedString_p, args);
        }
    }
    return result;
}
