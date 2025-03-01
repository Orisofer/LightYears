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
    void BeginPlayInternal();
    virtual void BeginPlay();
    virtual void Tick(float deltaTime);
    virtual ~Actor();

private:
    
    World* m_OwningWorld;
    bool m_IsPlaying;
    
};




}
