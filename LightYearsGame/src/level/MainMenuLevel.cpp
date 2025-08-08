//
// Created by Ori Sofer on 08/08/2025.
//

#include "level/MainMenuLevel.h"
#include "widgets/MainMenuHUD.h"
#include "framework/Application.h"
#include "level/GameLevelOne.h"

namespace ly
{
    MainMenuLevel::MainMenuLevel(Application *owningApp) :
    World(owningApp)
    {
        m_MainMenuHUD = SpawnHUD<MainMenuHUD>();
    }

    void MainMenuLevel::BeginPlay()
    {
        m_MainMenuHUD.lock()->OnStartClicked.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
        m_MainMenuHUD.lock()->OnQuitClicked.BindAction(GetWeakRef(), &MainMenuLevel::EndGame);
    }

    void MainMenuLevel::StartGame()
    {
        GetApplication()->LoadWorld<GameLevelOne>();
    }

    void MainMenuLevel::EndGame()
    {
        GetApplication()->QuitApplication();
    }
}
