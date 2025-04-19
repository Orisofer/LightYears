#pragma once

namespace ly
{
    class Object
    {
    public:
        Object();
        virtual void Destroy();
        bool IsPendingDestroyed() const;
        virtual ~Object();
    private:
        bool m_IsPendingDestroyed;
    };
}
