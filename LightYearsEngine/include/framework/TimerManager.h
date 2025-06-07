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
    struct TimerHandler
    {
    public:
        TimerHandler();
        unsigned int GetTimerKey() const;
    private:
        unsigned int m_TimerKey;
        static unsigned int m_TimerKeyCounter;
        static unsigned int GetNextTimerKey();
    };

    // functor - object that is a function (operator () overloaded)
    struct TimerHandlerHashFunction
    {
    public:
        std::size_t operator()(const TimerHandler& timerHandler) const
        {
            return timerHandler.GetTimerKey();
        }
    };

    bool operator==(const TimerHandler& lhs, const TimerHandler& rhs);

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
        TimerHandler SetTimer(weak<Object> weakRef, void(ClassName::*callback)(), float duration, bool repeat = false)
        {
            TimerHandler newHandler{};
            m_Timers.insert({newHandler, Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, duration, repeat)});

            return newHandler;
        }

        void UpdateTimers(float deltaTime);
        void ClearTimer(TimerHandler timerHandler);

    protected:
        TimerManager();
    private:
        static unique<TimerManager> s_Instance;
        Dictionary<TimerHandler, Timer, TimerHandlerHashFunction> m_Timers;
    };
}

#endif //TIMERMANAGER_H
