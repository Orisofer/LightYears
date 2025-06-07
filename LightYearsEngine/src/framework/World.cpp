
#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"

namespace ly
{
    World::World(Application* owningApp) :
    m_OwningApp{owningApp},
    m_Playing{false},
    m_Actors(),
    m_PendingActors(),
    m_GameStages(),
    m_CurrentStageIndex(-1)
    {

    }

    void World::BeginPlayInternal()
    {
        if (!m_Playing)
        {
            m_Playing = true;

            BeginPlay();
            InitGameStages();
            NextGameStage();
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

        if (m_CurrentStageIndex >= 0 && m_CurrentStageIndex < m_GameStages.size())
        {
            m_GameStages[m_CurrentStageIndex]->TickStage(deltaTime);
        }

        Tick(deltaTime);
    }

    void World::Render(sf::RenderWindow &window)
    {
        for (shared<Actor>& actor : m_Actors)
        {
            actor->Render(window);
        }

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

        for (auto iter = m_GameStages.begin(); iter != m_GameStages.end();)
        {
            if (iter->get()->IsStageFinished())
            {
                m_GameStages.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
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

    }

    void World::NextGameStage()
    {
        m_CurrentStageIndex++;

        if (m_CurrentStageIndex >= 0 && m_CurrentStageIndex < m_GameStages.size())
        {
            m_GameStages[m_CurrentStageIndex]->OnStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
            m_GameStages[m_CurrentStageIndex]->StartStage();
        }
        else
        {
            AllGameStagesFinished();
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
