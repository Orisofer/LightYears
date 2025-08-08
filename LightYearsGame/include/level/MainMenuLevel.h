//
// Created by Ori Sofer on 08/08/2025.
//

#ifndef MAINMENULEVEL_H
#define MAINMENULEVEL_H

#include "framework/World.h"

namespace ly
{
    class MainMenuHUD;

    class MainMenuLevel : public World
    {
    public:
        MainMenuLevel(Application* owningApp);

    private:
        virtual void BeginPlay() override;
        void StartGame();
        void EndGame();
        weak<MainMenuHUD> m_MainMenuHUD;
    };
}

#endif //MAINMENULEVEL_H
