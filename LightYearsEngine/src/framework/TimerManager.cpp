//
// Created by Ori Sofer on 24/05/2025.
//

#include "framework/TimerManager.h"

namespace ly
{

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
        for (Timer& timer : m_Timers)
        {
            timer.TickTime(deltaTime);
        }
    }
}
