
#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"
#include "widgets/HUD.h"

namespace ly
{
    World::World(Application* owningApp) :
    m_OwningApp{owningApp},
    m_Playing{false},
    m_Actors(),
    m_PendingActors(),
    m_GameStages(),
    m_CurrentGameStage(m_GameStages.end())
    {

    }

    void World::BeginPlayInternal()
    {
        if (!m_Playing)
        {
            m_Playing = true;

            BeginPlay();
            InitGameStages();
            StartStages();
        }
    }

    void World::TickInternal(float deltaTime)
    {
        for (shared<Actor> actor : m_PendingActors)
        {
            m_Actors.push_back(actor);

            actor->BeginPlayInternal();
        }

        m_PendingActors.clear();

        for (auto iter = m_Actors.begin(); iter != m_Actors.end();)
        {
            iter->get()->TickInternal(deltaTime);
            ++iter;
        }

        if (m_CurrentGameStage != m_GameStages.end())
        {
            m_CurrentGameStage->get()->TickStage(deltaTime);
        }

        Tick(deltaTime);

        // tick HUD
        if (m_HUD != nullptr)
        {
            if (!m_HUD->HasInit())
            {
                m_HUD->NativeInit(m_OwningApp->GetWindow());
            }

            m_HUD->Tick(deltaTime);
        }
    }

    void World::Render(sf::RenderWindow &window)
    {
        for (shared<Actor>& actor : m_Actors)
        {
            actor->Render(window);
        }

        // we render the hud after we render the actors so all the hud
        // will be in front
        RenderHud(window);
    }

    void World::CleanCycle()
    {
        for (auto iter = m_Actors.begin(); iter != m_Actors.end();)
        {
            if (iter->get()->IsPendingDestroyed())
            {
                iter = m_Actors.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    bool World::DispatchEvent(const sf::Event& event)
    {
        if (m_HUD)
        {
            return m_HUD->HandleEvent(event);
        }
        return false;
    }

    void World::AddStage(const shared<GameStage> stage)
    {
        if (stage != nullptr)
        {
            m_GameStages.push_back(stage);
        }
    }

    void World::BeginPlay()
    {
        LOG("World Begin");
    }

    void World::Tick(float deltaTime)
    {
        //LOG("Ticking at framerate %f", 1.0f / deltaTime);
    }

    void World::InitGameStages()
    {
        // no-op
    }

    void World::AllGameStagesFinished()
    {
        LOG("World : All Game Stages Finished");
    }

    void World::RenderHud(sf::RenderWindow& window)
    {
        if (m_HUD)
        {
            m_HUD->Draw(window);
        }
    }

    void World::NextGameStage()
    {
        m_CurrentGameStage = m_GameStages.erase(m_CurrentGameStage);

        if (m_CurrentGameStage != m_GameStages.end())
        {
            m_CurrentGameStage->get()->StartStage();
            m_CurrentGameStage->get()->OnStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
        }
        else
        {
            AllGameStagesFinished();
        }
    }

    void World::StartStages()
    {
        if (!m_GameStages.empty())
        {
            m_CurrentGameStage = m_GameStages.begin();
            m_CurrentGameStage->get()->StartStage();
            m_CurrentGameStage->get()->OnStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
        }
    }

    World::~World()
    {

    }

    sf::Vector2u World::GetWindowSize() const
    {
        return m_OwningApp->GetWindowSize();
    }
}
