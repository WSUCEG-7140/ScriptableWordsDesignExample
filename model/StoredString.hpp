#ifndef WSUWord_hpp
#define WSUWord_hpp

#include <string>

/// This entire project is part of a demonstration for Wright State University (WSU) CS-7140 "Advanced Software Eng." Spring 2021.
namespace WSU {

/// Model Subsystem
///
/// This Module contains components that are part of the @ref Model within the overall @ref ModelViewPresenter Design.
namespace Model {

    /// @imp @ref R1_0 This class implements the core of the Model subsystem with methods to manipulate a stored string.
    class StoredString {
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
