//
// Created by Ori Sofer on 24/04/2025.
//

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    class World;

    class Explosion
    {
    public:
        Explosion(int particleAmount = 20,
            float lifeTimeMin = .5f, float lifeTimeMax = 1.0f,
            float sizeMin = 1.f, float sizeMax = 2.f,
            float speedMin = 200.f, float speedMax = 400.f,
            const sf::Color& particleColor = sf::Color{255,128,0,255});

        void SpawnExplosion(World* world, const sf::Vector2f& location);

    private:
        List<std::string> m_ParticleImagePaths;
        sf::Color m_ParticleColor;
        int m_ParticleAmount;
        float m_LifeTimeMin;
        float m_LifeTimeMax;
        float m_SizeMax;
        float m_SizeMin;
        float m_SpeedMax;
        float m_SpeedMin;
    };
}
#endif //EXPLOSION_H
