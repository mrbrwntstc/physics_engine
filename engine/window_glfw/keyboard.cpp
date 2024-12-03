#include "../../engine.h"

namespace engine
{
namespace window
{
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

  void update()
  {
    update_key(&left, glfwGetKey(engine::window::handle, GLFW_KEY_LEFT));
    update_key(&right, glfwGetKey(engine::window::handle, GLFW_KEY_RIGHT));
    update_key(&up, glfwGetKey(engine::window::handle, GLFW_KEY_UP));
    update_key(&down, glfwGetKey(engine::window::handle, GLFW_KEY_DOWN));
    update_key(&close_window, glfwGetKey(engine::window::handle, GLFW_KEY_ESCAPE));
  }
}
}
}
