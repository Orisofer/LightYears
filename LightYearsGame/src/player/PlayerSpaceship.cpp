//
// Created by Ori Sofer on 15/03/2025.
//

#include <SFML/System.hpp>

#include "player/PlayerSpaceship.h"

namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World *owningWorld, const std::string &texturePath)
        : Spaceship{owningWorld, texturePath}, m_MoveInput{}, m_MoveSpeed{200.f}
    {

    }

    void PlayerSpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        HandleInput();
        ConsumeInput(deltaTime);
    }

    void PlayerSpaceship::SetSpeed(float speed)
    {
        m_MoveSpeed = speed;
    }

    float PlayerSpaceship::GetSpeed() const
    {
        return m_MoveSpeed;
    }

    void PlayerSpaceship::HandleInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m_MoveInput.y += -1.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m_MoveInput.y += 1.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            m_MoveInput.x += -1.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m_MoveInput.x += 1.f;
        }
    }

    void PlayerSpaceship::ConsumeInput(float deltaTime)
    {
        SetVelocity(m_MoveInput * m_MoveSpeed);
        m_MoveInput = sf::Vector2f{0.f,0.f};
    }
}
