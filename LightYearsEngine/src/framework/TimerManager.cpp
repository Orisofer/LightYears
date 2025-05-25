//
// Created by Ori Sofer on 24/05/2025.
//

#include "framework/TimerManager.h"

namespace ly
{

    // ---------------------------------- TIMER HANDLER PART --------------------------------------

    unsigned int TimerHandler::m_TimerKeyCounter = 0;

    unsigned int TimerHandler::GetNextTimerKey()
    {
        return ++m_TimerKeyCounter;
    }

    TimerHandler::TimerHandler() :
    m_TimerKey(GetNextTimerKey())
    {
    }

    unsigned int TimerHandler::GetTimerKey() const
    {
        return m_TimerKey;
    }

    bool operator==(const TimerHandler& lhs, const TimerHandler& rhs)
    {
        return lhs.GetTimerKey() == rhs.GetTimerKey();
    }

    // --------------------------------- TIMER STRUCTURE PART -------------------------------------


    Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat) :
    m_Listener(weakRef, callback),
    m_Duration(duration),
    m_Repeat(repeat),
    m_TimeCounter(0.f),
    m_Expired(false)
    {

    }

    void Timer::TickTime(float deltaTime)
    {
        if (Expired())
        {
            return;
        }

        m_TimeCounter += deltaTime;

        if (m_TimeCounter >= m_Duration)
        {
            m_Listener.second();

            if (m_Repeat)
            {
                m_TimeCounter = 0.f;
            }
            else
            {
                SetExpired();
            }
        }
    }

    bool Timer::Expired() const
    {
        return m_Expired || m_Listener.first.expired() || m_Listener.first.lock()->IsPendingDestroyed();
    }

    void Timer::SetExpired()
    {
        m_Expired = true;
    }

    // --------------------------------------------------------------------------------------------


    unique<TimerManager> TimerManager::s_Instance{nullptr};

    TimerManager::TimerManager() :
    m_Timers()
    {
    }

    TimerManager& TimerManager::Get()
    {
        if (!s_Instance)
        {
            s_Instance = unique<TimerManager>(new TimerManager());
        }

        return *s_Instance;
    }

    void TimerManager::UpdateTimers(float deltaTime)
    {
        for (auto iter = m_Timers.begin(); iter != m_Timers.end();)
        {
            if (iter->second.Expired())
            {
                iter = m_Timers.erase(iter);
            }
            else
            {
                iter->second.TickTime(deltaTime);
                ++iter;
            }
        }
    }

    void TimerManager::ClearTimer(TimerHandler timerHandler)
    {
        auto iter = m_Timers.find(timerHandler);

        if (iter != m_Timers.end())
        {
            iter->second.SetExpired();
        }
    }
}
