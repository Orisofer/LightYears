//
// Created by Ori Sofer on 15/03/2025.
//

#include "spaceship/Spaceship.h"

namespace ly
{
    Spaceship::Spaceship(World *owningWorld, const std::string&texturePath) :
    Actor(owningWorld, texturePath),
    m_Velocity{},
    m_HealthComp{100,100}
    {

    }

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
        m_HealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);

        m_HealthComp.ChangeHealth(-88);
    }

    void Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        AddActorLocationOffset(GetVelocity() * deltaTime);
    }

    void Spaceship::SetVelocity(const sf::Vector2f &velocity)
    {
        m_Velocity = velocity;
    }

    void Spaceship::Shoot()
    {
    }

    sf::Vector2f Spaceship::GetVelocity() const
    {
        return m_Velocity;
    }

    void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
    {
        LOG("on health changed: amount: %f, health: %f / %f", amt, health, maxHealth);
    }
}
