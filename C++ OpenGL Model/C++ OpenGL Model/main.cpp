#include "Shader.h"
#include "camera.h"
#include "mesh.hpp"
#include "model.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;

int main(int argc, const char* argv[]) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, argv[0], NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }
  
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }
  
  glEnable(GL_DEPTH_TEST);
  
  const char* path = "./backpack.obj";
  Model ourModel(path);
  Shader backpackShader("backpack_shader.vs", "backpack_shader.fs");
  
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    processInput(window);
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    backpackShader.use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    backpackShader.setMat4("projection", projection);
    backpackShader.setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));  // it's a bit too big for our scene, so scale it down
    backpackShader.setMat4("model", model);
    
    ourModel.Draw(backpackShader);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.ProcessKeyboard(FORWARD, deltaTime);
  }
  
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  }
  
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.ProcessKeyboard(LEFT, deltaTime);
  }
  
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.ProcessKeyboard(RIGHT, deltaTime);
  }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(const char* path) {
  unsigned int ID;
  glGenTextures(1, &ID);
  
  int width, height, nrComponents;
  unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
  
  if (!data) {
    std::cout << "Texture failed to load at " << path << "\n";
    stbi_image_free(data);
    return ID;
  }
  
  GLenum format;
  switch (nrComponents) {
    case 1:
      format = GL_RED;
      break;
    case 3:
      format = GL_RGB;
      break;
    case 4:
      format = GL_RGBA;
      break;
    default:
      format = GL_RED;
      break;
  }
  
  glBindTexture(GL_TEXTURE_2D, ID);
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  stbi_image_free(data);
  
  return ID;
}
