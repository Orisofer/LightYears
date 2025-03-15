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
}

#endif //MATHUTILILY_H
