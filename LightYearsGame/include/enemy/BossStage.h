//
// Created by Ori Sofer on 22/08/2025.
//

#ifndef BOSSSTAGE_H
#define BOSSSTAGE_H

#include "gameplay/GameStage.h"

namespace ly
{
    class Actor;

    class BossStage : public GameStage
    {
    public:
        BossStage(World* world);
        virtual void StartStage() override;

    private:
        void BossDestroyed(Actor* actor);
    };

}

#endif //BOSSSTAGE_H
