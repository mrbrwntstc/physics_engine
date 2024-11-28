#include "../engine.h"

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
  static GLFWwindow *ptr_window;

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

    ptr_window = glfwCreateWindow(640, 480, "Physics Engine", NULL, NULL);
    if (!ptr_window)
    {
      glfwTerminate();
      exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(ptr_window);
    glfwSetFramebufferSizeCallback(ptr_window, callbacks_glfw::framebuffer_size);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);
  }

  void cleanup()
  {
    glfwDestroyWindow(ptr_window);
    glfwTerminate();
  }

  bool should_close()
  {
    return glfwWindowShouldClose(ptr_window);
  }

  void clear_screen(float r, float g, float b, float a)
  {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void flush()
  {
    glfwSwapBuffers(ptr_window);
    glfwPollEvents();
  }

}
}