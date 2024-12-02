#include "engine.h"

namespace keyboard
{
  bool left;
  bool right;
  bool up;
  bool down;
  bool close_window;

  void init()
  {
    glfwSetInputMode(engine::window::handle, GLFW_STICKY_KEYS, GLFW_TRUE);
  }

  static inline void update_key(bool *key, int state_key) { *key = state_key == GLFW_PRESS || state_key == GLFW_REPEAT; }

  void update_keys()
  {
    update_key(&left, glfwGetKey(engine::window::handle, GLFW_KEY_LEFT));
    update_key(&right, glfwGetKey(engine::window::handle, GLFW_KEY_RIGHT));
    update_key(&up, glfwGetKey(engine::window::handle, GLFW_KEY_UP));
    update_key(&down, glfwGetKey(engine::window::handle, GLFW_KEY_DOWN));
    update_key(&close_window, glfwGetKey(engine::window::handle, GLFW_KEY_ESCAPE));
  }
}

int main()
{
  engine::init();
  keyboard::init();
  engine::physics::rigid_body circle = engine::physics::rigid_body_circle(10, glm::vec2(200,50));

  while (!engine::window::should_close())
  {
    keyboard::update_keys();

    int dx = 0;
    int dy = 0;
    float speed = 1.0f;
    if(keyboard::left) { dx--; }
    if(keyboard::right) { dx++; }
    if(keyboard::up) { dy++; }
    if(keyboard::down) { dy--; }
    if(keyboard::close_window) { glfwSetWindowShouldClose(engine::window::handle, GLFW_TRUE); }

    if(dx != 0 || dy != 0)
    {
      glm::vec2 direction = glm::normalize(glm::vec2(dx, dy));
      glm::vec2 velocity = direction * speed;
      circle.position += velocity;
    }

    engine::window::clear_screen();

    engine::render::triangle::draw(glm::vec2(400, 200), glm::vec2(10, 10), glm::vec3(1,0,0));
    engine::render::circle::draw(circle.position, circle.radius, glm::vec3(0,1,0));

    engine::window::flush();
  }
 
  engine::cleanup();

  return 0;
}
