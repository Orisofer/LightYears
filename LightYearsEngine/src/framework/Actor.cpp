#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath) : m_OwningWorld{owningWorld}, m_IsPlaying(false),
    m_Sprite(), m_Texture()
    {
        //SetTexture(texturePath);
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
        m_Texture.loadFromFile(texturePath);
        m_Sprite.setTexture(m_Texture);

        const int texWidth = m_Texture.getSize().x;
        const int texHeight = m_Texture.getSize().y;

        m_Sprite.setTextureRect(sf::IntRect{sf::Vector2i{0,0}, sf::Vector2i{texWidth, texHeight}});
    }

    void Actor::Render(sf::RenderWindow &window)
    {
        if (IsPendingDestroyed()) return;

        window.draw(m_Sprite);
    }

    Actor::~Actor()
    {
        LOG("Actor Destroyed");
    }
}

