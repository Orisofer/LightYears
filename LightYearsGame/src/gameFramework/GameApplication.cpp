#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* GetApplication(const unsigned int width, const unsigned int height, const std::string title, sf::Uint32 style)
{
    return new ly::GameApplication{width, height, title, style};
}

namespace ly
{
    GameApplication::GameApplication(unsigned int width, unsigned int height, const std::string title, sf::Uint32 style) :
    Application(width, height, title, style)
    {
        weak<World> newWorld = LoadWorld<World>();
        newWorld.lock()->SpawnActor<Actor>();
        m_ActorToDestroy = newWorld.lock()->SpawnActor<Actor>();
        m_Counter = 0;
    }

    void GameApplication::Tick(float deltaTime)
    {
        m_Counter += deltaTime;

        if (m_Counter > 4.f)
        {
            if (!m_ActorToDestroy.expired())
            {
                m_ActorToDestroy.lock()->Destroy();
            }
        }
    }
}
