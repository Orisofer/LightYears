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
        shared<sf::Font> LoadFont(const std::string& fontPath);
        void CleanCycle();
        void SetAssetRootDirectory(const std::string& assetRootDirectory);
    protected:
        AssetManager();
    private:
        static unique<AssetManager> assetManager;
        Dictionary<std::string , shared<sf::Texture>> m_TextureMap;
        Dictionary<std::string, shared<sf::Font>> m_FontMap;
        std::string m_AssetRootDirectory;

        template<typename T>
        shared<T> LoadAsset(const std::string& assetPath,
            Dictionary<std::string, shared<T>>& container);

        template<typename T>
        void CleanUniqueRef(Dictionary<std::string, shared<T>>& container);
    };

    template<typename T>
    shared<T> AssetManager::LoadAsset(const std::string &assetPath, Dictionary<std::string, shared<T>> &container)
    {
        auto foundIterator = container.find(assetPath);

        if (foundIterator != container.end())
        {
            return foundIterator->second;
        }

        shared<T> toLoad{new T};

        if (toLoad->loadFromFile(m_AssetRootDirectory + assetPath))
        {
            container.insert({assetPath, toLoad});
            return toLoad;
        }

        return shared<T>{nullptr};
    }

    template<typename T>
    void AssetManager::CleanUniqueRef(Dictionary<std::string, shared<T>>& container)
    {
        for (auto iter = container.begin(); iter != container.end();)
        {
            if (iter->second.use_count() == 1) // shared ptr has only 1 reference
            {
                LOG("Cleaning %s", iter->first.c_str());
                iter = container.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}

#endif //ASSETMANAGER_H
