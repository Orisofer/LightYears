//
// Created by Ori Sofer on 09/05/2025.
//

#include "level/GameLevelOne.h"

#include "enemy/HexagonStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/UFOStage.h"
#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerManager.h"
#include "reward/Reward.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp) :
    World(owningApp)
    {
        // m_PlayerSpaceship = SpawnActor<PlayerSpaceship>();
        // m_PlayerSpaceship.lock()->SetLocation(sf::Vector2f(owningApp->GetWindowSize().x / 2.f,
        //     owningApp->GetWindowSize().y / 2.f));

    }

    void GameLevelOne::BeginPlay()
    {
        Player player = PlayerManager::Get().CreateNewPlayer();
        player.SpawnSpaceship(this);
        // Enemy TESTING:
        // weak<UFO> ufo = SpawnActor<UFO>(sf::Vector2f{0.f, 0.f});
        // ufo.lock()->SetLocation(sf::Vector2f(GetWindowSize().x / 2.f, 300.f));

        // reward TESTING
        // weak<Reward> reward = SpawnActor<Reward>("SpaceShooterRedux/PNG/Power-ups/bolt_gold.png", RewardThreeWayShooter);
        // reward.lock()->SetLocation(sf::Vector2f(GetWindowSize().x / 2.f, 100.f));
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<VanguardStage>(new VanguardStage(this)));
        AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));

        AddStage(shared<TwinBladeStage>(new TwinBladeStage(this)));
        AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));

        AddStage(shared<HexagonStage>(new HexagonStage(this)));
        AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));

        AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));
        AddStage(shared<UFOStage>(new UFOStage(this)));
    }
}
