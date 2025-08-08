#include <config.h>

#include "gameFramework/GameApplication.h"
#include "level/GameLevelOne.h"
#include "framework/AssetManager.h"
#include "level/MainMenuLevel.h"

ly::Application* GetApplication(const unsigned int width, const unsigned int height, const std::string title, sf::Uint32 style)
{
    return new ly::GameApplication{width, height, title, style};
}

namespace ly
{
    GameApplication::GameApplication(unsigned int width, unsigned int height, const std::string title, sf::Uint32 style) :
    Application(width, height, title, style)
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDirectory());
        weak<MainMenuLevel> newWorld = LoadWorld<MainMenuLevel>();
    }
}