//
// Created by Ori Sofer on 07/06/2025.
//

#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
    class World;

    class GameStage : public Object
    {
    public:
        GameStage(World* world);
        const World* GetWorld() const;
        World* GetWorld();

        Delegate<> OnStageFinished;

        virtual void StartStage();
        virtual void TickStage(float deltaTime);
        virtual void FinishStage();

        bool IsStageFinished() const;
    private:
        virtual void StageFinished();
        World* m_World;
        bool m_StageFinished;
    };
}

#endif //GAMESTAGE_H
