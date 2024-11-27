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
  }

  void cleanup()
  {
    circle::cleanup();
    triangle::cleanup();
    shader::cleanup();
  }
}
}