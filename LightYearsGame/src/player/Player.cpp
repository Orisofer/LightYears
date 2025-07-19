//
// Created by Ori Sofer on 19/07/2025.
//

#include "player/Player.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    Player::Player() :
    m_LifeCount(3),
    m_Score(0)
    {
    }

    weak<PlayerSpaceship> Player::SpawnSpaceship(World *world)
    {
        if (m_LifeCount > 0)
        {
            m_LifeCount--;

            auto windowSize = world->GetWindowSize();

            m_CurrentSpaceship = world->SpawnActor<PlayerSpaceship>();

            m_CurrentSpaceship.lock()->SetLocation(sf::Vector2f(windowSize.x / 2.f,
                windowSize.y - 100.f));

            m_OnLifeChanged.Broadcast(GetLifeCount());

            return m_CurrentSpaceship;
        }
        else
        {
            m_OnLifeExhausted.Broadcast();
        }
        return weak<PlayerSpaceship>();
    }

    const weak<PlayerSpaceship> Player::GetSpaceship() const
    {
        return m_CurrentSpaceship;
    }

    void Player::AddLifeCount(unsigned int count)
    {
        m_LifeCount += count;

        m_OnLifeChanged.Broadcast(GetLifeCount());
    }

    unsigned int Player::GetLifeCount() const
    {
        return m_LifeCount;
    }

    void Player::AddScore(unsigned int score)
    {
        m_Score += score;

        m_OnScoreChanged.Broadcast(GetScore());
    }

    unsigned int Player::GetScore() const
    {
        return m_Score;
    }
}
