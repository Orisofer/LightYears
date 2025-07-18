//
// Created by Ori Sofer on 12/07/2025.
//

#ifndef FRONTALWIPERSHOOTER_H
#define FRONTALWIPERSHOOTER_H

#include <SFML/Graphics.hpp>
#include "weapon/BulletShooter.h"

namespace ly
{
    class FrontalWiperShooter : public Shooter
    {
    public:
        FrontalWiperShooter(Actor* owningActor, float cooldownTime = .3f,
            const sf::Vector2f& localOffset = sf::Vector2f(0.f,0.f));
        virtual void LevelUp(int amount) override;
    private:
        virtual void ShootImpl() override;

        BulletShooter m_ShooterLeft;
        BulletShooter m_ShooterMid01;
        BulletShooter m_ShooterMid02;
        BulletShooter m_ShooterRight;
        BulletShooter m_MaxLevelShooterRight;
        BulletShooter m_MaxLevelShooterLeft;
    };
}

#endif //FRONTALWIPERSHOOTER_H
