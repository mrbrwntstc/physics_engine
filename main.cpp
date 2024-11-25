#include "engine.h"

#include <glad/glad.h>

#include <iostream>

namespace render
{
namespace shader
{
  static const char *source_vertex = 
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 0.0, 1.0);\n"
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
  }
  void cleanup()
  {
    glDeleteProgram(program);
  }
}
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
      -1.0f, -1.0f,
       0.0f,  1.0f,
       1.0f, -1.0f
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
  }
  void cleanup()
  {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
  }
}
}

namespace render
{
  void init()
  {
    shader::init();
    triangle::init();
  }

  void cleanup()
  {
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

    glUseProgram(render::shader::program);
    glBindVertexArray(render::triangle::vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    engine::window::flush();
  }
 
  render::cleanup();
  engine::cleanup();

  return 0;
}
