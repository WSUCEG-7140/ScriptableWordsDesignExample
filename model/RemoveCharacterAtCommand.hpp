
#ifndef RemoveCharacterAtCommand_hpp
#define RemoveCharacterAtCommand_hpp

#include "Command.hpp"
#include "StoredString.hpp"
using json = nlohmann::json;

namespace WSU {
namespace Model {

    /// \imp \ref R6_0 This class provides a concrete implementation of the [Command Design Pattern](https://en.wikipedia.org/wiki/Command_pattern) in order to remove a character at an index in a string.
    class RemoveCharacterAtCommand : public ModelCommand<StoredString> {
    public:
        typedef ModelCommand<StoredString> base_t;

        RemoveCharacterAtCommand(
            base_t::model_p_t storedString_p, const json& args)
            : base_t(storedString_p, args)
        {
            // Intentionally empty
        }

        /// \imp \ref R3_0 \anchor DR3_5 \dreq DR3_5 Use to execute commands via
        /// a script, undo, or redo an operation, it is necessary to "run" the
        /// operation.
        virtual void run();

        base_t::model_p_t getStoredString() { return getModel_p(); }

        /// @brief This function returns a command that performs the reciprocal operation of the Command instance. The reciprocal Command is a Command that undoes whatever this Command does.
        ///
        /// \imp \ref R12_0 reciprocal Commands are needed to implement Undo.
        /// @return The reciprocal Command
        virtual base_t::command_p_t getReciprocalCommand()
        {
            json args {};
            auto index = getArgs()["at"];
            args["char"]
                = std::string { getStoredString()->getString()[index] };
            args["at"] = index;

            auto reciprocalCommand_p = base_t::makeCommandWithName(
                "insertCharacterAt", getStoredString(), args);
            return reciprocalCommand_p;
        }

        /// @brief As a side effect of creating this static instance, a FActory is registered to enable construction of Command instances based on the name of the Command.
        static base_t::FactoryInstaller s_removeCharacterAtFactory;
    };

} // namespace Model
} // namespace WSU

#endif /* RemoveCharacterAtCommand_hpp */
