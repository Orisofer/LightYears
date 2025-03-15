#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
    class World;

    class Actor : public Object
    {
    public:
        Actor(World* owningWorld, const std::string& texturePath = "");
        virtual ~Actor();
        void BeginPlayInternal();
        virtual void BeginPlay();
        void TickInternal(float deltaTime);
        virtual void Tick(float deltaTime);
        void SetTexture(const std::string& texturePath);
        void Render(sf::RenderWindow& window);

        void SetActorLocation(const sf::Vector2f& location);
        void SetActorRotation(float rotation);
        void AddActorLocationOffset(const sf::Vector2f& offset);
        void AddActorRotationOffset(float rotationOffset);
        sf::Vector2f GetLocation();
        float GetRotation();
        sf::Vector2f GetActorForwardDirection();
        sf::Vector2f GetActorRightDirection();

    private:
        void CenterPivot();

        World* m_OwningWorld;
        bool m_IsPlaying;
        sf::Sprite m_Sprite;
        shared<sf::Texture> m_Texture;
    };
}
