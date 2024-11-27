#include "../engine.h"

namespace engine
{
  void init()
  {
    window::init();
    render::init();
  }

  void cleanup()
  {
    render::cleanup();
    window::cleanup();
  }
}
