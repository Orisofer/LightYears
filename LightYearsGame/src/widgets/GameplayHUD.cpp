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
    m_LifeCounter("X"),
    m_ScoreCounter("no-score"),
    m_HealthBar(),
    m_PlayerLiveIcon("/SpaceShooterRedux/PNG/playerShip1_blue.png"),
    m_PlayerScoreIcon("/SpaceShooterRedux/PNG/Power-ups/star_gold.png")
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

        // init life counter text
        float lifeCounterPadding = 25.f;
        float LifeCounterPosX = healthIconPosX + m_LifeCounter.GetBounds().width + lifeCounterPadding;
        m_LifeCounter.SetLocation(sf::Vector2f(LifeCounterPosX, healthBarPosY - 7));
        m_LifeCounter.SetTextSize(20);

        // init score icon
        float scoreIconPadding = 10.f;
        float scoreIconPosX = LifeCounterPosX + m_LifeCounter.GetBounds().width + scoreIconPadding;
        m_PlayerScoreIcon.SetLocation(sf::Vector2f(scoreIconPosX, healthBarPosY));
        m_PlayerScoreIcon.SetSizeMultiplier(.5f);

        // init score counter
        float scoreCounterPaddingX = 10.f;
        float scoreCounterPosX = scoreIconPosX + m_PlayerScoreIcon.GetBounds().width + scoreCounterPaddingX;
        m_ScoreCounter.SetLocation(sf::Vector2f(scoreCounterPosX, healthBarPosY - 7));
        m_ScoreCounter.SetTextSize(20);

        RegisterPlayerData();
    }

    void GameplayHUD::Draw(sf::RenderWindow &windowRef)
    {
        m_FpsCounter.NativeDraw(windowRef);
        m_HealthBar.NativeDraw(windowRef);
        m_PlayerLiveIcon.NativeDraw(windowRef);
        m_LifeCounter.NativeDraw(windowRef);
        m_PlayerScoreIcon.NativeDraw(windowRef);
        m_ScoreCounter.NativeDraw(windowRef);
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
        RegisterPlayerData();
        RefreshHealthBar();
    }

    void GameplayHUD::OnPlayerScoreChanged(unsigned int score)
    {
        RefreshPlayerScore(score);
    }

    void GameplayHUD::OnPlayerLifeChanged(int life)
    {
        RefreshPlayerLives(life);
    }

    void GameplayHUD::OnPlayerLifeExhausted()
    {
        m_LifeCounter.SetText("-");
    }

    void GameplayHUD::RefreshPlayerScore(unsigned int score)
    {
        m_ScoreCounter.SetText(std::to_string(score));
    }

    void GameplayHUD::RefreshPlayerLives(int lives)
    {
        m_LifeCounter.SetText(std::to_string(lives));
    }

    void GameplayHUD::RegisterPlayerData()
    {
        Player* player = PlayerManager::Get().GetPlayer();

        if (player != nullptr && !player->GetSpaceship().expired())
        {
            player->m_OnLifeExhausted.BindAction(GetWeakRef(), &GameplayHUD::OnPlayerLifeExhausted);
            player->m_OnScoreChanged.BindAction(GetWeakRef(), &GameplayHUD::OnPlayerScoreChanged);
            player->m_OnLifeChanged.BindAction(GetWeakRef(), &GameplayHUD::OnPlayerLifeChanged);

            int lifeCount = player->GetLifeCount();

            RefreshPlayerLives(lifeCount);
        }
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
