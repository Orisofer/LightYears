//
// Created by Ori Sofer on 15/03/2025.
//

#ifndef MATHUTILILY_H
#define MATHUTILILY_H
#include "SFML/Graphics.hpp"

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
}

#endif //MATHUTILILY_H
