//
//  Application.cpp
//  LighYearsGame
//
//  Created by Ori Sofer on 22/02/2025.
//

#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
    Application::Application(unsigned int width, unsigned int height, std::string title, sf::Uint32 style)
    : m_Window{sf::VideoMode(width,height),title, style},
    m_TargetFrameRate{60.0f},
    m_TickClock{},
    m_CurrentWorld{nullptr},
    m_CleanCycleClock{},
    m_CleanCycleInterval{2.f}
    {

    }

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

        // ticking the world logic (kind of like update in unity)
        if (m_CurrentWorld)
        {
            m_CurrentWorld->BeginPlayInternal();
            m_CurrentWorld->TickInternal(deltaTime);
        }

        // ticking the physics logic (kind of like fixed update in unity)
        PhysicsSystem::Get().Step(deltaTime);

        if (m_CleanCycleClock.getElapsedTime().asSeconds() >= m_CleanCycleInterval)
        {
            m_CleanCycleClock.restart();
            AssetManager::Get().CleanCycle();

            if (m_CurrentWorld)
            {
                m_CurrentWorld->CleanCycle();
            }
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
        if (m_CurrentWorld)
        {
            m_CurrentWorld->Render(m_Window);
        }
    }

    Application::~Application()
    {
        LOG("Application destructor called");
        m_Window.close();
    }

    sf::Vector2u Application::GetWindowSize() const
    {
        return m_Window.getSize();
    }

    sf::RenderWindow * Application::GetWindow()
    {
        return &m_Window;
    }
}
