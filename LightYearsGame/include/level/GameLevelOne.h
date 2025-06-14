//
// Created by Ori Sofer on 09/05/2025.
//

#ifndef GAMELEVELONE_H
#define GAMELEVELONE_H

#include "framework/TimerManager.h"
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
        virtual void InitGameStages() override;
        weak<PlayerSpaceship> m_PlayerSpaceship;
        TimerHandler m_TimerHandler_Test;
    };

}

#endif //GAMELEVELONE_H
