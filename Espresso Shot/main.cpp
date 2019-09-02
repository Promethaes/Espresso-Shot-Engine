#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <time.h>

#include "Espresso/Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(Espresso::Camera& defaultCamera, float dt, GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

//settings, might change from globals to something else
float lastX = 400, lastY = 300;
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;

Espresso::Camera defaultCamera;

float dt = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
int main() {
	srand(time(0));
	//initialize glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800 * 2, 600 * 2, "Optics simulation", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << "\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << "\n";
		return -1;
	}


	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(defaultCamera,dt,window);
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}


void processInput(Espresso::Camera& defaultCamera, float dt, GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	defaultCamera.move(window, 2.5f * dt);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	defaultCamera.doMouseMovement(xoffset, yoffset);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);

}