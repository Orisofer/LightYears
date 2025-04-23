//
// Created by Ori Sofer on 15/03/2025.
//

#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"

namespace ly
{
    Spaceship::Spaceship(World *owningWorld, const std::string&texturePath) :
    Actor(owningWorld, texturePath),
    m_Velocity{},
    m_HealthComp{100,100},
    m_BlinkTime(0.f),
    m_BlinkDuration(0.2f),
    m_BlinkColorOffset{255, 0,0, 255}
    {

    }

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);

        // register to health components callbacks
        m_HealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
        m_HealthComp.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
        m_HealthComp.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::Blow);
    }

    void Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        AddActorLocationOffset(GetVelocity() * deltaTime);
        UpdateBlink(deltaTime);
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

    void Spaceship::ApplyDamage(float damage)
    {
        m_HealthComp.ChangeHealth(-damage);
    }

    void Spaceship::Blink()
    {
        if (m_BlinkTime == 0)
        {
            m_BlinkTime = m_BlinkDuration;
        }
    }

    void Spaceship::UpdateBlink(float deltaTime)
    {
        if (m_BlinkTime > 0)
        {
            m_BlinkTime -= deltaTime;
            m_BlinkTime = m_BlinkTime > 0 ? m_BlinkTime : 0;

            GetSprite().setColor(LerpColor(sf::Color::White, m_BlinkColorOffset, m_BlinkTime / m_BlinkDuration));
        }
    }

    void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
    {
        LOG("spaceship: on health changed: amount: %f, health: %f / %f", amt, health, maxHealth);
    }

    void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
    {
        Blink();
    }

    void Spaceship::Blow()
    {
        LOG("spaceship: on health empty");
        Destroy();
    }
}
