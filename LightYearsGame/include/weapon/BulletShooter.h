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
        BulletShooter(Actor* owner, float coolDownTime = 0.1f, const sf::Vector2f& localPositionOffset = sf::Vector2f(0,0),
            float localRotationOffset = 0, const std::string& texturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        bool IsOnCooldown() const override;
        bool CanShoot() const override;
        void SetTexturePath(const std::string& texturePath);
        virtual void LevelUp(int amount = 1) override;
    private:
        void ShootImpl() override;
        sf::Clock m_CooldownClock;
        sf::Vector2f m_LocalPositionOffset;
        std::string m_TexturePath;
        float m_LocalRotationOffset;
        float m_CooldownTime;
        float m_BulletsAngle;
    };
}

#endif //BULLETSHOOTER_H
