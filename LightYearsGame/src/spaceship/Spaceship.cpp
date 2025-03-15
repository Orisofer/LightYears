//
// Created by Ori Sofer on 15/03/2025.
//

#include "spaceship/Spaceship.h"

namespace ly
{
    Spaceship::Spaceship(World *owningWorld, const std::string&texturePath) : Actor(owningWorld, texturePath), m_Velocity{}
    {

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

    sf::Vector2f Spaceship::GetVelocity() const
    {
        return m_Velocity;
    }
}
