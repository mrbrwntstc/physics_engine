#ifndef __ENGINE_PHYSICS_ENGINE__
#define __ENGINE_PHYSICS_ENGINE__

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
namespace window
{
namespace keyboard
{
  extern bool left;
  extern bool right;
  extern bool up;
  extern bool down;
  extern bool close_window;

  void init();
  void update();
}
  constexpr int width = 640;
  constexpr int height = 480;
  extern GLFWwindow* handle;
  void init();
  void cleanup();
  bool should_close();
  void clear_screen(float r = 0, float g = 0, float b = 0, float a = 0);
  void flush();
}
}

namespace engine
{
namespace render
{
namespace shader
{
  extern unsigned int program;
  void init();
  void cleanup();
}

namespace triangle
{
  void init();
  void cleanup();
  void draw(glm::vec2 pos, glm::vec2 size, glm::vec3 color);
}

namespace circle
{
  void init();
  void cleanup();
  void draw(glm::vec2, float radius, glm::vec3 color);
}

namespace quad
{
  void init();
  void cleanup();
  void draw(glm::vec2 top_left, float length, float width, glm::vec3 color);
}

  void init();
  void cleanup();
}
}

namespace engine
{
namespace physics
{
namespace collisions
{
  struct result
  {
    glm::vec2 direction;
    float depth;
    bool collision_occured;
  };

  result circle_circle(glm::vec2 center_other, float radius_other, glm::vec2 center_self, float radius_self);
}
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

  rigid_body rigid_body_circle(float radius, glm::vec2 position_center);
}
}

namespace engine
{
  void init();
  void cleanup();
}

#endif // __ENGINE_PHYSICS_ENGINE__