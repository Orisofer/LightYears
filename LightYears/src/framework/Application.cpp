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

Application::Application(float width, float height) :
m_Window{sf::VideoMode(width,height), "Light Years"},
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
        }
        
        accumulatedTime += m_TickClock.restart().asSeconds();
        
        while (accumulatedTime > targetDeltaTime)
        {
            accumulatedTime -= targetDeltaTime;
            
            TickInternal(targetDeltaTime);
            RenderInternal();
        }
    }
}

void
Application::TickInternal(float deltaTime)
{
    Tick(deltaTime);
}

void
Application::Tick(float deltaTime)
{
    
}

void Application::RenderInternal()
{
    m_Window.clear();
    Render();
    m_Window.display();
}

void
Application::Render()
{
    sf::RectangleShape rect{sf::Vector2f{100,100}};
    rect.setFillColor(sf::Color::Red);
    rect.setOrigin(50,50);
    rect.setPosition((m_Window.getSize().x / 2), (m_Window.getSize().y / 2));
    m_Window.draw(rect);
}

Application::~Application()
{
    std::cout << "Application destructor called" << std::endl;
    m_Window.close();
}


}
