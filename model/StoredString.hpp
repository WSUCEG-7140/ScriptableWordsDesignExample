#ifndef WSUWord_hpp
#define WSUWord_hpp

//#include "Command.hpp"
#include "json.hpp"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
using json = nlohmann::json;

/// This entire project is part of a demonstration for Wright State University (WSU) CS-7140 "Advanced Software Eng." Spring 2021.
namespace WSU {

/// Model Subsystem
///
/// This Module contains components that are part of the @ref Model within the overall @ref ModelViewPresenter Design.
namespace Model {

    /// @imp @ref R1_0 This class implements the core of the Model subsystem with methods to manipulate a stored string.
    class StoredString {
    public:
        /// @brief Type used for pointers to StoredString instances
        typedef std::shared_ptr<StoredString> p_t;

        /// This is an abstract base class for Commands that operate upon Stored String instances.
        class Command {
        public:
            /// @brief Type used for pointers to Command instances
            typedef std::shared_ptr<Command> command_p_t;

            /// Type for Factory Methods. Having a standard type simplifies use of [Factory Methods](https://en.wikipedia.org/wiki/Factory_method_pattern) because the caller need not know any details (like special arguments) about the object(s) created by the Factory Method.
            typedef std::function<Command::command_p_t(
                p_t storedString_p, json args)>
                factory_t;

            /// @brief This is the type used to store name to Factory associations
            typedef std::unordered_map<std::string, factory_t> factoryMap_t;

        private:
            /// @brief Pointer to string ti be modified by command
            StoredString::p_t m_storedString_p;

            /// @brief JSON encode arguments to teh command
            json m_args;

        protected:
            ///\anchor DR3_2 \dreq DR3_2 In C++, all classes that have one or more virtual method are required to have a virtual destructor.
            virtual ~Command()
            { /* Intentionally Empty */
            }

            /// \imp \ref R3_1 In order to recognize commands by their names in a script, it is necessary to be able to lookup commands by name. This function returns a map from name to a Factory that creates instances of the command with that name. See [Factory Design Pattern](https://www.oodesign.com/factory-pattern.html)
            static factoryMap_t& _getNameToFactoryMap();

        public:
            Command(StoredString::p_t storedString_p, const json& args)
                : m_storedString_p(storedString_p)
                , m_args(args)
            {
                // Intentionally empty
            }

            StoredString::p_t getStoredString() const
            {
                return m_storedString_p;
            }

            const json& getArgs() const { return m_args; }

            /// \imp \ref R3_0 \anchor DR3_5 \dreq DR3_5 Use to execute commands via a script, undo, or redo an operation, it is necessary to "run" the operation.
            virtual void run() = 0;

            /// \imp \ref Rx_0 In order to be able to undo a command, the reciprocal of the command is needed. \imp \ref Rx_2 In order to redo an undo command, the reciprocal of the command executed as part of undo is needed.
            virtual command_p_t makeReciprocalCommand() = 0;

            /// \imp \ref R3_0 In order to create a script of commands, it is necessary to have string representations of the commands
            /// \anchor DR3_6 \dreq DR3_6 A script will consist of a sequence of commands identified by their string representations
            /// anchor DR3_7  \dreq DR3_7 String representations are human readable
            virtual std::string getStringRepresentation() = 0;

            /// C++ has a well established idiom know as [Functors](https://www.geeksforgeeks.org/functors-in-cpp). Functors are a C++ language level implementation of the Command Design Pattern particularly when combined with C++11 std::bind and std::function. Providing this operator makes it seamless to use this class as a Functor along with std::bind and std::function.
            /// \anchor DR_1_0 \dreq DR_1_0: Any implementation of a Design Pattern should incorporate related language idioms as a matter of courtesy for other practitioners of the language.
            void operator()() { run(); }

            /// \imp \ref R3_1 In order to recognize commands by their names in a script, it is necessary to be able to lookup commands by name. This function returns a map from name to a Factory that creates instances of the command with that name. See [Factory Design Pattern](https://www.oodesign.com/factory-pattern.html)
            static const factoryMap_t& getNameToFactoryMap();

            /// \imp \ref R3_1 In order to recognize commands by their names in a script, it is necessary to be able to lookup commands by name. This method provides a mechanism to associate a command Factory with the name of the command. A command Factory Method is an implantation of the [Factory Method Design Pattern](https://en.wikipedia.org/wiki/Factory_method_pattern).
            ///
            ///\args factory : The Factory to be associated with the name, name.
            ///\args name : The name of a Command Factory
            static void registerFactoryWithName(
                factory_t factory, std::string name);
        };

    private:
        /// @imp @ref R1_0 Storage for a string
        std::string m_string {};

        /// @imp @ref R4_0
        /// @return reference to the stored string
        std::string& _getString() { return m_string; }

    public:
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
        const std::string& getString() { return _getString(); }

        /// @imp @ref R4_0
        /// @param c
        /// @param index
        void insertCharacterAtIndex(char c, uint32_t index)
        {
            _getString().insert(index, 1, c);
        }

        /// \imp \ref R3_1 Create a Command instance using the named Factory, stored string, and arguments. The name is a human readable identifier that may be used in scripts. The arguments are [JSON](https://www.json.org/json-en.html) formatted key/value pairs where each key is a string argument name and each value is a JSON value type.
        /// \ref R3_1_1 As an implementation detail, JSON is chosen as a human readable format.
        ///
        ///\arg name : The name of a Command
        static Command::command_p_t makeCommandWithName(
            std::string name, p_t storedString_p, const json& args);

        class FactoryInstaller {
        public:
            FactoryInstaller(
                const std::string& name, Command::factory_t factory)
            {
                Command::registerFactoryWithName(factory, name);
            }
        };
    };

    /// \imp \ref R3_0 This class provides a concrete implementation of the Command design patter in order to insert a character at an index ina string.
    class InsertCharacterAtCommand : public StoredString::Command {
    public:
        InsertCharacterAtCommand(StoredString::p_t storedString_p, json args)
            : StoredString::Command(storedString_p, args)
        {
            // Intentionally empty
        }

        /// \imp \ref R3_0 \anchor DR3_5 \dreq DR3_5 Use to execute commands via
        /// a script, undo, or redo an operation, it is necessary to "run" the
        /// operation.
        virtual void run()
        {
            getStoredString()->insertCharacterAtIndex(
                getArgs()["char"].get<std::string>()[0],
                getArgs()["at"].get<uint32_t>());
        }

        /// \imp \ref Rx_0 In order to be able to undo a command, the reciprocal of the command is needed.
        /// \imp \ref Rx_2 In order to redo an undo command, the reciprocal of the command executed as part of undo is needed.
        virtual command_p_t makeReciprocalCommand() { return nullptr; }

        /// \imp \ref R3_0 In order to create a script of commands, it is necessary to have string representations of the commands
        /// \anchor DR3_6 \dreq DR3_6 A script will consist of a sequence of commands identified by their string representations
        /// anchor DR3_7  \dreq DR3_7 String representations are human readable
        virtual std::string getStringRepresentation()
        {
            return "Insert Character At";
        }
    };

    class FactoryInstaller {
    public:
        FactoryInstaller(
            const std::string& name, StoredString::Command::factory_t factory)
        {
            StoredString::Command::registerFactoryWithName(factory, name);
        }
    };

    static FactoryInstaller s_insertCharacterAt { "insertCharacterAt",
        [](StoredString::p_t storedString_p, json args) {
            return StoredString::Command::command_p_t(
                new InsertCharacterAtCommand { storedString_p, args });
        } };

} // namespace Model
} // namespace WSU

#endif /* WSUWord_hpp */
