#include "engine.h"

int main()
{
  engine::init();

  while (!engine::window::should_close())
  {
    engine::window::clear_screen();

    engine::window::flush();
  }
 
    engine::cleanup();

  return 0;
}
