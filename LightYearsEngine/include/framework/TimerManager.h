//
// Created by Ori Sofer on 24/05/2025.
//

#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <functional>

#include "Object.h"
#include "framework/Core.h"

namespace ly
{
    struct Timer
    {
    public:
        Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat);
        void TickTime(float deltaTime);
        bool Expired() const;
        void SetExpired();
    private:
        std::pair<weak<Object>, std::function<void()>> m_Listener;
        float m_Duration;
        float m_TimeCounter;
        bool m_Repeat;
        bool m_Expired;
    };
    class TimerManager
    {
    public:
        static TimerManager& Get();

        template<typename ClassName>
        void SetTimer(weak<Object> weakRef, void(ClassName::*callback)(), float duration, bool repeat = false)
        {
            m_Timers.push_back(Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, duration, repeat));

        }

        void UpdateTimers(float deltaTime);

    protected:
        TimerManager();
    private:
        static unique<TimerManager> s_Instance;
        List<Timer> m_Timers;
    };
}

#endif //TIMERMANAGER_H
