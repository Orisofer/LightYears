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
        return LoadAsset(texturePath, m_TextureMap);
    }

    shared<sf::Font> AssetManager::LoadFont(const std::string &fontPath)
    {
        return LoadAsset(fontPath, m_FontMap);
    }

    void AssetManager::CleanCycle()
    {
        CleanUniqueRef(m_TextureMap);
        CleanUniqueRef(m_FontMap);
    }

    void AssetManager::SetAssetRootDirectory(const std::string &assetRootDirectory)
    {
        m_AssetRootDirectory = assetRootDirectory;
    }

    AssetManager::AssetManager() : m_AssetRootDirectory{}
    {
    }
}
