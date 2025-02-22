#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow renderWindow{sf::VideoMode(200,500), "My Window"};
    
    while (renderWindow.isOpen())
    {
        sf::Event event;
        
        while (renderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                renderWindow.close();
            }
            
            renderWindow.clear(sf::Color::Blue);
            renderWindow.display();
        }
    }
    
    std::cout << "Hello" << std::endl;
}
