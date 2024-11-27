#include "../../engine.h"

namespace engine
{
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
}
