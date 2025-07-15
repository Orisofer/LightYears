//
// Created by Ori Sofer on 15/03/2025.
//

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
    class Spaceship : public Actor
    {
        public:
        Spaceship(World* owningWorld, const std::string& texturePath = "");
        virtual void BeginPlay() override;
        virtual void Tick(float deltaTime) override;
        void SetVelocity(const sf::Vector2f &velocity);
        virtual void Shoot();
        sf::Vector2f GetVelocity() const;
        virtual void ApplyDamage(float damage) override;
        HealthComponent& GetHealthComponent();
    private:
        void Blink();
        void UpdateBlink(float deltaTime);
        virtual void OnHealthChanged(float amt, float health, float maxHealth);
        virtual void OnTakenDamage(float amt, float health, float maxHealth);
        virtual void Blow();
        sf::Vector2f m_Velocity;
        HealthComponent m_HealthComp;

        float m_BlinkTime;
        float m_BlinkDuration;
        sf::Color m_BlinkColorOffset;
    };
}

#endif //SPACESHIP_H
