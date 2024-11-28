#include "engine.h"

namespace input
{
  bool left;
  bool right;
  bool up;
  bool down;
}

int main()
{
  engine::init();

  while (!engine::window::should_close())
  {
    engine::window::clear_screen();

    engine::render::triangle::draw(glm::vec2(400, 200), glm::vec2(10, 10), glm::vec3(1,0,0));
    engine::render::circle::draw(glm::vec2(100, 100), glm::vec2(10, 10), glm::vec3(0,1,0));

    engine::window::flush();
  }
 
  engine::cleanup();

  return 0;
}
