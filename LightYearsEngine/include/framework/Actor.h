#pragma once

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
    class World;

    class Actor : public Object
    {
    public:
        Actor(World* owningWorld);
        virtual ~Actor();
        void BeginPlayInternal();
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
    private:
        World* m_OwningWorld;
        bool m_IsPlaying;
    };
}
