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

    AppendCharacterCommand::base_t::command_p_t AppendCharacterCommand::run()
    {
        auto result = getReciprocalCommand();
        getStoredString()->insertCharacterAtIndex(
            getArgs()["char"].get<std::string>()[0],
            getStoredString()->getString().size());
        return result;
    }

    AppendCharacterCommand::base_t::command_p_t
    AppendCharacterCommand::getReciprocalCommand()
    {
        auto args = json {};

        // This is called before append, so the last valid index after
        // append will the the current size() instead of size() - 1.
        args["at"] = getStoredString()->getString().size();

        auto reciprocalCommand_p = base_t::makeCommandWithName(
            "removeCharacterAt", getStoredString(), args);
        return reciprocalCommand_p;
    }

} // namespace Model
} // namespace WSU
