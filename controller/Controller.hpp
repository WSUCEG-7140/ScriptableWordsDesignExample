//
//  Controller.hpp

#ifndef Controller_hpp
#define Controller_hpp

#include "ScriptInterpreter.hpp"
#include "StoredString.hpp"
#include "UndoRedoManager.hpp"

namespace WSU {

/// Controller Subsystem
///
/// This Module contains components that are part of the "Supervising Controller" within an overall @designpattern \ref ModelViewPresenter Design Pattern.
namespace Controller {

    typedef WSU::Model::StoredString model_t;
    typedef WSU::Model::ModelCommand<model_t> command_t;
    typedef typename command_t::model_p_t model_p_t;
    typedef WSU::Model::ScriptInterpreter<command_t> interpreter_t;

    /// This class is part of the "Supervising Controller" within an overall \ref ModelViewPresenter Design Pattern.
    /// This class creates an instance of the Model and serves as a clearing house for operations upon the Model. For example, use runCommandWithUndoRedoSupport() to run commands that mutate the Model in such a way that those mutations may be undone or redone at a later time. Similarly, use runScript() to run an entire script of commands that mutate the Model.
    class Controller {
    public:
        typedef typename command_t::command_p_t command_p_t;

    private:
        /// An instance of the Model
        model_p_t m_storedString_p { new WSU::Model::StoredString { "" } };

        UndoRedoManager m_undoRedoManager {};

    public:
        model_p_t getCurrentStoredString_p() { return m_storedString_p; }

        /// \imp \ref R12_0
        /// This functions runs the command at the top of the Undo stack. The commands in the Undo stack are reciprocals of commands previously executed. As a result, running a command from the Undo stack effectively undoes a command that was previously run.
        void undo() { m_undoRedoManager.undo(); }

        /// \imp \ref R14_0
        /// This function redoes a most recently run command that has been undone.
        void redo() { m_undoRedoManager.redo(); }

        /// \imp \ref R12_0
        /// This functions runs the specified command in such a way that the reciprocal of the specified command is placed on an Undo stack.
        void runCommandWithUndo(command_p_t command_p)
        {
            m_undoRedoManager.runCommandWithUndo(command_p);
        }
    };

} // namespace Controller
} // namespace WSU

#endif /* CommandController_hpp */