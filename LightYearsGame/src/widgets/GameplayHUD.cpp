//
// Created by Ori Sofer on 26/07/2025.
//

#include "widgets/GameplayHUD.h"
#include "player/PlayerManager.h"
#include "player/Player.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    GameplayHUD::GameplayHUD() :
    m_FpsCounter("Frame rate:"),
    m_HealthBar(),
    m_PlayerLiveIcon("/SpaceShooterRedux/PNG/playerShip1_blue.png")
    {

    }

    void GameplayHUD::Init(const sf::RenderWindow &windowRef)
    {
        // init health bar graphics
        float healthBarPosX = 10.f;
        float healthBarPadding = 15.f;
        float halfBarYSize = m_HealthBar.GetBarSize().y / 2.f;

        float healthBarPosY = windowRef.getSize().y - halfBarYSize - healthBarPadding;
        m_HealthBar.SetLocation(sf::Vector2f(healthBarPosX, healthBarPosY));

        RefreshHealthBar();

        // init player Lives Icon
        float healthIconPadding = 10.f;
        float healthIconPosX = healthBarPosX + m_HealthBar.GetBarSize().x + healthIconPadding;
        m_PlayerLiveIcon.SetLocation(sf::Vector2f(healthIconPosX, healthBarPosY - 2));
        m_PlayerLiveIcon.SetSizeMultiplier(.25f);
    }

    void GameplayHUD::Draw(sf::RenderWindow &windowRef)
    {
        m_FpsCounter.NativeDraw(windowRef);
        m_HealthBar.NativeDraw(windowRef);
        m_PlayerLiveIcon.NativeDraw(windowRef);
    }

    void GameplayHUD::Tick(float deltaTime)
    {
        HUD::Tick(deltaTime);

        int frameRate = int(1 / deltaTime);
        std::string frameRateString = "Frame Rate: " + std::to_string(frameRate);
        m_FpsCounter.SetText(frameRateString);
    }

    void GameplayHUD::OnPlayerHealthUpdated(float amt, float health, float maxHealth)
    {
        m_HealthBar.UpdateValue(health, maxHealth);
    }

    void GameplayHUD::OnPlayerSpaceshipDestroyed(Actor* spaceship)
    {
        RefreshHealthBar();
    }

    void GameplayHUD::RefreshHealthBar()
    {
        // init health bar logic
        Player* player = PlayerManager::Get().GetPlayer();

        if (player != nullptr && !player->GetSpaceship().expired())
        {
            weak<PlayerSpaceship> playerSpaceship = player->GetSpaceship();

            playerSpaceship.lock()->ActorDestroyed.BindAction(GetWeakRef(), &GameplayHUD::OnPlayerSpaceshipDestroyed);

            HealthComponent& healthComponent = player->GetSpaceship().lock()->GetHealthComponent();
            healthComponent.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::OnPlayerHealthUpdated);

            m_HealthBar.UpdateValue(healthComponent.GetHealth(), healthComponent.GetMaxHealth());
        }
    }
}
