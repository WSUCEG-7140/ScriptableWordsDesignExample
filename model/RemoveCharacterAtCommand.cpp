#include "RemoveCharacterAtCommand.hpp"

namespace WSU {
namespace Model {

    /// \imp \ref R21_0 The script command can be looked up by a name that may occur in a script.
    RemoveCharacterAtCommand::base_t::FactoryInstaller
        RemoveCharacterAtCommand::s_removeCharacterAtFactory {
            "removeCharacterAt",
            [](StoredString::p_t storedString_p, json args) {
                return RemoveCharacterAtCommand::base_t::command_p_t(
                    new RemoveCharacterAtCommand { storedString_p, args });
            }
        };

    /// \imp \ref R6_0 The script command can be run.
    void RemoveCharacterAtCommand::run()
    {
        getStoredString()->removeCharacterAtIndex(
            getArgs()["at"].get<uint32_t>());
    }

} // namespace Model
} // namespace WSU
