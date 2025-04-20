//
// Created by Ori Sofer on 20/04/2025.
//

#include "gameplay/HealthComponent.h"

#include "framework/Core.h"

namespace ly
{
    HealthComponent::HealthComponent(float health, float maxHealth) :
    m_Health(health),
    m_MaxHealth(maxHealth)
    {
    }

    void HealthComponent::ChangeHealth(float amt)
    {
        if (amt == 0) return;
        if (m_Health == 0) return;

        m_Health += amt;

        if (m_Health < 0)
        {
            m_MaxHealth = 0;
        }

        if (m_Health > m_MaxHealth)
        {
            m_Health = m_MaxHealth;
        }

        if (amt < 0)
        {
            TakeDamage(-amt);

            if (m_Health <= 0)
            {
                HealthEmpty();
            }
        }
        else
        {
            Heal(amt);
        }

        onHealthChanged.Broadcast(amt, m_Health, m_MaxHealth);
    }

    float HealthComponent::GetHealth()
    {
        return m_Health;
    }

    float HealthComponent::GetMaxHealth()
    {
        return m_MaxHealth;
    }

    void HealthComponent::TakeDamage(float amt)
    {
        onTakenDamage.Broadcast(amt, m_Health, m_MaxHealth);
    }

    void HealthComponent::Heal(float amt)
    {
        onTakenDamage.Broadcast(amt, m_Health, m_MaxHealth);
    }

    void HealthComponent::HealthEmpty()
    {
        onHealthEmpty.Broadcast();
    }

}
