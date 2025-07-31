//
// Created by Ori Sofer on 31/07/2025.
//

#include "widgets/WidgetImage.h"
#include "framework/AssetManager.h"

namespace ly
{
    WidgetImage::WidgetImage(const std::string& filePath)
    {
        LoadTexture(filePath);
    }

    sf::FloatRect WidgetImage::GetBounds() const
    {
        sf::FloatRect bounds = m_Sprite.getGlobalBounds();
        return bounds;
    }

    void WidgetImage::SetImage(const shared<sf::Texture>& texture)
    {
        if (texture != nullptr)
        {
            m_Texture = texture;
            m_Sprite.setTexture(*m_Texture);
        }
    }

    void WidgetImage::SetSizeMultiplier(float multiplier)
    {
        m_Sprite.setScale(multiplier, multiplier);
    }

    void WidgetImage::Draw(sf::RenderWindow &windowRef)
    {
        windowRef.draw(m_Sprite);
    }

    void WidgetImage::LocationUpdated(const sf::Vector2f &newLocation)
    {
        m_Sprite.setPosition(newLocation);
    }

    void WidgetImage::RotationUpdated(float newRotation)
    {
        m_Sprite.setRotation(newRotation);
    }

    void WidgetImage::LoadTexture(const std::string &path)
    {
        AssetManager& assetManager = AssetManager::Get();
        shared<sf::Texture> newTexture = assetManager.LoadTexture(path);
        m_Texture = newTexture;
        m_Sprite = sf::Sprite(*m_Texture);
    }
}
