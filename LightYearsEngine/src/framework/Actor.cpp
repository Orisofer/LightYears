#include <box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath) :
    m_OwningWorld{owningWorld},
    m_IsPlaying(false),
    m_Sprite(),
    m_Texture(),
    m_PhysicsBody(nullptr),
    m_PhysicsEnabled(false),
    m_TeamID(GetNeutralTeamID())
    {
        if (!texturePath.empty())
        {
            SetTexture(texturePath);
        }
    }

    void Actor::BeginPlayInternal()
    {
        if (!m_IsPlaying)
        {
            m_IsPlaying = true;
            BeginPlay();
        }
    }

    void Actor::BeginPlay()
    {

    }

    void Actor::TickInternal(float deltaTime)
    {
        if (!IsPendingDestroyed())
        {
            Tick(deltaTime);
        }
    }

    void Actor::Tick(float deltaTime)
    {

    }

    void Actor::SetTexture(const std::string& texturePath)
    {
        if (texturePath == "none")
        {
            return;
        }

        m_Texture = AssetManager::Get().LoadTexture(texturePath);

        if (!m_Texture)
        {
            return;
        }

        m_Sprite.setTexture(*m_Texture);
        m_Sprite.setTextureRect(sf::IntRect{sf::Vector2i{}, sf::Vector2i{m_Texture->getSize()}});

        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow &window)
    {
        if (IsPendingDestroyed()) return;

        window.draw(m_Sprite);
    }

    void Actor::SetLocation(const sf::Vector2f &location)
    {
        m_Sprite.setPosition(location);
        UpdatePhysicsBodyTransform();
    }

    void Actor::SetRotation(float rotation)
    {
        m_Sprite.setRotation(rotation);
        UpdatePhysicsBodyTransform();
    }

    float Actor::GetRotation()
    {
        float rotation = m_Sprite.getRotation();
        return rotation;
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f &offset)
    {
        SetLocation(GetLocation() + offset);
    }

    void Actor::AddActorRotationOffset(float rotationOffset)
    {
        SetRotation(GetRotation() + rotationOffset);
    }

    void Actor::SetSizeMultiplier(float multiplier)
    {
        m_Sprite.setScale(multiplier, multiplier);
    }

    sf::Vector2f Actor::GetLocation() const
    {
        return m_Sprite.getPosition();
    }

    sf::Vector2f Actor::GetForwardDirection()
    {
        float rotation = GetRotation();
        sf::Vector2f forward = ly::RotationToVector(rotation - 90.f);
        return forward;
    }

    sf::Vector2f Actor::GetRightDirection()
    {
        float rotation = GetRotation();
        sf::Vector2f right = ly::RotationToVector(rotation);
        return right;
    }

    sf::Vector2f Actor::GetLeftDirection()
    {
        float rotation = GetRotation();
        sf::Vector2f left = ly::RotationToVector(rotation + 180.f);
        return left;
    }

    sf::Vector2f Actor::GetBackwardDirection()
    {
        float rotation = GetRotation();
        sf::Vector2f back = ly::RotationToVector(rotation + 90.f);
        return back;
    }

    sf::Vector2f Actor::GetCustomRelativeDirection(float angle)
    {
        return ly::RotationToVector(GetRotation() + angle);
    }

    sf::FloatRect Actor::GetGlobalBounds() const
    {
        return m_Sprite.getGlobalBounds();
    }

    sf::Vector2u Actor::GetSize() const
    {
        return m_Texture->getSize();
    }

    void Actor::SetTeamID(uint8 teamID)
    {
        m_TeamID = teamID;
    }

    uint8 Actor::GetNeutralTeamID()
    {
        return s_NeutralTeamID;
    }

    sf::Sprite& Actor::GetSprite()
    {
        sf::Sprite& spriteRef = m_Sprite;
        return spriteRef;
    }

    bool Actor::IsOtherHostile(Actor *other) const
    {
        if (other == nullptr) return false;

        if (GetTeamID() == GetNeutralTeamID() || other->GetTeamID() == GetNeutralTeamID())
        {
            return false;
        }

        return GetTeamID() != other->GetTeamID();
    }

    uint8 Actor::GetTeamID() const
    {
        return m_TeamID;
    }

    World * Actor::GetWorld() const
    {
        return m_OwningWorld;
    }

    bool Actor::IsActorOutOfWindowBounds(float allowedOffset) const
    {
        float windowWidth = GetWorld()->GetWindowSize().x;
        float windowHeight = GetWorld()->GetWindowSize().y;

        float actorWidth = GetGlobalBounds().width;
        float actorHeight = GetGlobalBounds().height;

        float actorPositionX = GetLocation().x;
        float actorPositionY = GetLocation().y;

        if ((actorPositionX + (actorWidth * 0.5f)) - allowedOffset > windowWidth)
        {
            return true;
        }

        if ((actorPositionX - (actorWidth * 0.5f)) + allowedOffset < 0)
        {
            return true;
        }

        if ((actorPositionY + (actorHeight * 0.5f)) - allowedOffset > windowHeight)
        {
            return true;
        }

        if (actorPositionY - (actorHeight * 0.5f) + allowedOffset < 0)
        {
            return true;
        }

        return false;
    }

    void Actor::CenterPivot()
    {
        sf::FloatRect bounds = m_Sprite.getGlobalBounds();
        m_Sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }

    void Actor::UpdatePhysicsBodyTransform()
    {
        if (m_PhysicsBody)
        {
            float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
            b2Vec2 pos{GetLocation().x * physicsScale, GetLocation().y * physicsScale};

            float rotDegrees = GetRotation();
            float rotRadians = DegreesToRadians(rotDegrees);
            b2Vec2 newVel{cos(rotRadians), sin(rotRadians)};

            m_PhysicsBody->SetTransform(pos, rotRadians);
            m_PhysicsBody->SetLinearVelocity(newVel);
        }
    }

    void Actor::SetEnablePhysics(bool enable)
    {
        m_PhysicsEnabled = enable;

        if (enable)
        {
            InitializePhysics();
        }
        else
        {
            UnInitializePhysics();
        }
    }

    void Actor::InitializePhysics()
    {
        if (!m_PhysicsBody)
        {
            m_PhysicsBody = PhysicsSystem::Get().AddListener(this);
        }
    }

    void Actor::UnInitializePhysics()
    {
        if (m_PhysicsBody)
        {
            m_PhysicsBody->GetUserData().pointer = 0;

            PhysicsSystem::Get().RemoveListener(m_PhysicsBody);
            m_PhysicsBody = nullptr;
        }
    }

    void Actor::OnActorBeginOverlap(Actor *actor)
    {
        // no-op
    }

    void Actor::OnActorEndOverlap(Actor *other)
    {
        // no-op
    }

    void Actor::ApplyDamage(float damage)
    {
        // no-op
    }

    void Actor::Destroy()
    {
        UnInitializePhysics();
        ActorDestroyed.Broadcast(this);

        Object::Destroy();
    }

    Actor::~Actor()
    {
        LOG("Actor Destroyed");
    }
}

