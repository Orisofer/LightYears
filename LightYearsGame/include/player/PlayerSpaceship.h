//
// Created by Ori Sofer on 15/03/2025.
//

#ifndef PLAYERSPACESHIP_H
#define PLAYERSPACESHIP_H

#include "spaceship/Spaceship.h"
#include "framework/Core.h"
#include "weapon/Shooter.h"

namespace ly
{
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png");
        virtual void Tick(float deltaTime) override;
        void SetSpeed(float speed);
        float GetSpeed() const;
        void Shoot() override;
    private:
        void HandleInput();
        void NormalizeInput();
        void ClampInputOnEdge();
        void ConsumeInput(float deltaTime);

        sf::Vector2f m_MoveInput;
        float m_MoveSpeed;

        std::unique_ptr<Shooter> m_BulletShooter;
    };
}

#endif //PLAYERSPACESHIP_H
