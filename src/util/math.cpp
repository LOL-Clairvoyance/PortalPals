/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 16:50:58
 */

#include "math.hpp"

namespace math
{
    float Lerp(float a, float b, float t)
    {
         return a * (1.0 - t) + (b * t);
    }
}
