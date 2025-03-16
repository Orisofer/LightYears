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

        if (toLoad->loadFromFile(m_AssetRootDirectory + texturePath))
        {
            m_TextureMap.insert({texturePath, toLoad});
            return toLoad;
        }

        return shared<sf::Texture>{nullptr};
    }

    void AssetManager::CleanCycle()
    {
        for (auto iter = m_TextureMap.begin(); iter != m_TextureMap.end();)
        {
            if (iter->second.unique())
            {
                LOG("Cleaning texture %s", iter->first.c_str());
                iter = m_TextureMap.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    void AssetManager::SetAssetRootDirectory(const std::string &assetRootDirectory)
    {
        m_AssetRootDirectory = assetRootDirectory;
    }

    AssetManager::AssetManager() : m_AssetRootDirectory{}
    {
    }
}
