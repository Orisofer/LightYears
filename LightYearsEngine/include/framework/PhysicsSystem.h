//
// Created by Ori Sofer on 11/04/2025.
//

#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <box2d/b2_world.h>
#include "Core.h"

namespace ly
{
    class Actor;

    class PhysicsContactListener : public b2ContactListener
    {
        virtual void BeginContact(b2Contact* contact) override;
        virtual void EndContact(b2Contact* contact) override;
    };

    class PhysicsSystem
    {
    public:
        static PhysicsSystem& Get();
        void Step(float deltaTime);
        float GetPhysicsScale() const;
        b2Body* AddListener(Actor* listener);
        void RemoveListener(b2Body* toRemove);

    protected:
        PhysicsSystem();
    private:
        static unique<PhysicsSystem> m_PhysicsSystem;
        b2World m_PhysicsWorld;
        float m_PhysicsScale;
        int m_VelocityIterations;
        int m_PositionIterations;
        PhysicsContactListener m_ContactListener;
    };
}

#endif //PHYSICSSYSTEM_H
