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
    class HUD;

    class World : public Object
    {
    public:
        World(Application* owningApp);
        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        void Render(sf::RenderWindow& window);
        void CleanCycle();
        void AddStage(const shared<GameStage> stage);
        bool DispatchEvent(const sf::Event& event);

        template<typename T, typename... Args>
        weak<T> SpawnActor(Args... args);

        template<typename HudType, typename... Args>
        weak<HUD> SpawnHUD(Args... args);

        virtual ~World();
        sf::Vector2u GetWindowSize() const;
    private:
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        virtual void InitGameStages();
        virtual void AllGameStagesFinished();
        virtual void RenderHud(sf::RenderWindow& window);
        void NextGameStage();
        void StartStages();
        List<shared<Actor>> m_Actors;
        List<shared<Actor>> m_PendingActors;
        List<shared<GameStage>> m_GameStages;
        List<shared<GameStage>>::iterator m_CurrentGameStage;
        shared<HUD> m_HUD;
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

    template<typename HudType, typename... Args>
    weak<HUD> World::SpawnHUD(Args... args)
    {
        shared<HudType> newHud{new HudType(args...)};
        m_HUD = newHud;
        return newHud;
    }
}
#endif /* World_hpp */
