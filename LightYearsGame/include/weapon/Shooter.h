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
        virtual ~Shooter() = default;
    protected:
        Shooter(Actor* owner);
    private:
        virtual void ShootImpl() = 0;
        Actor* m_Owner;
    };
}

#endif //SHOOTER_H
