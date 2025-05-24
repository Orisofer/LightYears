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
        virtual void BeginPlay() override;
        void TimerCallback_Test();
        weak<PlayerSpaceship> m_PlayerSpaceship;
        unsigned int m_TimerIndex_Test;
    };

}

#endif //GAMELEVELONE_H
