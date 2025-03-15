#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"
#include "framework/MathUtility.h"

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
        m_ActorToDestroy.lock()->SetTexture(GetResourceDirectory() + "SpaceShooterRedux/PNG/playerShip1_blue.png");

        m_ActorToDestroy.lock()->SetActorLocation(sf::Vector2f(width / 2.f, height / 2.f));
        m_ActorToDestroy.lock()->SetActorRotation(ly::DegreesToRadians(90.f));
        m_Counter = 0;
    }

    void GameApplication::Tick(float deltaTime)
    {
    }
}
