//
// Created by Ori Sofer on 15/03/2025.
//

#ifndef PLAYERSPACESHIP_H
#define PLAYERSPACESHIP_H

#include "spaceship/Spaceship.h"
#include "framework/Core.h"
#include "weapon/Shooter.h"
#include "framework/TimerManager.h"

namespace ly
{
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png");
        virtual void Tick(float deltaTime) override;
        virtual void ApplyDamage(float damage) override;
        virtual void BeginPlay() override;
        void SetSpeed(float speed);
        void SetShooter(unique<Shooter>&& newShooter);
        float GetSpeed() const;
        void Shoot() override;
    private:
        void HandleInput();
        void NormalizeInput();
        void ClampInputOnEdge();
        void ConsumeInput(float deltaTime);
        void StopInvulnerable();
        void UpdateInvulnerable(float deltaTime);

        TimerHandler m_InvulnerableTimerHandler;
        sf::Vector2f m_MoveInput;
        float m_MoveSpeed;
        float m_InvulnerableTime;
        float m_InvulnerableFlashInterval;
        float m_InvulnerableFlashTimer;
        float m_InvulnerableFlashDirection;
        bool m_Invulnerable;

        std::unique_ptr<Shooter> m_BulletShooter;
    };
}

#endif //PLAYERSPACESHIP_H
