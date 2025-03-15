#include "gameFramework/GameApplication.h"

#include <config.h>

#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"
#include "spaceship/Spaceship.h"

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
        m_PlayerSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
        m_PlayerSpaceship.lock()->SetTexture(GetResourceDirectory() + "SpaceShooterRedux/PNG/playerShip1_blue.png");

        m_PlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(width / 2.f, height / 2.f));
        m_PlayerSpaceship.lock()->SetActorRotation(ly::DegreesToRadians(90.f));
        m_PlayerSpaceship.lock()->SetVelocity(sf::Vector2f(0.f, -200.f));
        m_Counter = 0;
    }

    void GameApplication::Tick(float deltaTime)
    {
    }
}
