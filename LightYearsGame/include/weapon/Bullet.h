//
// Created by Ori Sofer on 29/03/2025.
//

#ifndef BULLET_H
#define BULLET_H
#include "framework/Actor.h"

namespace ly
{
    class Bullet : public Actor
    {
    public:
        Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 800.f, float damage = 10.f);

        virtual void BeginPlay() override;
        void Tick(float deltaTime) override;

        void SetSpeed(float speed);
        void SetDamage(float damage);
    private:
        void Move(float deltaTime);
        Actor* m_Owner;
        float m_Speed;
        float m_Damage;
    };
}

#endif //BULLET_H
