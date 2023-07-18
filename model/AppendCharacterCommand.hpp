
#ifndef AppendCharacter_hpp
#define AppendCharacter_hpp

#include "Command.hpp"
#include "StoredString.hpp"
using json = nlohmann::json;

namespace WSU {
namespace Model {

    /// \imp \ref R2_0 This class provides a concrete implementation of the Command design pattern in order to append a character to a string.
    class AppendCharacterCommand : public ModelCommand<StoredString> {
    public:
        typedef ModelCommand<StoredString> base_t;

        AppendCharacterCommand(
            base_t::model_p_t storedString_p, const json& args)
            : base_t(storedString_p, args)
        {
            // Intentionally empty
        }

        /// \imp \ref R2_0
        virtual void run();

        base_t::model_p_t getStoredString() { return getModel_p(); }

        /// @brief This function returns a command that performs the reciprocal operation of the Command instance. The reciprocal Command is a Command that undoes whatever this Command does.
        ///
        /// \imp \ref R12_0 reciprocal Commands are needed to implement Undo.
        /// @return The reciprocal Command
        virtual base_t::command_p_t getReciprocalCommand()
        {
            auto args = json {};

            // This is called before append, so the last valid index after
            // append will the the current size() instead of size() - 1.
            args["at"] = getStoredString()->getString().size();

            auto reciprocalCommand_p = base_t::makeCommandWithName(
                "removeCharacterAt", getStoredString(), args);
            return reciprocalCommand_p;
        }

        /// @brief As a side effect of creating this static instance, a FActory is registered to enable construction of Command instances based on the name of the Command.
        static base_t::FactoryInstaller s_appendCharacterFactory;
    };

} // namespace Model
} // namespace WSU

#endif /* AppendCharacter_hpp */
