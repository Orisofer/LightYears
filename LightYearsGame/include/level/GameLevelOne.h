//
// Created by Ori Sofer on 09/05/2025.
//

#ifndef GAMELEVELONE_H
#define GAMELEVELONE_H

#include "framework/World.h"

namespace ly
{
    class PlayerSpaceship;

    class GameLevelOne : public World
    {
    public:
        GameLevelOne(Application* owningApp);
    private:
        weak<PlayerSpaceship> m_PlayerSpaceship;
    };

}

#endif //GAMELEVELONE_H
