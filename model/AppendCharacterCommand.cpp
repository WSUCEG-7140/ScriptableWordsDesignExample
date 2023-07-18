#include "AppendCharacterCommand.hpp"

namespace WSU {
namespace Model {

    AppendCharacterCommand::base_t::FactoryInstaller
        AppendCharacterCommand::s_appendCharacterFactory { "appendCharacter",
            [](AppendCharacterCommand::base_t::model_p_t storedString_p,
                json args) {
                return Command::command_p_t(
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
