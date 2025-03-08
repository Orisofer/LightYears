//
// Created by Ori Sofer on 08/03/2025.
//


#include "framework/AssetManager.h"

namespace ly
{
    unique<AssetManager> AssetManager::assetManager{nullptr};

    AssetManager& AssetManager::Get()
    {
        if (assetManager == nullptr)
        {
            assetManager = std::move(unique<AssetManager>{new AssetManager});
        }

        return *assetManager;
    }

    shared<sf::Texture> AssetManager::LoadTexture(const std::string &texturePath)
    {
        auto foundIterator = m_TextureMap.find(texturePath);

        if (foundIterator != m_TextureMap.end())
        {
            return foundIterator->second;
        }

        shared<sf::Texture> toLoad{new sf::Texture};

        if (toLoad->loadFromFile(texturePath))
        {
            m_TextureMap.insert({texturePath, toLoad});
            return toLoad;
        }

        return shared<sf::Texture>{nullptr};
    }

    AssetManager::AssetManager()
    {
    }
}
