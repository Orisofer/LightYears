//
// Created by Ori Sofer on 24/04/2025.
//

#include "VFX/Particle.h"
#include "framework/MathUtility.h"

namespace ly
{
    Particle::Particle(World *owningWorld, const std::string &texturePath)
        : Actor(owningWorld, texturePath), m_Velocity(), m_Lifetime(1.0f), m_Timer()
    {

    }

    void Particle::BeginPlay()
    {
        Actor::BeginPlay();
    }

    void Particle::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        Move(deltaTime);
        Fade(deltaTime);

        if (m_Timer.getElapsedTime().asSeconds() >= m_Lifetime)
        {
            Destroy();
        }
    }

    void Particle::RandomVelocity(float minSpeed, float maxSpeed)
    {
        float speed = RandomRange(minSpeed, maxSpeed);
        m_Velocity = RandomUnitVector() * speed;
    }

    void Particle::RandomSize(float minSize, float maxSize)
    {
        float scale = RandomRange(minSize, maxSize);
        GetSprite().setScale(scale,scale);
    }

    void Particle::RandomLifetime(float minLifetime, float maxLifetime)
    {
        m_Lifetime = RandomRange(minLifetime, maxLifetime);
    }

    void Particle::Move(float deltaTime)
    {
        AddActorLocationOffset(m_Velocity * deltaTime);
    }

    void Particle::Fade(float deltaTime)
    {
        float elapsedTime = m_Timer.getElapsedTime().asSeconds();

        sf::Color transparentColor = sf::Color(255,255,255,0);
        sf::Vector2f zeroScale = sf::Vector2f(0.0f, 0.0f);

        GetSprite().setColor(LerpColor(GetSprite().getColor(), transparentColor, elapsedTime / m_Lifetime));
        GetSprite().setScale(LerpVector(GetSprite().getScale(), zeroScale, elapsedTime / m_Lifetime));
    }
}
