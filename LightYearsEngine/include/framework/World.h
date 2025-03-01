#ifndef World_hpp
#define World_hpp

namespace ly
{

class Application;

class World
{
    
public:
    
    World(Application* owningApp);
    
    void BeginPlayInternal();
    void TickInternal(float deltaTime);
    
    virtual ~World();
    
private:
    
    virtual void BeginPlay();
    virtual void Tick(float deltaTime);
    
    Application* m_OwningApp;
    bool m_Playing;
};

}
#endif /* World_hpp */
