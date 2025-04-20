//
// Created by Ori Sofer on 20/04/2025.
//

#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "framework/Delegate.h"

namespace ly
{
    class HealthComponent
    {
    public:
        HealthComponent(float health, float maxHealth);
        void ChangeHealth(float amt);
        float GetHealth();
        float GetMaxHealth();
        Delegate<float, float, float> onHealthChanged;
    private:
        void TakeDamage(float amt);
        void Heal(float amt);
        void HealthEmpty();
        float m_MaxHealth;
        float m_Health;
    };
}

#endif //HEALTHCOMPONENT_H
