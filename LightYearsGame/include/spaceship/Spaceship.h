//
// Created by Ori Sofer on 15/03/2025.
//

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "framework/Actor.h"

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
    private:
        sf::Vector2f m_Velocity;
    };
}

#endif //SPACESHIP_H
