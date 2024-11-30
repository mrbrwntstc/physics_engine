#include "engine.h"

int main()
{
  engine::init();

  engine::physics::rigid_body circle = engine::physics::rigid_body_circle(10, glm::vec2(200,50));

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
