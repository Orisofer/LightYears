

#include <config.h>

#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"
#include "player/PlayerSpaceship.h"
#include "framework/AssetManager.h"
#include "enemy/Vanguard.h"

ly::Application* GetApplication(const unsigned int width, const unsigned int height, const std::string title, sf::Uint32 style)
{
    return new ly::GameApplication{width, height, title, style};
}

namespace ly
{
    GameApplication::GameApplication(unsigned int width, unsigned int height, const std::string title, sf::Uint32 style) :
    Application(width, height, title, style)
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDirectory());
        weak<World> newWorld = LoadWorld<World>();
        m_PlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
        m_PlayerSpaceship.lock()->SetLocation(sf::Vector2f(width / 2.f, height / 2.f));

        weak<Vanguard> testEnemySpaceship = newWorld.lock()->SpawnActor<Vanguard>();
        testEnemySpaceship.lock()->SetLocation(sf::Vector2f(width / 2.f, 100.f));
        testEnemySpaceship.lock()->SetRotation(180.f);

        m_Counter = 0;
    }

    void GameApplication::Tick(float deltaTime)
    {
        m_Counter += deltaTime;
        //
        // if (m_Counter >= 10.f)
        // {
        //     if (!m_PlayerSpaceship.expired())
        //     {
        //         m_PlayerSpaceship.lock()->Destroy();
        //     }
        // }
    }
}
