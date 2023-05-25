#ifndef WSUWord_hpp
#define WSUWord_hpp

#include "Command.hpp"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

/// This entire project is part of a demonstration for Wright State University (WSU) CS-7140 "Advanced Software Eng." Spring 2021.
namespace WSU {

/// Model Subsystem
///
/// This Module contains components that are part of the @ref Model within the overall @ref ModelViewPresenter Design.
namespace Model {

    /// @imp @ref R1_0 This class implements the core of the Model subsystem with methods to manipulate a stored string.
    class StoredString {
    public:
        typedef std::shared_ptr<StoredString> p_t;

    private:
        /// @imp @ref R1_0 Storage for a string
        std::string m_string {};

        /// @imp @ref R4_0
        /// @return reference to the stored string
        std::string& _getString() { return m_string; }

        /// This is an abstract base class for Commands that operate upon Stored String instances.
        class Command : public WSU::Model::Command {
        private:
            StoredString::p_t m_storedString_p;

        public:
            typedef typename WSU::Model::Command::p_t p_t;

            Command(StoredString::p_t storedString_p);

            StoredString::p_t getStoredString() const;
        };

        typedef typename WSU::Model::Command::p_t command_p_t;

        /// Type for Factory Methods. Having a standard type simplifies use of [Factory Methods](https://en.wikipedia.org/wiki/Factory_method_pattern) because the caller need not know any details (like special arguments) about the object(s) created by the Factory Method.
        typedef std::function<command_p_t(p_t storedString_p, std::string args)>
            commandFactory_t;

        typedef std::unordered_map<std::string, StoredString::commandFactory_t>
            factoryMap_t;

        /// \imp \ref R3_1 In order to recognize commands by their names in a script, it is necessary to be able to lookup commands by name. This function returns a map from name to a Factory that creates instances of the command with that name. See [Factory Design Pattern](https://www.oodesign.com/factory-pattern.html)
        static factoryMap_t& getNameToFactoryMap();

    public:
        /// \imp \ref R3_1 In order to recognize commands by their names in a script, it is necessary to be able to lookup commands by name. This method provides a mechanism to associate a command Factory with the name of the command. A command Factory Method is an implantation of the [Factory Method Design Pattern](https://en.wikipedia.org/wiki/Factory_method_pattern).
        static void registerCommandFactoryWithName(
            commandFactory_t, std::string name);

        /// \imp \ref R3_1 Create a Command instance using the named Factory, stored string, and arguments. The name is a human readable identifier that may be used in scripts. The arguments are [JSON](https://www.json.org/json-en.html) formatted key/value pairs where each key is a string argument name and each value is a JSON value type.
        /// \ref R3_1_1 As an implementation detail, JSON is chosen as a human readable format .
        static command_p_t makeCommandWithName(
            std::string name, p_t storedString_p, std::string args);

        /// Default Constructor: @imp @ref R1_0 Initially store zero characters
        StoredString()
        {
            // Intentionally empty
        }

        /// @imp @ref R1_0 Initially store zero or more characters
        StoredString(const std::string& contents)
            : m_string(contents)
        {
            // Intentionally empty
        }

        /// @imp @ref R1_0
        /// @return const refrence to teh stored string
        const std::string& getString() const { return m_string; }

        /// @imp @ref R4_0
        /// @param c
        /// @param index
        void insertCharacterAtIndex(char c, uint32_t index)
        {
            _getString().insert(index, 1, c);
        }
    };

} // namespace Model
} // namespace WSU

#endif /* WSUWord_hpp */
