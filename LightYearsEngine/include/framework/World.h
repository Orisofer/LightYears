#ifndef World_hpp
#define World_hpp

#include "Object.h"
#include "framework/Core.h"
#include "SFML/Graphics/RenderWindow.hpp"

namespace ly
{
    class Application;
    class Actor;
    class GameStage;

    class World : public Object
    {
    public:
        World(Application* owningApp);
        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        void Render(sf::RenderWindow& window);
        void CleanCycle();
        void AddStage(const shared<GameStage> stage);

        template<typename T, typename... Args>
        weak<T> SpawnActor(Args... args);

        virtual ~World();
        sf::Vector2u GetWindowSize() const;
    private:
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        virtual void InitGameStages();
        virtual void AllGameStagesFinished();
        void NextGameStage();
        List<shared<Actor>> m_Actors;
        List<shared<Actor>> m_PendingActors;
        List<shared<GameStage>> m_GameStages;
        Application* m_OwningApp;
        int m_CurrentStageIndex;
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
