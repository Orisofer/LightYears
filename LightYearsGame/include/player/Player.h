//
// Created by Ori Sofer on 19/07/2025.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerSpaceship.h"
#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
    class PlayerSpaceship;

    class Player : public Object
    {
    public:
        Player();
        weak<PlayerSpaceship> SpawnSpaceship(World* world);
        const weak<PlayerSpaceship> GetSpaceship() const;

        void AddLifeCount(unsigned int count);
        void RemoveLifeCount(unsigned int count);
        unsigned int GetLifeCount() const;

        void AddScore(unsigned int score);
        unsigned int GetScore() const;

        Delegate<int> m_OnLifeChanged;
        Delegate<unsigned int> m_OnScoreChanged;
        Delegate<> m_OnLifeExhausted;

    private:
        weak<PlayerSpaceship> m_CurrentSpaceship;
        unsigned int m_LifeCount;
        unsigned int m_MaxLife;
        unsigned int m_Score;
    };
}

#endif //PLAYER_H
