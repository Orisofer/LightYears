#pragma once

#include <memory>

#include "framework/Core.h"
#include "framework/Delegate.h"

namespace ly
{
    class Object : public std::enable_shared_from_this<Object>
    {
    public:
        Object();
        virtual void Destroy();
        bool IsPendingDestroyed() const;
        weak<Object> GetWeakRef();
        weak<const Object> GetWeakRef() const;
        virtual ~Object();
        unsigned int GetUniqueID() const;
        Delegate<Object*> onDestroy;

    private:
        static unsigned int s_UniqueIdCounter;
        static unsigned int GetNextAvailableID();

        unsigned int m_UniqueId;
        bool m_IsPendingDestroyed;
    };
}
