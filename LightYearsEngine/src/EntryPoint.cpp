#include "EntryPoint.h"
#include "framework/Application.h"

int main()
{
    ly::Application* app = GetApplication(600.f, 800.f);
    app->Run();
    
    delete app;
}
