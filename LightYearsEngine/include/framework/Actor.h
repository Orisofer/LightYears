#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"
#include "framework/Delegate.h"

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

        void SetLocation(const sf::Vector2f& location);
        void SetRotation(float rotation);
        void AddActorLocationOffset(const sf::Vector2f& offset);
        void AddActorRotationOffset(float rotationOffset);
        void SetSizeMultiplier(float multiplier);
        float GetRotation();

        sf::Vector2f GetLocation() const;
        sf::Vector2f GetForwardDirection();
        sf::Vector2f GetRightDirection();
        sf::Vector2f GetLeftDirection();
        sf::Vector2f GetBackwardDirection();
        sf::Vector2f GetCustomRelativeDirection(float angle);
        sf::FloatRect GetGlobalBounds() const;
        sf::Vector2u GetSize() const;

        void SetTeamID(uint8 teamID);
        uint8 GetTeamID() const;
        bool IsOtherHostile(Actor* other) const;

        virtual void ApplyDamage(float damage);

        World* GetWorld() const;

        bool IsActorOutOfWindowBounds(float allowedOffset = 10.f) const;

        void SetEnablePhysics(bool enable);

        virtual void OnActorBeginOverlap(Actor * other);
        virtual void OnActorEndOverlap(Actor * other);

        void Destroy() override;

        static uint8 GetNeutralTeamID();

        sf::Sprite& GetSprite();

        Delegate<Actor*> ActorDestroyed;

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
        uint8 m_TeamID;

        const static uint8 s_NeutralTeamID = 255;
    };


}
