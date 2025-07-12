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
        FrontalWiperShooter(Actor* owningActor, float cooldownTime = .3f, const sf::Vector2f& localOffset = sf::Vector2f(0.f,0.f));
    private:
        virtual void ShootImpl() override;

        BulletShooter m_ShooterLeft;
        BulletShooter m_ShooterMid;
        BulletShooter m_ShooterRight;
    };
}

#endif //FRONTALWIPERSHOOTER_H
