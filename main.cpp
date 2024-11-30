#include "engine.h"

namespace physics
{
  enum class shape_type { circle };
  struct rigid_body
  {
    shape_type shape;
    union
    { // I need one or the other, but never both
      float radius;
      struct {
        float length;
        float width;
      };
    };
    glm::vec2 position;
  };

  rigid_body rigid_body_circle(float radius, glm::vec2 position_center)
  {
    rigid_body circle;
    circle.shape = shape_type::circle;
    circle.radius = radius;
    circle.position = position_center;

    return circle;
  }
}

int main()
{
  engine::init();

  physics::rigid_body circle = physics::rigid_body_circle(10, glm::vec2(100,100));

  while (!engine::window::should_close())
  {
    engine::window::clear_screen();

    engine::render::triangle::draw(glm::vec2(400, 200), glm::vec2(10, 10), glm::vec3(1,0,0));
    engine::render::circle::draw(circle.position, circle.radius, glm::vec3(0,1,0));

    engine::window::flush();
  }
 
  engine::cleanup();

  return 0;
}
