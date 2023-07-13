//
//  Controller.hpp

#ifndef Controller_hpp
#define Controller_hpp

#include "StoredString.hpp"
#include <string>

namespace WSU {
namespace Controller {

    /// This class is part of the "Supervising Controller" within an overall \ref ModelViewPresenter Design Pattern.
    /// This class creates an instance of the Model and serves as a clearing house for operations upon the Model. For example, use runCommandWithUndoRedoSupport() to run commands that mutate the Model in such a way that those mutations may be undone or redone at a later time. Similarly, use runScript() to run an entire script of commands that mutate the Model.
    class Controller {
    private:
        /// An instance of the Model
        Model::StoredString m_storedString {};

    public:
        const std::string& getCurrentStoredStringValue()
        {
            return m_storedString.getString();
        }
    };

} // namespace Controller
} // namespace WSU

#endif /* CommandController_hpp */