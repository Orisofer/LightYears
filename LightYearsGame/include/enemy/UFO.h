//
// Created by Ori Sofer on 12/07/2025.
//

#ifndef UFO_H
#define UFO_H

#include "enemy/EnemySpaceship.h"

namespace ly
{
    class BulletShooter;

    class UFO : public EnemySpaceship
    {
    public:
        UFO(World* owningWorld, const sf::Vector2f &velocity, const std::string& texturePath = "SpaceShooterRedux/PNG/ufoYellow.png",
            float rotationSpeed = 40.f);
        virtual void Tick(float deltaTime) override;
    private:
        virtual void Shoot() override;

        unique<BulletShooter> m_Shooter01;
        unique<BulletShooter> m_Shooter02;
        unique<BulletShooter> m_Shooter03;

        float m_RotationSpeed;
    };
}

#endif //UFO_H
