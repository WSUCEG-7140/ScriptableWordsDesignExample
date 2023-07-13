#ifndef ScriptInterpreter_hpp
#define ScriptInterpreter_hpp

#include "json.hpp"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
using json = nlohmann::json;

namespace WSU {

namespace Model {

    /// @imp @ref R23_0
    /// @brief This class provides a mechanism to interpret a "script" that consists of one or more strings that describe modifications to be performed to the stored string.
    class ScriptInterpreter {
    public:
        /// @imp @ref R23_0
        /// @brief Parses and executes the scriptString as a JSON array containing JSON objects. Each top level object is a script language command with associated arguments.
        /// @param ss_p : Pointer to stored string to be modified by the script
        /// @param scriptString : A string containing a valid JSON representation of a script
        /// @return 0 upon successful interpretation. -1 is returned to indicate error.
        static int32_t interpret(
            std::shared_ptr<StoredString> ss_p, const std::string& scriptString)
        {
            int32_t result { 0 };
            auto scriptJSON = json::parse(scriptString);
            for (auto statement : scriptJSON) {
                auto command = WSU::Model::StoredString::makeCommandWithName(
                    statement["command"], ss_p, statement["args"]);
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
