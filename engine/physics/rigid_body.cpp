#include "../../engine.h"

namespace engine
{
namespace physics
{
  rigid_body rigid_body_circle(float radius, glm::vec2 position_center)
  {
    rigid_body circle;
    circle.shape = shape_type::circle;
    circle.radius = radius;
    circle.position = position_center;

    return circle;
  }
}
}
