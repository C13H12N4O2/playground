#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0";

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

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);
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
  
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
  }
  
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
  }
  
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::Link::Program::LINKING_FAILED\n" << infoLog << "\n";
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  
  glUseProgram(shaderProgram);
  
  float vertices1[] = {
     0.8f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f,
     0.8f,  -0.5f, 0.0f,
  };
  
  float vertices2[] = {
    -0.8f, -0.5f, 0.0f,
     0.0f, -0.5f, 0.0f,
    -0.8f,  0.5f, 0.0f,
  };
  
  unsigned int VBO1, VBO2, VAO1, VAO2;
  
  glGenVertexArrays(1, &VAO1);
  glGenBuffers(1, &VBO1);
  
  glBindVertexArray(VAO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glEnableVertexAttribArray(0);
  
  glGenVertexArrays(1, &VAO2);
  glGenBuffers(1, &VBO2);

  glBindVertexArray(VAO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glEnableVertexAttribArray(0);
  
  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glDeleteVertexArrays(1, &VAO1);
  glDeleteBuffers(1, &VBO1);
  glDeleteVertexArrays(1, &VAO2);
  glDeleteBuffers(1, &VBO2);
  glDeleteProgram(shaderProgram);
  
  glfwTerminate();
  return 0;
}

