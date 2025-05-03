//
// Created by Ori Sofer on 15/03/2025.
//
#include <__random/random_device.h>

#include "framework/MathUtility.h"

#include <random>

namespace ly
{
    const float PI = 3.14159265358979323846f;

    sf::Vector2f ly::RotationToVector(float rotation)
    {
        float radians = DegreesToRadians(rotation);
        return sf::Vector2f(std::cos(radians), std::sin(radians));
    }

    float DegreesToRadians(float degrees)
    {
        return degrees * PI / 180.0f;
    }

    float RadiansToDegrees(float radians)
    {
        return radians * 180.0f / PI;
    }

    float LerpFloat(float a, float b, float t)
    {
        if (t > 1)
        {
            t = 1;
        }

        if (t < 0)
        {
            t = 0;
        }

        return a + (b - a) * t;
    }

    sf::Color LerpColor(const sf::Color& colA, const sf::Color& colB, float t)
    {
        float r = LerpFloat(colA.r, colB.r, t);
        float g = LerpFloat(colA.g, colB.g, t);
        float b = LerpFloat(colA.b, colB.b, t);
        float a = LerpFloat(colA.a, colB.a, t);

        return sf::Color(r, g, b, a);
    }

    sf::Vector2f LerpVector(const sf::Vector2f &a, const sf::Vector2f &b, float t)
    {
        float x = LerpFloat(a.x, b.x, t);
        float y = LerpFloat(a.y, b.y, t);

        return sf::Vector2f(x, y);
    }

    float RandomRange(float min, float max)
    {
        // boilerplate:
        // this is how to create a random float between two numbers

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> distribution(min, max);

        return distribution(gen);
    }

    sf::Vector2f RandomUnitVector()
    {
        float randomX = RandomRange(-1.0f, 1.0f);
        float randomY = RandomRange(-1.0f, 1.0f);

        sf::Vector2f randomVector = sf::Vector2f(randomX, randomY);

        Normalize(randomVector);

        return randomVector;
    }
}



