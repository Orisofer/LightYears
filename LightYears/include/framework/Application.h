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
    ~Application();
private:
    sf::RenderWindow m_Window;
};

}

#endif /* Application_hpp */
