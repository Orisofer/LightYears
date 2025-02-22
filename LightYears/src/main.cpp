#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "framework/Application.h"


int main()
{
    std::unique_ptr<ly::Application> app = std::make_unique<ly::Application>(300,550);
    app->Run();
    
    std::cout << "Hello" << std::endl;
}
