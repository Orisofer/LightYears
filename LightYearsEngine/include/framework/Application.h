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
    
    Application();
    Application(float width, float height);
    
    void Run();
    
    template<typename T>
    weak<World> LoadWorld();
    
    ~Application();
    
private:
    
    void TickInternal(float deltaTime);
    void RenderInternal();
    
    virtual void Tick(float deltaTime);
    virtual void Render();
    
    sf::RenderWindow m_Window;
    sf::Clock m_TickClock;
    
    shared<World> m_CurrentWorld;
    
    float m_TargetFrameRate;
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
