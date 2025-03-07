#include "EntryPoint.h"
#include "framework/Application.h"

int main()
{
    ly::Application* app = GetApplication(600, 800, "Light Years Game", sf::Style::Titlebar | sf::Style::Close);
    app->Run();
    
    delete app;
}
