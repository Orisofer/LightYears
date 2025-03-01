#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

ly::Application* GetApplication(float width, float height)
{
    return new ly::GameApplication{width, height};
}

namespace ly
{

GameApplication::GameApplication()
{
    LoadWorld<World>();
}

GameApplication::GameApplication(float width, float height)
: Application(width, height)
{
    weak<World> newWorld = LoadWorld<World>();
    newWorld.lock()->SpawnActor<Actor>();
}

}
