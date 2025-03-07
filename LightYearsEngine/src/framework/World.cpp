
#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly
{
    World::World(Application* owningApp) : m_OwningApp{owningApp}, m_Playing{false}, m_Actors{}, m_PendingActors{} {}

    void World::BeginPlayInternal()
    {
        if (!m_Playing)
        {
            m_Playing = true;
            BeginPlay();
        }
    }

    void World::TickInternal(float deltaTime)
    {
        for (shared<Actor> actor : m_PendingActors)
        {
            m_Actors.push_back(actor);
            actor->BeginPlayInternal();
        }

        m_PendingActors.clear();

        for (auto iter = m_Actors.begin(); iter != m_Actors.end(); )
        {
            if (iter->get()->IsPendingDestroyed())
            {
                iter = m_Actors.erase(iter);
            }
            else
            {
                iter->get()->TickInternal(deltaTime);
                ++iter;
            }
        }
        Tick(deltaTime);
    }

    void World::Render(sf::RenderWindow &window)
    {
        for (shared<Actor>& actor : m_Actors)
        {
            actor->Render(window);
        }

    }

    void World::BeginPlay()
    {
        LOG("World Begin");
    }

    void World::Tick(float deltaTime)
    {
        //LOG("Ticking at framerate %f", 1.0f / deltaTime);
    }

    World::~World()
    {

    }
}
