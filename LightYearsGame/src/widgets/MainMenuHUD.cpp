//
// Created by Ori Sofer on 08/08/2025.
//

#include "widgets/MainMenuHUD.h"

namespace ly
{
    MainMenuHUD::MainMenuHUD() :
    m_TitleText("Light Years"),
    m_ButtonStart("Start"),
    m_ButtonQuit("Quit")
    {
        m_TitleText.SetTextSize(50);
    }

    void MainMenuHUD::Init(const sf::RenderWindow &windowRef)
    {
        sf::Vector2u windowSize = windowRef.getSize();

        // init title
        sf::FloatRect textSize = m_TitleText.GetBounds();
        m_TitleText.SetLocation(sf::Vector2f(windowSize.x / 2.f - textSize.width / 2.f, 100.f));

        //init button start
        sf::FloatRect buttonSize = m_ButtonStart.GetBounds();

        m_ButtonStart.SetLocation(sf::Vector2f((windowSize.x / 2.f) - buttonSize.width / 2.f, 400.f));
        m_ButtonStart.OnClick.BindAction(GetWeakRef(), &MainMenuHUD::OnStartButtonClicked);

        // init button quit
        float buttonHeight = buttonSize.height;
        float padding = 25.f;
        float quitButtonY = m_ButtonStart.GetLocation().y + (buttonSize.height / 2.f) + padding;
        m_ButtonQuit.SetLocation(sf::Vector2f((windowSize.x / 2.f) - buttonSize.width / 2.f, quitButtonY));
        m_ButtonQuit.OnClick.BindAction(GetWeakRef(), &MainMenuHUD::OnQuitButtonClicked);
    }

    void MainMenuHUD::Draw(sf::RenderWindow &windowRef)
    {
        m_TitleText.NativeDraw(windowRef);
        m_ButtonStart.NativeDraw(windowRef);
        m_ButtonQuit.NativeDraw(windowRef);
    }

    bool MainMenuHUD::HandleEvent(const sf::Event &event)
    {
        return m_ButtonStart.HandleEvent(event) && m_ButtonQuit.HandleEvent(event) || HUD::HandleEvent(event);
    }

    void MainMenuHUD::OnStartButtonClicked()
    {
        OnStartClicked.Broadcast();
    }

    void MainMenuHUD::OnQuitButtonClicked()
    {
        OnQuitClicked.Broadcast();
    }
}
