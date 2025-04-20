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

    weak<Object> Object::GetWeakRef()
    {
        return weak_from_this();
    }

    weak<const Object> Object::GetWeakRef() const
    {
        return weak_from_this();
    }

    Object::~Object()
    {
        LOG("Object Destroyed");
    }
}
