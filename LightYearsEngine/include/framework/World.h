#ifndef World_hpp
#define World_hpp

#include "framework/Core.h"
#include "SFML/Graphics/RenderWindow.hpp"

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
        void Render(sf::RenderWindow& window);
        void CleanCycle();

        template<typename T, typename... Args>
        weak<T> SpawnActor(Args... args);

        virtual ~World();
        sf::Vector2u GetWindowSize() const;
    private:
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        List<shared<Actor>> m_Actors;
        List<shared<Actor>> m_PendingActors;
        Application* m_OwningApp;
        bool m_Playing;
    };

    template<typename T, typename... Args>
    weak<T> World::SpawnActor(Args... args)
    {
        shared<T> newActor{new T {this, args...} };
        m_PendingActors.push_back(newActor);
        return newActor;
    }
}
#endif /* World_hpp */
