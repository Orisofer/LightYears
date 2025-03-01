#ifndef World_hpp
#define World_hpp

#include "framework/Core.h"

namespace ly
{

class Application;
class Actor;

class World
{
    
public:
    
    World(Application* owningApp);
    
    void BeginPlayInternal();
    void TickInternal(float deltaTime);
    
    template<typename T>
    weak<T> SpawnActor();
    
    virtual ~World();
    
private:
    
    virtual void BeginPlay();
    virtual void Tick(float deltaTime);
    
    List<shared<Actor>> m_Actors;
    List<shared<Actor>> m_PendingActors;
    Application* m_OwningApp;
    bool m_Playing;

};

template<typename T>
weak<T> World::SpawnActor()
{
    shared<T> newActor{new T {this} };
    m_PendingActors.push_back(newActor);
    return newActor;
}

}
#endif /* World_hpp */
