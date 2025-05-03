//
// Created by Ori Sofer on 03/05/2025.
//

#ifndef ENEMYSPACESHIP_H
#define ENEMYSPACESHIP_H

#include "spaceship/Spaceship.h"

namespace ly
{
    class EnemySpaceship : public Spaceship
    {
    public:
        EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage = 200.f);
        virtual void Tick(float deltaTime) override;
    private:
        float m_CollisionDamage;

        virtual void OnActorBeginOverlap(Actor *other) override;

    };
}

#endif //ENEMYSPACESHIP_H
