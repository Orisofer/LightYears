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
        Delegate<Object*> onDestroy;
        virtual ~Object();
    private:
        bool m_IsPendingDestroyed;
    };
}
