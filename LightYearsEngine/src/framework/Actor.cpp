#include <box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath) : m_OwningWorld{owningWorld}, m_IsPlaying(false),
    m_Sprite(), m_Texture(), m_PhysicsBody(nullptr), m_PhysicsEnabled(false)
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

    void Actor::SetTexture(const std::string &texturePath)
    {
        m_Texture = AssetManager::Get().LoadTexture(texturePath);

        if (!m_Texture) return;

        m_Sprite.setTexture(*m_Texture);

        const int texWidth = m_Texture->getSize().x;
        const int texHeight = m_Texture->getSize().y;

        m_Sprite.setTextureRect(sf::IntRect{sf::Vector2i{0,0}, sf::Vector2i{texWidth, texHeight}});

        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow &window)
    {
        if (IsPendingDestroyed()) return;

        window.draw(m_Sprite);
    }

    void Actor::SetActorLocation(const sf::Vector2f &location)
    {
        m_Sprite.setPosition(location);
        UpdatePhysicsBodyTransform();
    }

    void Actor::SetActorRotation(float rotation)
    {
        m_Sprite.setRotation(rotation);
        UpdatePhysicsBodyTransform();
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f &offset)
    {
        SetActorLocation(GetLocation() + offset);
    }

    void Actor::AddActorRotationOffset(float rotationOffset)
    {
        SetActorRotation(GetRotation() + rotationOffset);
    }

    sf::Vector2f Actor::GetLocation() const
    {
        return m_Sprite.getPosition();
    }

    float Actor::GetRotation()
    {
        return m_Sprite.getRotation();
    }

    // the +90.f and -90.f corrections are compensation
    // because for some reason when loading textures everything is flipped 90
    // degrees to the right
    sf::Vector2f Actor::GetActorForwardDirection()
    {
        return ly::RotationToVector(GetRotation() + 270.f);
    }

    // also here
    sf::Vector2f Actor::GetActorRightDirection()
    {
        return ly::RotationToVector(GetRotation() + 90.f);
    }

    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return m_Sprite.getGlobalBounds();
    }

    sf::Vector2u Actor::GetSize() const
    {
        return m_Texture->getSize();
    }

    World * Actor::GetWorld() const
    {
        return m_OwningWorld;
    }

    bool Actor::IsActorOutOfWindowBounds() const
    {
        float windowWidth = GetWorld()->GetWindowSize().x;
        float windowHeight = GetWorld()->GetWindowSize().y;

        float actorWidth = GetActorGlobalBounds().width;
        float actorHeight = GetActorGlobalBounds().height;

        float actorPositionX = GetLocation().x;
        float actorPositionY = GetLocation().y;

        if (actorPositionX + (actorWidth * 0.5f) > windowWidth)
        {
            return true;
        }

        if (actorPositionX + (actorWidth * 0.5f) < 0)
        {
            return true;
        }

        if (actorPositionY + (actorHeight * 0.5f) > windowHeight)
        {
            return true;
        }

        if (actorPositionY +  (actorHeight * 0.5f) < 0)
        {
            return true;
        }

        return false;
    }

    void Actor::CenterPivot()
    {
        sf::FloatRect bounds = m_Sprite.getGlobalBounds();
        m_Sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    void Actor::UpdatePhysicsBodyTransform()
    {
        if (m_PhysicsBody)
        {
            float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
            b2Vec2 pos{GetLocation().x * physicsScale, GetLocation().y * physicsScale};
            float rotation = DegreesToRadians(GetRotation());

            m_PhysicsBody->SetTransform(pos, rotation);
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
            PhysicsSystem::Get().RemoveListener(m_PhysicsBody);
            m_PhysicsBody = nullptr;
        }
    }

    void Actor::OnActorBeginOverlap(Actor *actor)
    {
        LOG("Overlap begin");
    }

    void Actor::OnActorEndOverlap(Actor *other)
    {
        LOG("Overlap finished");
    }

    void Actor::Destroy()
    {
        UnInitializePhysics();
        Object::Destroy();
    }

    Actor::~Actor()
    {
        LOG("Actor Destroyed");
    }
}

