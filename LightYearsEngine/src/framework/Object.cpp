#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
    unsigned int Object::s_UniqueIdCounter = 0;

    Object::Object() :
    m_IsPendingDestroyed{false},
    m_UniqueId(GetNextAvailableID())
    {
    }

    void Object::Destroy()
    {
        onDestroy.Broadcast(this);
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

    unsigned int Object::GetUniqueID() const
    {
        return m_UniqueId;
    }

    unsigned int Object::GetNextAvailableID()
    {
        return s_UniqueIdCounter++;
    }
}
