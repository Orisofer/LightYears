#pragma once

#include <framework/Application.h>
#include "framework/Core.h"

namespace ly
{
    class Actor;
    class PlayerSpaceship;

    class GameApplication : public Application
    {
    public:
        GameApplication(unsigned int width, unsigned int height, std::string title, sf::Uint32 style);
    };
}
