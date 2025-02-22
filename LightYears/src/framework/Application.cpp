//
//  Application.cpp
//  LighYearsGame
//
//  Created by Ori Sofer on 22/02/2025.
//

#include "framework/Application.h"
#include <iostream>

namespace ly
{

Application::Application() :
m_Window{sf::VideoMode(1024,1440), "Light Years"},
m_TargetFrameRate{60.0f},
m_TickClock{} {}

void
Application::Run()
{
    m_TickClock.restart();
    
    float accumulatedTime = 0;
    float targetDeltaTime = 1.0f / m_TargetFrameRate;
    
    while (m_Window.isOpen())
    {
        sf::Event event;
        
        while (m_Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_Window.close();
            }
            
            m_Window.clear(sf::Color::Blue);
            m_Window.display();
        }
        
        accumulatedTime += m_TickClock.restart().asSeconds();
        
        while (accumulatedTime > targetDeltaTime)
        {
            accumulatedTime -= targetDeltaTime;
            
            Tick(targetDeltaTime);
            Render();
        }
    }
}

void
Application::Tick(float deltaTime)
{
    std::cout << "ticking at frame rate: " << 1 / deltaTime << std::endl;
}

void Application::Render()
{
    
}

Application::~Application()
{
    std::cout << "Application destructor called" << std::endl;
    m_Window.close();
}

}
