//
// Created by Ori Sofer on 15/03/2025.
//

#ifndef MATHUTILILY_H
#define MATHUTILILY_H

#include <SFML/Graphics.hpp>

namespace ly
{
    sf::Vector2f RotationToVector(float rotation);
    float DegreesToRadians(float degrees);
    float RadiansToDegrees(float radians);

    template <typename T>
    float GetVectorLength(const sf::Vector2<T>& vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    template <typename T>
    sf::Vector2<T>& ScaleVector(sf::Vector2<T>& toScale, float amount)
    {
        toScale.x *= amount;
        toScale.y *= amount;

        return toScale;
    }

    template <typename T>
    sf::Vector2<T>& Normalize(sf::Vector2<T>& toNormalize)
    {
        float length = GetVectorLength<T>(toNormalize);

        if (length == 0.f) return toNormalize;

        toNormalize.x /= length;
        toNormalize.y /= length;

        return toNormalize;
    }

    float LerpFloat(float a, float b, float t);

    sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float t);

    sf::Vector2f LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float t);

    float RandomRange(float min, float max);

    sf::Vector2f RandomUnitVector();
}

#endif //MATHUTILILY_H
