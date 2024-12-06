#include "engine.h"

int main()
{
  engine::init();
  // circle-circle collisions
  // ---
  // engine::physics::rigid_body circle = engine::physics::rigid_body_circle(10, glm::vec2(250,50));
  // engine::physics::rigid_body circle2 = engine::physics::rigid_body_circle(10, glm::vec2(600,200));
  // ---
  engine::physics::rigid_body quad = engine::physics::rigid_body_quad(25, 50, glm::vec2(400, 400));

  while (!engine::window::should_close())
  {
    engine::window::keyboard::update();

    int dx = 0;
    int dy = 0;
    float speed = 1.0f;
    if(engine::window::keyboard::left) { dx--; }
    if(engine::window::keyboard::right) { dx++; }
    if(engine::window::keyboard::up) { dy++; }
    if(engine::window::keyboard::down) { dy--; }
    if(engine::window::keyboard::close_window) { glfwSetWindowShouldClose(engine::window::handle, GLFW_TRUE); }

    if(dx != 0 || dy != 0)
    {
      glm::vec2 direction = glm::normalize(glm::vec2(dx, dy));
      glm::vec2 velocity = direction * speed;
      //circle.position += velocity;
      quad.position += velocity;
    }

    // circle-circle collision
    // ---
    // engine::physics::collisions::result result = engine::physics::collisions::circle_circle(circle2.position, circle2.radius, circle.position, circle.radius);
    // if(result.collision_occured)
    // {
      // circle2.position += (-result.direction * result.depth / 2.f);
      // circle.position += (result.direction * result.depth / 2.f);
    // }
    // ---

    engine::window::clear_screen();

    // engine::render::triangle::draw(glm::vec2(400, 200), glm::vec2(10, 10), glm::vec3(1,0,0));
    // engine::render::circle::draw(circle.position, circle.radius, glm::vec3(0,1,0));
    // engine::render::circle::draw(circle2.position, circle2.radius, glm::vec3(1, 1, 0));
    engine::render::quad::draw(quad.position, glm::vec2(quad.length, quad.width), glm::vec3(1, 0, 1));
    engine::window::flush();
  }
 
  engine::cleanup();

  return 0;
}
