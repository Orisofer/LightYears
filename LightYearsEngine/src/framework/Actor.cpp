#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{

Actor::Actor(World* owningWorld)
: m_OwningWorld{owningWorld},
m_IsPlaying(false) {}

void
Actor::BeginPlayInternal()
{
    if (!m_IsPlaying)
    {
        m_IsPlaying = true;
        BeginPlay();
    }
}

void
Actor::BeginPlay()
{
    LOG("actor begin play");
}

void
Actor::Tick(float deltaTime)
{
    
}

Actor::~Actor()
{
    LOG("Actor Destroyed");
}

}

