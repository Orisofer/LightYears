//
// Created by Ori Sofer on 15/03/2025.
//

#include <SFML/System.hpp>

#include "player/PlayerSpaceship.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiperShooter.h"

namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World *owningWorld, const std::string &texturePath)
    : Spaceship{owningWorld, texturePath},
    m_MoveInput{},
    m_MoveSpeed{200.f},
    m_BulletShooter{new ThreeWayShooter(this, 0.17f, {0.f, 50.f})}
    {
        // this works like a layer mask for collision detection filtering
        SetTeamID(1);
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

    void PlayerSpaceship::SetShooter(unique<Shooter>&& newShooter)
    {
        // if the new shooter is of the same type as the current shooter
        if (m_BulletShooter != nullptr && typeid(*m_BulletShooter) == typeid(*newShooter))
        {
            m_BulletShooter->LevelUp(1);
        }
        else
        {
            m_BulletShooter = std::move(newShooter);
        }
    }

    float PlayerSpaceship::GetSpeed() const
    {
        return m_MoveSpeed;
    }

    void PlayerSpaceship::Shoot()
    {
        if (m_BulletShooter)
        {
            m_BulletShooter->Shoot();
        }
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

        ClampInputOnEdge();
        NormalizeInput();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Shoot();
        }
    }

    void PlayerSpaceship::NormalizeInput()
    {
        Normalize<float>(m_MoveInput);
    }

    void PlayerSpaceship::ClampInputOnEdge()
    {
        sf::Vector2u worldSize = m_OwningWorld->GetWindowSize();
        sf::Vector2u spaceShipSize = GetSize();
        sf::Vector2f spaceshipPos = GetLocation();

        float halfSizeX = spaceShipSize.x * 0.5f;
        float halfSizeY = spaceShipSize.y * 0.5f;

        if (spaceshipPos.x < 0.f + halfSizeX && m_MoveInput.x == -1.f)
        {
            m_MoveInput.x = 0.f;
        }

        if (spaceshipPos.y < 0.f + halfSizeY && m_MoveInput.y == -1.f)
        {
            m_MoveInput.y = 0.f;
        }

        if (spaceshipPos.x > worldSize.x - halfSizeX && m_MoveInput.x == 1.f)
        {
            m_MoveInput.x = 0.f;
        }

        if (spaceshipPos.y > worldSize.y - halfSizeY && m_MoveInput.y == 1.f)
        {
            m_MoveInput.y = 0.f;
        }
    }

    void PlayerSpaceship::ConsumeInput(float deltaTime)
    {
        SetVelocity(m_MoveInput * m_MoveSpeed);
        m_MoveInput = sf::Vector2f{0.f,0.f};
    }
}
