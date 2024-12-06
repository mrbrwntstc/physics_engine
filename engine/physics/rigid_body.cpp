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

  rigid_body rigid_body_quad(float width, float length, glm::vec2 top_left)
  {
    rigid_body quad;
    quad.shape = shape_type::quad;
    quad.width = width;
    quad.length = length;
    quad.position = top_left;

    return quad;
  }
}
}
