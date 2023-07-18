#ifndef WSUWord_hpp
#define WSUWord_hpp

#include <memory>
#include <string>

/// This entire project is part of a demonstration for Wright State University (WSU) CS-7140 "Advanced Software Eng." Summer 2023.
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

    private:
        /// @imp @ref R1_0 Storage for a string
        std::string m_string {};

        /// @imp @ref R1_0
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
        /// @return const reference to the stored string
        const std::string& getString() { return _getString(); }

        /// @imp @ref R4_0
        /// @param c
        /// @param index
        void insertCharacterAtIndex(char c, uint32_t index)
        {
            _getString().insert(index, 1, c);
        }

        /// @imp @ref R7_0
        /// @param index
        void removeCharacterAtIndex(uint32_t index)
        {
            _getString().erase(index, 1);
        }
    };

} // namespace Model
} // namespace WSU

#endif /* WSUWord_hpp */
