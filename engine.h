#ifndef __ENGINE_PHYSICS_ENGINE__
#define __ENGINE_PHYSICS_ENGINE__

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
  void init()
  {
    window::init();
  }

  void cleanup()
  {
    window::cleanup();
  }
}

#endif // __ENGINE_PHYSICS_ENGINE__