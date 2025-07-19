//
// Created by Ori Sofer on 19/07/2025.
//

#include "player/PlayerManager.h"

namespace ly
{
    unique<PlayerManager> PlayerManager::s_Instance{nullptr};

    PlayerManager::PlayerManager() { }

    PlayerManager & PlayerManager::Get()
    {
        if (s_Instance != nullptr)
        {
            return *s_Instance;
        }

        s_Instance = std::move(unique<PlayerManager>{new PlayerManager()});

        return *s_Instance;
    }

    Player& PlayerManager::CreateNewPlayer()
    {
        m_Players.emplace(m_Players.begin(), Player());

        return m_Players.back();
    }

    Player* PlayerManager::GetPlayer(int playerIndex)
    {
        if (playerIndex >= 0 && playerIndex < m_Players.size())
        {
            return &m_Players[playerIndex];
        }
        return nullptr;
    }

    const Player * PlayerManager::GetPlayer(int playerIndex) const
    {
        if (playerIndex >= 0 && playerIndex < m_Players.size())
        {
            return &m_Players[playerIndex];
        }
        return nullptr;
    }
}
