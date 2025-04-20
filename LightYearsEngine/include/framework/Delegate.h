//
// Created by Ori Sofer on 20/04/2025.
//

#ifndef DELEGATE_H
#define DELEGATE_H

#include <functional>

#include "Core.h"

namespace ly
{
    class Object;

    template<typename... Args>
    class Delegate
    {
    public:
        template<typename ClassName>
        void BindAction(weak<Object> obj, void(ClassName::*callback)(Args...))
        {
            // this is one of the ugliest things so far in cpp
            std::function<bool(Args...)> callbackFunc = [obj, callback](Args... args)->bool
            {
                if (!obj.expired())
                {
                    (static_cast<ClassName*>(obj.lock().get())->*callback)(args...);
                    return true;
                }
                return false;
            };

            m_Callbacks.push_back(callbackFunc);
        }

        void Broadcast(Args... args)
        {
            for (auto iter = m_Callbacks.begin() ; iter != m_Callbacks.end();)
            {
                if ((*iter)(args...))
                {
                    ++iter;
                }
                else
                {
                    iter = m_Callbacks.erase(iter);
                }
            }
        }

    private:
        List<std::function<bool(Args...)>> m_Callbacks;
    };
}

#endif //DELEGATE_H
