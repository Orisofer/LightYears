//
//  Application.hpp
//  LighYearsGame
//
//  Created by Ori Sofer on 22/02/2025.
//

#ifndef Application_hpp
#define Application_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "World.h"
#include "framework/Core.h"

namespace ly
{
    class World;

    class Application
    {
    public:
        Application(unsigned int width, unsigned int height, const std::string title, sf::Uint32 style);
        void Run();

        template<typename T>
        weak<T> LoadWorld();

        ~Application();
        sf::Vector2u GetWindowSize() const;
        sf::RenderWindow& GetWindow();
        const sf::RenderWindow& GetWindow() const;

        void QuitApplication();

    private:
        void TickInternal(float deltaTime);
        void RenderInternal();
        bool DispatchEvent(const sf::Event& event);
        virtual void Tick(float deltaTime);
        virtual void Render();

        sf::RenderWindow m_Window;
        sf::Clock m_TickClock;
        sf::Clock m_CleanCycleClock;
        shared<World> m_CurrentWorld;
        shared<World> m_PendingWorld;
        float m_TargetFrameRate;
        float m_CleanCycleInterval;
    };

    template<typename T>
    weak<T> Application::LoadWorld()
    {
        shared<T> newWorldPtr{ new T{ this } };
        m_PendingWorld = newWorldPtr;
        return newWorldPtr;
    }
}

#endif /* Application_hpp */
