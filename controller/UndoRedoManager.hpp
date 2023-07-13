#ifndef UndoRedoManager_hpp
#define UndoRedoManager_hpp

#include "StoredString.hpp"
#include <string>

namespace WSU {
namespace Controller {

    /// \imp \ref R12_0
    /// This class encapsulates data structures and operations related to collections of Command instances that can be undone or redone.
    ///
    /// Undo and Redo operations are part of the Controller subsystem because, the Undo and redo data structures are not part if the Model. The data structures are not save with the Model. Undo and Redo can not be part of the Presenter subsystem because teh Presenter subsystem is not allowed to know about the Model, but Undo and Redo need to know about the Model.
    class UndoRedoManager {

    public:
        void undo() { }
    };

} // namespace Controller
} // namespace WSU

#endif /* UndoRedoManager_hpp */