//
// Created by Ori Sofer on 08/07/2025.
//

#ifndef WAITSTAGE_H
#define WAITSTAGE_H

#include "GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
    class WaitStage : public GameStage
    {
    public:
        WaitStage(World* world, float waitTime = 5.f);
        virtual void StartStage() override;
    private:
        TimerHandler m_WaitTimeHandler;
        float m_WaitTime;
    };
}

#endif //WAITSTAGE_H
