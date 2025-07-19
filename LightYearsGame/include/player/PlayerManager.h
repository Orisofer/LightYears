//
// Created by Ori Sofer on 19/07/2025.
//

#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "framework/Core.h"
#include "player/Player.h"

namespace ly
{
    // singleton T_T
    class PlayerManager
    {
    public:
        static PlayerManager& Get();
        Player& CreateNewPlayer();
        Player* GetPlayer(int playerIndex = 0);
        const Player* GetPlayer(int playerIndex = 0) const;

    protected:
        PlayerManager();

    private:
        static unique<PlayerManager> s_Instance;
        List<Player> m_Players;
    };
}

#endif //PLAYERMANAGER_H
