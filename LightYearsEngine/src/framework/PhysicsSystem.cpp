//
// Created by Ori Sofer on 11/04/2025.
//

#include "framework/PhysicsSystem.h"

namespace ly
{
    // because this is a static instance it needs to be initialized to not get a linking error
    // we initializing it with null ptr
    unique<PhysicsSystem> PhysicsSystem::m_PhysicsSystem{nullptr};

    PhysicsSystem& PhysicsSystem::Get()
    {
        if (m_PhysicsSystem == nullptr)
        {
            m_PhysicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem()});
        }

        return *m_PhysicsSystem;
    }

    PhysicsSystem::PhysicsSystem() :
    m_PhysicsWorld(b2Vec2{0.f,0.f}),
    m_PhysicsScale(.01f)
    {
    }
}
