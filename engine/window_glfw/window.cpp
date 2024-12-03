#include "../../engine.h"

namespace callbacks_glfw
{
  static void error(int error, const char* description)
  {
    fprintf(stderr, "Error: %s\n", description);
  }

  static void framebuffer_size(GLFWwindow* window, int width, int height)
  {
    glViewport(0, 0, width, height);
  }
}

namespace engine
{
namespace window
{
  GLFWwindow *handle;

  void init()
  {
    glfwSetErrorCallback(callbacks_glfw::error);
  
    if (!glfwInit())
      exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  #endif

    handle = glfwCreateWindow(640, 480, "Physics Engine", NULL, NULL);
    if (!handle)
    {
      glfwTerminate();
      exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(handle);
    glfwSetFramebufferSizeCallback(handle, callbacks_glfw::framebuffer_size);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);
  
    keyboard::init();
  }

  void cleanup()
  {
    glfwDestroyWindow(handle);
    glfwTerminate();
  }

  bool should_close()
  {
    return glfwWindowShouldClose(handle);
  }

  void clear_screen(float r, float g, float b, float a)
  {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void flush()
  {
    glfwSwapBuffers(handle);
    glfwPollEvents();
  }

}
}