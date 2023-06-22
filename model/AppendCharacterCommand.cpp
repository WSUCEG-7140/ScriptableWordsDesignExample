#include "AppendCharacterCommand.hpp"

namespace WSU {
namespace Model {

    StoredString::Command::FactoryInstaller
        AppendCharacterCommand::s_appendCharacterFactory { "appendCharacter",
            [](StoredString::p_t storedString_p, json args) {
                return StoredString::Command::command_p_t(
                    new AppendCharacterCommand { storedString_p, args });
            } };

    void AppendCharacterCommand::run()
    {
        getStoredString()->insertCharacterAtIndex(
            getArgs()["char"].get<std::string>()[0],
            getStoredString()->getString().size());
    }

} // namespace Model
} // namespace WSU
