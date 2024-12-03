#include "../../engine.h"

namespace engine
{
namespace physics
{
namespace collisions
{
  result circle_circle(glm::vec2 center_other, float radius_other, glm::vec2 center_self, float radius_self)
  {
    result result_collision;

    float distance_centers = glm::distance(center_other, center_self);
    float radii = radius_other + radius_self;

    if(distance_centers >= radii)
      result_collision.collision_occured = false;
    else
    {
      result_collision.collision_occured = true;
      result_collision.direction = glm::normalize(center_self - center_other);
      result_collision.depth = radii - distance_centers;
    }

    return result_collision;
  }
}
}
}
