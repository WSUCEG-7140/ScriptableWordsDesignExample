//
//  Controller.hpp

#ifndef Controller_hpp
#define Controller_hpp

#include "ScriptInterpreter.hpp"
#include "StoredString.hpp"
#include "UndoRedoManager.hpp"
#include <string>

namespace WSU {
namespace Controller {

    /// This class is part of the "Supervising Controller" within an overall \ref ModelViewPresenter Design Pattern.
    /// This class creates an instance of the Model and serves as a clearing house for operations upon the Model. For example, use runCommandWithUndoRedoSupport() to run commands that mutate the Model in such a way that those mutations may be undone or redone at a later time. Similarly, use runScript() to run an entire script of commands that mutate the Model.
    class Controller {
    private:
        /// An instance of the Model
        WSU::Model::StoredString::p_t m_storedString_p {
            new WSU::Model::StoredString { "" }
        };

        UndoRedoManager m_undoRedoManager {};

    public:
        WSU::Model::StoredString::p_t getCurrentStoredString_p()
        {
            return m_storedString_p;
        }

        /// \imp \ref R12_0
        /// This functions runs the command at the top of the Undo stack. The commands in teh Undo stack are reciprocals of commands previously executed. As a result, running a command from teh Undo stack effectively undoes a command that was previously run.
        void undo() { m_undoRedoManager.undo(); }

        /// \imp \ref R14_0
        /// This function redoes a most recently run command that has been undone.
        void redo() { m_undoRedoManager.redo(); }

        /// \imp \ref R12_0
        /// This functions runs the specified command in such a way that the reciprocal of the specified command is placed on an Undo stack.
        void runCommandWithUndo(WSU::Model::StoredString::command_p_t command_p)
        {
            m_undoRedoManager.runCommandWithUndo(command_p);
        }
    };

} // namespace Controller
} // namespace WSU

#endif /* CommandController_hpp */