//
// Created by Ori Sofer on 22/08/2025.
//

#include "enemy/Boss.h"

namespace ly
{
    Boss::Boss(World *owningWorld, const std::string& texturePath) :
    EnemySpaceship(owningWorld, texturePath),
    m_Speed(100.f),
    m_SwitchDistanceToEdge(100.f)
    {

    }

    void Boss::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
    }

    void Boss::BeginPlay()
    {
        EnemySpaceship::BeginPlay();
    }
}
