#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
    Object::Object() : m_IsPendingDestroyed{false} {}

    void Object::Destroy()
    {
        m_IsPendingDestroyed = true;
        LOG("Object marked for destruction");
    }

    bool Object::IsPendingDestroyed() const
    {
        return m_IsPendingDestroyed;
    }

    Object::~Object()
    {
        LOG("Object Destroyed");
    }
}
