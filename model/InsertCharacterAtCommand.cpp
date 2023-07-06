#include "InsertCharacterAtCommand.hpp"

namespace WSU {
namespace Model {

    /// \imp \ref R3_0
    StoredString::Command::FactoryInstaller
        InsertCharacterAtCommand::s_insertCharacterAtFactory {
            "insertCharacterAt",
            [](StoredString::p_t storedString_p, json args) {
                return StoredString::Command::command_p_t(
                    new InsertCharacterAtCommand { storedString_p, args });
            }
        };

    /// \imp \ref R3_0
    void InsertCharacterAtCommand::run()
    {
        getStoredString()->insertCharacterAtIndex(
            getArgs()["char"].get<std::string>()[0],
            getArgs()["at"].get<uint32_t>());
    }

} // namespace Model
} // namespace WSU
