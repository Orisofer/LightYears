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

namespace ly
{

class Application
{
public:
    Application();
    void Run();
    void Tick(float deltaTime);
    void Render();
    ~Application();
private:
    sf::RenderWindow m_Window;
    sf::Clock m_TickClock;
    float m_TargetFrameRate;
};

}

#endif /* Application_hpp */
