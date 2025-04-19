//
// Created by Ori Sofer on 11/04/2025.
//

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>

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
        ProcessPendingRemoveListeners();

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

        b2Body *body = m_PhysicsWorld.CreateBody(&bodyDef);

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

    void PhysicsSystem::RemoveListener(b2Body* toRemove)
    {
        m_PendingRemoveListeners.insert(toRemove);
    }

    PhysicsSystem::PhysicsSystem() :
    m_PhysicsWorld(b2Vec2{0.f,0.f}),
    m_PhysicsScale(.01f),
    m_PositionIterations(8),
    m_VelocityIterations(3),
    m_ContactListener(),
    m_PendingRemoveListeners()
    {
        m_PhysicsWorld.SetContactListener(&m_ContactListener);
        m_PhysicsWorld.SetAllowSleeping(false);
    }

    void PhysicsSystem::ProcessPendingRemoveListeners()
    {
        for (auto listener : m_PendingRemoveListeners)
        {
            m_PhysicsWorld.DestroyBody(listener);
        }

        m_PendingRemoveListeners.clear();
    }

    // this two methods are like colliders in Unity, we provide a listener class
    // that can catch the collision's data. We override these functions to retrieve the collision
    // data
    void PhysicsContactListener::BeginContact(b2Contact *contact)
    {
        Actor* actorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        Actor* actorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        if (actorA && !actorA->IsPendingDestroyed())
        {
            actorA->OnActorBeginOverlap(actorB);
        }

        if (actorB && !actorB->IsPendingDestroyed())
        {
            actorB->OnActorBeginOverlap(actorA);
        }
    }

    void PhysicsContactListener::EndContact(b2Contact *contact)
    {
        Actor* actorA = nullptr;
        Actor* actorB = nullptr;

        if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
        {
            actorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        }

        if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
        {
            actorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        }

        if (actorA && !actorA->IsPendingDestroyed())
        {
            actorA->OnActorEndOverlap(actorB);
        }

        if (actorB && !actorB->IsPendingDestroyed())
        {
            actorB->OnActorEndOverlap(actorA);
        }
    }
}
