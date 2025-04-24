//
// Created by Ori Sofer on 24/04/2025.
//

#include "framework/MathUtility.h"
#include "framework/World.h"
#include "VFX/Explosion.h"
#include "VFX/Particle.h"

namespace ly
{
    Explosion::Explosion(int particleAmount,
            float lifeTimeMin, float lifeTimeMax,
            float sizeMin, float sizeMax,
            float speedMin, float speedMax, const sf::Color& particleColor)
        : m_ParticleAmount(particleAmount), m_ParticleImagePaths{
            "SpaceShooterRedux/PNG/Effects/star1.png",
            "SpaceShooterRedux/PNG/Effects/star2.png",
            "SpaceShooterRedux/PNG/Effects/star3.png"},
    m_LifeTimeMin(lifeTimeMin),
    m_LifeTimeMax(lifeTimeMax),
    m_SizeMin(sizeMin),
    m_SizeMax(sizeMax),
    m_SpeedMin(speedMin),
    m_SpeedMax(speedMax),
    m_ParticleColor(particleColor)
    {

    }

    void Explosion::SpawnExplosion(World *world, const sf::Vector2f& location)
    {
        if (!world) return;

        for (int i = 0; i < m_ParticleAmount; i++)
        {
            std::string path = m_ParticleImagePaths[(int)RandomRange(0, m_ParticleImagePaths.size())];
            weak<Particle> newParticle = world->SpawnActor<Particle>(path);

            newParticle.lock()->RandomLifetime(m_LifeTimeMin, m_LifeTimeMax);
            newParticle.lock()->SetActorLocation(location);
            newParticle.lock()->RandomVelocity(m_SpeedMin, m_SpeedMax);
            newParticle.lock()->RandomSize(m_SizeMin, m_SizeMax);
            newParticle.lock()->GetSprite().setColor(m_ParticleColor);
        }
    }
}
