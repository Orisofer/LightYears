//
// Created by Ori Sofer on 11/04/2025.
//

#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <box2d/b2_world.h>

#include "Core.h"

namespace ly
{
    class PhysicsSystem
    {
    public:
        static PhysicsSystem& Get();
    protected:
        PhysicsSystem();
    private:
        static unique<PhysicsSystem> m_PhysicsSystem;
        b2World m_PhysicsWorld;
        float m_PhysicsScale;
    };
}

#endif //PHYSICSSYSTEM_H
