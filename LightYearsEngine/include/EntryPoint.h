#pragma once
#include <string>
#include <SFML/Config.hpp>

namespace ly
{
    class Application;
}

extern ly::Application* GetApplication();
extern ly::Application* GetApplication(unsigned int width, unsigned int height, std::string title, sf::Uint32 style);
