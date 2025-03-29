#include "framework/Actor.h"

#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/MathUtility.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath) : m_OwningWorld{owningWorld}, m_IsPlaying(false),
    m_Sprite(), m_Texture()
    {
        SetTexture(texturePath);
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
    }

    void Actor::SetActorRotation(float rotation)
    {
        m_Sprite.setRotation(rotation);
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f &offset)
    {
        SetActorLocation(GetLocation() + offset);
    }

    void Actor::AddActorRotationOffset(float rotationOffset)
    {
        SetActorRotation(GetRotation() + rotationOffset);
    }

    sf::Vector2f Actor::GetLocation()
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

    sf::Vector2u Actor::GetSize() const
    {
        return m_Texture->getSize();
    }

    World * Actor::GetWorld() const
    {
        return m_OwningWorld;
    }

    void Actor::CenterPivot()
    {
        sf::FloatRect bounds = m_Sprite.getGlobalBounds();
        m_Sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    Actor::~Actor()
    {
        LOG("Actor Destroyed");
    }
}

