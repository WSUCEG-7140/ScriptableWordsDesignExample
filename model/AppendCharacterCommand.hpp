
#ifndef AppendCharacter_hpp
#define AppendCharacter_hpp

#include "StoredString.hpp"
#include "json.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <string>
using json = nlohmann::json;

namespace WSU {
namespace Model {

    /// \imp \ref R2_0 This class provides a concrete implementation of the Command design pattern in order to append a character to a string.
    class AppendCharacterCommand : public StoredString::Command {
    public:
        AppendCharacterCommand(
            StoredString::p_t storedString_p, const json& args)
            : StoredString::Command(storedString_p, args)
        {
            // Intentionally empty
        }

        /// \imp \ref R2_0
        virtual void run();

        /// @brief This function returns a command that performs the reciprocal operation of teh Command instance. The reciprocal Command is a Command that undoes whatever this Command does.
        ///
        /// \imp \ref R12_0 reciprocal Commands are needed to implement Undo.
        /// @return The reciprocal Command
        virtual command_p_t getReciprocalCommand()
        {
            auto argsString { "{\"at\":"
                + std::to_string(getStoredString()->getString().size() - 1)
                + "}" };
            std::cerr << "<" << argsString << ">\n";
            auto args { json::parse(argsString) };
            std::cerr << "<" << args.dump() << ">\n";
            auto reciprocalCommand_p = StoredString::makeCommandWithName(
                "removeCharacterAt", getStoredString(), args);
            return reciprocalCommand_p;
        }

        /// @brief As a side effect of creating this static instance, a FActory is registered to enable construction of Command instances based on the name of the Command.
        static StoredString::Command::FactoryInstaller s_appendCharacterFactory;
    };

} // namespace Model
} // namespace WSU

#endif /* AppendCharacter_hpp */
