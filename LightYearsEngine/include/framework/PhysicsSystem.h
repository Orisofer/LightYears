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

    class PhysicsSystem
    {
    public:
        static PhysicsSystem& Get();
        void Step(float deltaTime);
        b2Body* AddListener(Actor* listener);
        float GetPhysicsScale() const;

        void RemoveListener(b2Body* toRemove);

    protected:
        PhysicsSystem();
    private:
        static unique<PhysicsSystem> m_PhysicsSystem;
        b2World m_PhysicsWorld;
        float m_PhysicsScale;
        int m_VelocityIterations;
        int m_PositionIterations;
    };
}

#endif //PHYSICSSYSTEM_H
