//
// Created by Ori Sofer on 12/07/2025.
//

#ifndef THREEWAY_H
#define THREEWAY_H

#include <SFML/Graphics.hpp>
#include "weapon/BulletShooter.h"

namespace ly
{
    class ThreeWayShooter : public Shooter
    {
    public:
        ThreeWayShooter(Actor* owningActor, float cooldownTime = .3f,
            const sf::Vector2f& localOffset = sf::Vector2f(0.f,0.f));
        virtual void LevelUp(int amount = 1) override;
    private:
        virtual void ShootImpl() override;

        BulletShooter m_ShooterLeft;
        BulletShooter m_ShooterMid;
        BulletShooter m_ShooterRight;
        BulletShooter m_MaxLevelShooterLeft;
        BulletShooter m_MaxLevelShooterRight;
    };
}

#endif //THREEWAY_H
