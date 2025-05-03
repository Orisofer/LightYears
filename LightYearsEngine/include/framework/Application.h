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
        weak<World> LoadWorld();
        ~Application();
        sf::Vector2u GetWindowSize() const;
    protected:
        sf::RenderWindow* GetWindow();
    private:
        void TickInternal(float deltaTime);
        void RenderInternal();
        virtual void Tick(float deltaTime);
        virtual void Render();
        sf::RenderWindow m_Window;
        sf::Clock m_TickClock;
        sf::Clock m_CleanCycleClock;
        shared<World> m_CurrentWorld;
        float m_TargetFrameRate;
        float m_CleanCycleInterval;
    };

    template<typename T>
    weak<World> Application::LoadWorld()
    {
        shared<T> newWorldPtr{ new T{ this } };
        m_CurrentWorld = newWorldPtr;
        return newWorldPtr;
    }
}

#endif /* Application_hpp */
