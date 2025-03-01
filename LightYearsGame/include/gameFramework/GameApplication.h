#pragma once

#include <framework/Application.h>
#include "framework/Core.h"

namespace ly
{

class Actor;

class GameApplication : public Application
{
public:
    
    GameApplication();
    GameApplication(float width, float height);
    
    virtual void Tick(float deltaTime) override;
    
private:
    
    float m_Counter;
    weak<Actor> m_ActorToDestroy;
    
};

}
