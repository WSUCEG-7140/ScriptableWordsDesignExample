#include "RemoveCharacterAtCommand.hpp"

namespace WSU {
namespace Model {

    /// \imp \ref R7_0
    StoredString::Command::FactoryInstaller
        RemoveCharacterAtCommand::s_removeCharacterAtFactory {
            "removeCharacterAt",
            [](StoredString::p_t storedString_p, json args) {
                return StoredString::Command::command_p_t(
                    new RemoveCharacterAtCommand { storedString_p, args });
            }
        };

    /// \imp \ref R7_0
    void RemoveCharacterAtCommand::run()
    {
        getStoredString()->removeCharacterAtIndex(
            getArgs()["at"].get<uint32_t>());
    }

} // namespace Model
} // namespace WSU
