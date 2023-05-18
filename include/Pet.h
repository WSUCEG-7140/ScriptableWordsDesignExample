#ifndef Pet_H
#define Pet_H

#include <cstdint>

/// This class encapsulates information about pets
class Pet {
public:
    uint8_t m_age;
    const char* m_name;

    Pet()
        : m_age(0)
        , m_name("Anonymous")
    {
        // Intentionally empty
    }

    Pet(uint8_t age, const char* name)
        : m_age(age)
        , m_name(name)
    {
        // Intentionally empty
    }
};

#endif // Pet_H
