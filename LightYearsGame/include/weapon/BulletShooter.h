//
// Created by Ori Sofer on 24/03/2025.
//

#ifndef BULLETSHOOTER_H
#define BULLETSHOOTER_H

#include <SFML/System.hpp>
#include "framework/Core.h"
#include "Shooter.h"

namespace ly
{
    class BulletShooter : public Shooter
    {
    public:
        BulletShooter(Actor* owner, float coolDownTime = 0.1f);
        bool IsOnCooldown() const override;
        bool CanShoot() const override;
        ~BulletShooter() = default;
    private:
        void ShootImpl() override;
        sf::Clock m_CooldownClock;
        float m_CooldownTime;
        float m_BulletsAngle;
    };
}

#endif //BULLETSHOOTER_H
