//
// Created by Ori Sofer on 08/03/2025.
//

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
    class AssetManager
    {
    public:
        static AssetManager& Get();
        shared<sf::Texture> LoadTexture(const std::string& texturePath);
        void CleanCycle();
        void SetAssetRootDirectory(const std::string& assetRootDirectory);
    protected:
        AssetManager();
    private:
        static unique<AssetManager> assetManager;
        Dictionary<std::string , shared<sf::Texture>> m_TextureMap;
        std::string m_AssetRootDirectory;
    };
}

#endif //ASSETMANAGER_H
