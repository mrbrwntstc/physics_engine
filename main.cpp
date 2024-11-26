#include "engine.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace render
{
namespace shader
{
  static const char *source_vertex = 
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 model;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * model * vec4(aPos, 0.0, 1.0);\n"
    "}\0";

  static const char *source_fragment = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n\0";
  
  unsigned int program;

  void init()
  {
    int success;
    char info_log[512];

    unsigned int shader_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader_vertex, 1, &source_vertex, nullptr);
    glCompileShader(shader_vertex);
    glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(shader_vertex, 512, nullptr, info_log);
      std::cerr << "vertex shader: " << info_log << std::endl;
    }

    unsigned int shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader_fragment, 1, &source_fragment, nullptr);
    glCompileShader(shader_fragment);
    glGetShaderiv(shader_fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(shader_fragment, 512, nullptr, info_log);
      std::cerr << "fragment shader: " << info_log << std::endl;
    }

    program = glCreateProgram();
    glAttachShader(program, shader_vertex);
    glAttachShader(program, shader_fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
      glGetProgramInfoLog(program, 512, nullptr, info_log);
      std::cerr << "shader program linking: " << info_log << std::endl;
    }

    glDeleteShader(shader_vertex);
    glDeleteShader(shader_fragment);

    // projection matrix - bottom left of screen is (0,0)
    glm::mat4 mat4_projection = glm::ortho(0.0f, static_cast<float>(engine::window::width), 0.0f, static_cast<float>(engine::window::height), -1.f, 1.f);
    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(mat4_projection));
  }
  void cleanup()
  {
    glDeleteProgram(program);
  }
}
}

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
void draw_shape(glm::vec2 pos, glm::vec2 size, unsigned int *vao, int num_vertices)
{
  // matrix transformations
  // ---
  glm::mat4 mat4_model = glm::mat4(1.0);
  mat4_model = glm::translate(mat4_model, glm::vec3(pos, 0.0f));
  mat4_model = glm::scale(mat4_model, glm::vec3(size, 1.0f));
  glUniformMatrix4fv(glGetUniformLocation(render::shader::program, "model"), 1, GL_FALSE, glm::value_ptr(mat4_model));
  // ---

  // render
  glUseProgram(render::shader::program);
  glBindVertexArray(*vao);
  glDrawArrays(primitive_opengl, 0, num_vertices);
}

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
  void draw(glm::vec2 pos, glm::vec2 size)
  {
    draw_shape<GL_TRIANGLES>(pos, size, &vao, 3);
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
  void draw(glm::vec2 pos, glm::vec2 size)
  {
    draw_shape<GL_TRIANGLE_FAN>(pos, size, &vao, num_vertices);
  }
}
}

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

int main()
{
  engine::init();
  render::init();

  while (!engine::window::should_close())
  {
    engine::window::clear_screen();

    // render::triangle::draw(glm::vec2(100, 100), glm::vec2(10, 10));
    render::circle::draw(glm::vec2(100, 100), glm::vec2(10, 10));

    engine::window::flush();
  }
 
  render::cleanup();
  engine::cleanup();

  return 0;
}
