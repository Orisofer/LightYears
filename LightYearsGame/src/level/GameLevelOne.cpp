//
// Created by Ori Sofer on 09/05/2025.
//

#include "level/GameLevelOne.h"

#include "enemy/TwinBladeStage.h"
#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "enemy/TwinBladeStage.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp) :
    World(owningApp)
    {
        m_PlayerSpaceship = SpawnActor<PlayerSpaceship>();

        sf::Vector2u windowSize = owningApp->GetWindowSize();
        m_PlayerSpaceship.lock()->SetLocation(sf::Vector2f(owningApp->GetWindowSize().x / 2.f, owningApp->GetWindowSize().y / 2.f));
    }

    void GameLevelOne::BeginPlay()
    {
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<TwinBladeStage>(new TwinBladeStage(this)));
        AddStage(shared<VanguardStage>(new VanguardStage(this)));
    }
}
