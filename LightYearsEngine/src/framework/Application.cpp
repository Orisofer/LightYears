//
//  Application.cpp
//  LighYearsGame
//
//  Created by Ori Sofer on 22/02/2025.
//

#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
    Application::Application() : m_Window{sf::VideoMode(600,800),
"Light Years"}, m_TargetFrameRate{60.0f}, m_TickClock{},
    m_CurrentWorld{nullptr} {}

    Application::Application(unsigned int width, unsigned int height, std::string title, sf::Uint32 style) : m_Window{sf::VideoMode(width,height),
title, style}, m_TargetFrameRate{60.0f}, m_TickClock{}, m_CurrentWorld{nullptr} {}

    void Application::Run()
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

            float frameDeltaTime = m_TickClock.restart().asSeconds();
            accumulatedTime += frameDeltaTime;

            while (accumulatedTime > targetDeltaTime)
            {
                accumulatedTime -= targetDeltaTime;

                TickInternal(targetDeltaTime);
                RenderInternal();
            }
        }
    }

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);

        if (m_CurrentWorld)
        {
            m_CurrentWorld->BeginPlayInternal();
            m_CurrentWorld->TickInternal(deltaTime);
        }
    }

    void Application::Tick(float deltaTime)
    {

    }

    void Application::RenderInternal()
    {
        m_Window.clear();
        Render();
        m_Window.display();
    }

    void Application::Render()
    {
        sf::RectangleShape rect{sf::Vector2f{100,100}};
        rect.setFillColor(sf::Color::Red);
        rect.setOrigin(50,50);
        rect.setPosition((m_Window.getSize().x / 2), (m_Window.getSize().y / 2));
        m_Window.draw(rect);
    }

    Application::~Application()
    {
        LOG("Application destructor called");
        m_Window.close();
    }
}
