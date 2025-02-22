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
m_Window{sf::VideoMode(1024,1440), "Light Years"} {}

void
Application::Run()
{
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
    }
}

Application::~Application()
{
    std::cout << "Application destructor called" << std::endl;
    m_Window.close();
}

}
