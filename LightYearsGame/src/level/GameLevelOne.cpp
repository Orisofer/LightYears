//
// Created by Ori Sofer on 09/05/2025.
//

#include "level/GameLevelOne.h"
#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp) :
    World(owningApp)
    {
        m_PlayerSpaceship = SpawnActor<PlayerSpaceship>();
        m_PlayerSpaceship.lock()->SetLocation(sf::Vector2f(owningApp->GetWindowSize().x / 2.f, owningApp->GetWindowSize().y / 2.f));

        weak<Vanguard> testEnemySpaceship = SpawnActor<Vanguard>();
        testEnemySpaceship.lock()->SetLocation(sf::Vector2f(owningApp->GetWindowSize().x / 2.f, 100.f));
        testEnemySpaceship.lock()->SetRotation(180.f);
    }

    void GameLevelOne::BeginPlay()
    {
        m_TimerHandler_Test = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback_Test, 3.f, true);
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<GameStage>(new GameStage(this)));
    }

    void GameLevelOne::TimerCallback_Test()
    {
        LOG("TIMER CLLBACK TEST");
        TimerManager::Get().ClearTimer(m_TimerHandler_Test);
    }
}
