#include "../../engine.h"

namespace engine
{
namespace render
{
  void init()
  {
    shader::init();
    triangle::init();
    circle::init();
    quad::init();
  }

  void cleanup()
  {
    quad::cleanup();
    circle::cleanup();
    triangle::cleanup();
    shader::cleanup();
  }
}
}