#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

class b2Body;

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
        float GetRotation();
        sf::Vector2f GetLocation() const;
        sf::Vector2f GetActorForwardDirection();
        sf::Vector2f GetActorRightDirection();
        sf::FloatRect GetActorGlobalBounds() const;
        sf::Vector2u GetSize() const;

        World* GetWorld() const;

        bool IsActorOutOfWindowBounds() const;

        void SetEnablePhysics(bool enable);

        virtual void OnActorBeginOverlap(Actor * other);
        virtual void OnActorEndOverlap(Actor * other);

        void Destroy() override;

    protected:
        World* m_OwningWorld;

    private:
        void CenterPivot();
        void UpdatePhysicsBodyTransform();
        void InitializePhysics();
        void UnInitializePhysics();
        bool m_IsPlaying;
        sf::Sprite m_Sprite;
        shared<sf::Texture> m_Texture;
        b2Body* m_PhysicsBody;
        bool m_PhysicsEnabled;
    };
}
