//
// Created by Ori Sofer on 22/08/2025.
//

#include "enemy/BossStage.h"
#include "enemy/Boss.h"
#include "framework/Application.h"
#include "framework/World.h"
#include "framework/Actor.h"

namespace ly
{
    BossStage::BossStage(World *world) :
    GameStage(world)
    {

    }

    void BossStage::StartStage()
    {
        GameStage::StartStage();

        weak<Boss> boss = GetWorld()->SpawnActor<Boss>();

        sf::Vector2u windowSize = GetWorld()->GetWindowSize();

        boss.lock()->SetLocation({windowSize.x / 2.f, 200.f});
        boss.lock()->ActorDestroyed.BindAction(GetWeakRef(), &BossStage::BossDestroyed);
    }

    void BossStage::BossDestroyed(Actor* actor)
    {
        FinishStage();
    }
}
