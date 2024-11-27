#ifndef __ENGINE_PHYSICS_ENGINE__
#define __ENGINE_PHYSICS_ENGINE__

#include <glad/glad.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
namespace window
{
  constexpr int width = 640;
  constexpr int height = 480;
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
  void draw(glm::vec2 pos, glm::vec2 size);
}

namespace circle
{
  void init();
  void cleanup();
  void draw(glm::vec2, glm::vec2 size);
}

  void init();
  void cleanup();
}
}

namespace engine
{
  void init();
  void cleanup();
}

#endif // __ENGINE_PHYSICS_ENGINE__