//
// Created by Ori Sofer on 24/03/2025.
//

#ifndef SHOOTER_H
#define SHOOTER_H

namespace ly
{
    class Actor;

    class Shooter
    {
    public:
        void Shoot();
        virtual bool CanShoot() const;
        virtual bool IsOnCooldown() const;
        Actor* GetOwner() const;
        virtual void LevelUp(int amount = 1);
        int GetCurrentLevel() const;
        int GetMaxLevel() const;
        virtual ~Shooter() = default;
    protected:
        Shooter(Actor* owner);
    private:
        virtual void ShootImpl() = 0;
        Actor* m_Owner;
        int m_CurrentLevel;
        int m_MaxLevel;
    };
}

#endif //SHOOTER_H
