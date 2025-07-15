//
// Created by Ori Sofer on 15/07/2025.
//

#ifndef REWARD_H
#define REWARD_H

#include <functional>
#include "framework/Actor.h"


namespace ly
{
    class PlayerSpaceship;

    using RewardFunc = std::function<void(PlayerSpaceship*)>;

    class Reward : public Actor
    {
    public:
        Reward(World* owningWorld, const std::string& texturePath, RewardFunc rewardFunc, float speed = 200.f);
        virtual void BeginPlay() override;
        virtual void Tick(float deltaTime) override;
    private:
        virtual void OnActorBeginOverlap(Actor *other) override;
        virtual void OnActorEndOverlap(Actor *other) override;
    private:
        float m_Speed;
        std::function<void(PlayerSpaceship*)> m_RewardFunc; // i know im using "using" but i want to get used to the og syntax
    };
}

#endif //REWARD_H
