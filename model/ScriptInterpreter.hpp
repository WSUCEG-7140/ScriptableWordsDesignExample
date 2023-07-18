#ifndef ScriptInterpreter_hpp
#define ScriptInterpreter_hpp

#include "Command.hpp"
#include "json.hpp"
#include <string>
using json = nlohmann::json;

namespace WSU {

namespace Model {

    /// @imp @ref R23_0
    /// @brief This class provides a mechanism to interpret a "script" that consists of one or more strings that describe modifications to be performed to the stored string.
    template <typename COMMAND_T> class ScriptInterpreter {
    public:
        typedef COMMAND_T command_t;
        typedef std::shared_ptr<command_t> command_p_t;
        typedef typename command_t::model_p_t model_p_t;

        /// @imp @ref R23_0
        /// @brief Parses and executes the scriptString as a JSON array containing JSON objects. Each top level object is a script language command with associated arguments.
        /// @param model_p : Pointer to stored string to be modified by the script
        /// @param scriptString : A string containing a valid JSON representation of a script
        /// @return 0 upon successful interpretation. -1 is returned to indicate error.
        static int32_t interpret(
            model_p_t model_p, const std::string& scriptString)
        {
            int32_t result { 0 };
            auto scriptJSON = json::parse(scriptString);
            for (auto statement : scriptJSON) {
                auto command = command_t::makeCommandWithName(
                    statement["command"], model_p, statement["args"]);
                if (nullptr != command) {
                    (*command)();
                } else {
                    result = -1;
                }
            }

            return result;
        }
    };

} // namespace Model
} // namespace WSU

#endif // ScriptInterpreter_hpp
