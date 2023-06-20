#ifndef Command_hpp
#define Command_hpp

#include "json.hpp"
#include <functional>
#include <memory>
using json = nlohmann::json;

namespace WSU {
namespace Model {

    /// This class is an "interface" for Commands within the [Command Design Pattern](https://en.wikipedia.org/wiki/Command_pattern) "In object-oriented programming, the command pattern is a behavioral design pattern in which an object is used to encapsulate all information needed to perform an action or trigger an event at a later time. This information includes the method name, the object that owns the method and values for the method parameters." -wikipedia
    /// \imp \ref DR3_1 In order to script an operation (a.k.a. action), it is necessary to execute the reciprocal of the un-doable operation at a later time when the user chooses to undo.
    // \anchor DR3_1 \dreq DR3_1 Implement Command Design Pattern
    class Command {
    public:
        /// Reference to stored string to modify
        typedef std::shared_ptr<Command> p_t;

    protected:
        ///\anchor DR3_2 \dreq DR3_2 In C++, all classes that have one or more virtual method are required to have a virtual destructor.
        virtual ~Command()
        { /* Intentionally Empty */
        }

    public:
        /// This class exists to install a Command factories associated with names so that Command instances may be created by looking up named factories and using the factories to create the Command instances. See [Factory Design Pattern](https://www.oodesign.com/factory-pattern.html).
        /// \ref R3_0 \anchor DR3_4 \dreq DR3_4 Scripts contain human readable command names. The names may be used to lookup installed factories, and then the factories may be used to create instances of the named Commands.
        /// \anchor DR3_3 \dreq DR3_3 The Factory Design Pattern provides a mechanism to create instances of various concrete Command subclasses without the users of the [Factory](https://en.wikipedia.org/wiki/Factory_method_pattern) needing to know about the specific concrete classes i.e. decouple instance creation from specific classes.
        class FactoryInstaller {
        protected:
            typedef json arguments_t;

            /// Commands encapsulate the information needed to run the command
            /// at a later time. This method  must be implemented in all
            /// subclasses of those class to encapsulate (that is store) needed
            /// information.
            /// \param args \imp \ref R3_0 A script needs to be human readable.
            /// That implies the arguments to a command are human readable too.
            /// The args parameter is intended to contain a human readable
            /// string of command arguments such as the argument that may be
            /// present in a script. \dreq DR3_8 Scripts need to be human
            /// readable. JSON is used to encode args because JSON is human
            /// readable, standardized, and well known.
            /// \return true iff args are successful parsed and encapsulated. Return false otherwise.
            static arguments_t parse(const std::string& args);
        };

        /// \imp \ref R3_0 \anchor DR3_5 \dreq DR3_5 Use to execute commands via
        /// a script, undo, or redo an operation, it is necessary to "run" the
        /// operation.
        virtual void run() = 0;

        /// C++ has a well established idiom know as [Functors](https://www.geeksforgeeks.org/functors-in-cpp). Functors are a C++ language level implementation of the Command Design Pattern particularly when combined with C++11 std::bind and std::function. Providing this operator makes it seamless to use this class as a Functor along with std::bind and std::function.
        /// \anchor DR_1_0 \dreq DR_1_0: Any implementation of a Design Pattern should incorporate related language idioms as a matter of courtesy for other practitioners of the language.
        void operator()() { run(); }

        /// \imp \ref Rx_0 In order to be able to undo a command, the reciprocal of the command is needed.
        /// \imp \ref Rx_2 In order to redo an undo command, the reciprocal of the command executed as part of undo is needed.
        virtual p_t makeReciprocalCommand() = 0;

        /// \imp \ref R3_0 In order to create a script of commands, it is necessary to have string representations of the commands
        /// \anchor DR3_6 \dreq DR3_6 A script will consist of a sequence of commands identified by their string representations
        /// anchor DR3_7  \dreq DR3_7 String representations are human readable
        virtual std::string getStringRepresentation() = 0;
    };

} // namespace Model
} // namespace WSU

#endif /* Command_hpp */
