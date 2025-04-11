//
// Created by Ori Sofer on 11/04/2025.
//

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

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

    void PhysicsSystem::Step(float deltaTime)
    {
        m_PhysicsWorld.Step(deltaTime, m_VelocityIterations, m_PositionIterations);
    }

    b2Body * PhysicsSystem::AddListener(Actor *listener)
    {
        if (listener->IsPendingDestroyed()) return nullptr;

        b2BodyDef bodyDef;

        bodyDef.type = b2_dynamicBody;

        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);

        float listenerPosX = listener->GetLocation().x;
        float listenerPosY = listener->GetLocation().y;

        bodyDef.position.Set(listenerPosX * GetPhysicsScale(), listenerPosY * GetPhysicsScale());

        float listenerAngle = DegreesToRadians(listener->GetRotation());

        bodyDef.angle = listenerAngle;

        b2Body* body = m_PhysicsWorld.CreateBody(&bodyDef);

        b2PolygonShape shape;

        float listenerBoundsWidth = listener->GetActorGlobalBounds().width;
        float listenerBoundsHeight = listener->GetActorGlobalBounds().height;

        shape.SetAsBox(listenerBoundsWidth * .5f * GetPhysicsScale(), listenerBoundsHeight * .5f * GetPhysicsScale());

        b2FixtureDef fixtureDef;

        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.isSensor = true;

        body->CreateFixture(&fixtureDef);

        return body;
    }

    float PhysicsSystem::GetPhysicsScale() const
    {
        return m_PhysicsScale;
    }

    PhysicsSystem::PhysicsSystem() :
    m_PhysicsWorld(b2Vec2{0.f,0.f}),
    m_PhysicsScale(.01f),
    m_PositionIterations(8),
    m_VelocityIterations(3)
    {
    }
}
