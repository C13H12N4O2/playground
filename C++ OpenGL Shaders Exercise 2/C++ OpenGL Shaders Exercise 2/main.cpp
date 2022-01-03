#include "Shader.h"
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

int main(int argc, const char* argv[]) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  GLFWwindow* window = glfwCreateWindow(800, 600, argv[0], NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }
  
  glfwMakeContextCurrent(window);
  
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }
  
  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  Shader ourShader("shader.vs", "shader.fs");
  
  float vertices[] = {
      0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
      0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
  };
  
  unsigned int VBO, VAO;
  
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  float offset = 0.5f;
  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    ourShader.setFloat("x", offset);
    
    ourShader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwTerminate();
  return 0;
}
