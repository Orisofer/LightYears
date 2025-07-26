//
// Created by Ori Sofer on 26/07/2025.
//

#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "framework/Object.h"

namespace ly
{
    class HUD : public Object
    {
    public:
        virtual void Draw(sf::RenderWindow& windowRef) = 0;
        virtual void NativeInit(sf::RenderWindow& windowRef);
        bool HasInit();
        virtual bool HandleEvent(const sf::Event& event);

    protected:
        HUD();

    private:
        virtual void Init(sf::RenderWindow& windowRef);

        bool m_HasInit;
    };

}

#endif //HUD_H
