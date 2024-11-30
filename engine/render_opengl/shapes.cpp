#include "../../engine.h"

static void init_state(unsigned int* vao, unsigned int* vbo, float* vertices, int len_vertices)
{
  glGenVertexArrays(1, vao);
  glGenBuffers(1, vbo);

  glBindVertexArray(*vao);

  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) *  len_vertices, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
  glEnableVertexAttribArray(0);
}

template <GLenum primitive_opengl>
void draw_shape(glm::vec2 pos, glm::vec2 size, glm::vec3 color, unsigned int *vao, int num_vertices)
{
  // matrix transformations
  // ---
  glm::mat4 mat4_model = glm::mat4(1.0);
  mat4_model = glm::translate(mat4_model, glm::vec3(pos, 0.0f));
  mat4_model = glm::scale(mat4_model, glm::vec3(size, 1.0f));
  glUniformMatrix4fv(glGetUniformLocation(engine::render::shader::program, "model"), 1, GL_FALSE, glm::value_ptr(mat4_model));
  // ---

  // color
  // ---
  glUniform3fv(glGetUniformLocation(engine::render::shader::program, "color"), 1, glm::value_ptr(color));
  // ---

  // render
  glUseProgram(engine::render::shader::program);
  glBindVertexArray(*vao);
  glDrawArrays(primitive_opengl, 0, num_vertices);
}

namespace engine
{
namespace render
{
namespace triangle
{
  unsigned int vao;
  unsigned int vbo;
  void init()
  { // triangle
    float vertices[] = 
    {
      0.0f, 0.0f,
      0.5f, 1.0f,
      1.0f, 0.0f
    };

    init_state(&vao, &vbo, vertices, 6);
  }
  void cleanup()
  {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
  }
  void draw(glm::vec2 pos, glm::vec2 size, glm::vec3 color)
  {
    draw_shape<GL_TRIANGLES>(pos, size, color, &vao, 3);
  }
}

namespace circle
{
  unsigned int vao;
  unsigned int vbo;
  constexpr int num_vertices = 100;
  int len_vertices = num_vertices * 2; // 100 (x,y) coordinates
  void init()
  {
    float vertices[len_vertices];
    float theta = 2 * 3.141592f / static_cast<float>(num_vertices);
    float cos_theta = cosf(theta);
    float sin_theta = sinf(theta);
    float x_old;

    float x = 1;
    float y = 0;
    for(int i = 0; i < num_vertices; ++i)
    {
      vertices[2*i] = x;
      vertices[2*i + 1] = y;

      // apply rotation matrix
      x_old = x;
      x = cos_theta * x - sin_theta * y;
      y = sin_theta * x_old + cos_theta * y;
    }

    init_state(&vao, &vbo, vertices, len_vertices);
  }
  void cleanup()
  {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
  }
  void draw(glm::vec2 pos, float radius, glm::vec3 color)
  {
    draw_shape<GL_TRIANGLE_FAN>(pos, glm::vec2(radius, radius), color, &vao, num_vertices);
  }
}
}
}
