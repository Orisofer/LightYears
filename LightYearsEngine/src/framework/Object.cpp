#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
    Object::Object() : m_IsPendingDestroyed{false} {}

    void Object::Destroy()
    {
        m_IsPendingDestroyed = true;
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
