
#include "framework/World.h"
#include "framework/Core.h"

namespace ly
{

World::World(Application* owningApp)
: m_OwningApp{owningApp}, m_Playing{false} { }

void
World::BeginPlayInternal()
{
    if (!m_Playing)
    {
        m_Playing = true;
        BeginPlay();
    }
}

void
World::TickInternal(float deltaTime)
{
    Tick(deltaTime);
}

void
World::BeginPlay()
{
    LOG("World Begin");
}

void World::Tick(float deltaTime)
{
    LOG("Ticking at framerate %f", 1.0f / deltaTime);
}

World::~World()
{
    
}

}
