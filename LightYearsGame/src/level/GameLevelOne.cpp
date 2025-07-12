//
// Created by Ori Sofer on 09/05/2025.
//

#include "level/GameLevelOne.h"

#include "enemy/HexagonStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/UFO.h"
#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "gameplay/WaitStage.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp) :
    World(owningApp)
    {
        m_PlayerSpaceship = SpawnActor<PlayerSpaceship>();
        m_PlayerSpaceship.lock()->SetLocation(sf::Vector2f(owningApp->GetWindowSize().x / 2.f, owningApp->GetWindowSize().y / 2.f));
    }

    void GameLevelOne::BeginPlay()
    {
        // TESTING:

        weak<UFO> ufo = SpawnActor<UFO>(sf::Vector2f{0.f, 0.f});
        ufo.lock()->SetLocation(sf::Vector2f(GetWindowSize().x / 2.f, 300.f));
    }

    void GameLevelOne::InitGameStages()
    {

        // AddStage(shared<TwinBladeStage>(new TwinBladeStage(this)));
        // AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));
        // AddStage(shared<VanguardStage>(new VanguardStage(this)));
        // AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));
        // AddStage(shared<TwinBladeStage>(new TwinBladeStage(this)));
        // AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));
        // AddStage(shared<HexagonStage>(new HexagonStage(this)));
        //AddStage(shared<VanguardStage>(new VanguardStage(this)));
    }
}
