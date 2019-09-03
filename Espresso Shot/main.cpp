#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <time.h>

#include "Espresso/Camera.h"
#include "Espresso/ShaderProgram.h"
#include "f16.h"

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


	GLFWwindow* window = glfwCreateWindow(800 * 2, 600 * 2, "Espresso Test", NULL, NULL);
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
	//end initialization
	Espresso::Shader lightingShader("Assets/Shaders/lightingShader.vert", "Assets/Shaders/lightingShader.frag");

	std::vector<Espresso::GameObject*> gameObjects;
	gameObjects.push_back(new Espresso::F16(Espresso::Mesh("Assets/Mesh/f16.obj"), lightingShader));

	glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
	};



	glEnable(GL_DEPTH_TEST);


	//render loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(defaultCamera,dt,window);
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto x : gameObjects)
			x->update(dt);

		lightingShader.loadViewMatrix(defaultCamera);
		lightingShader.loadProjectionMatrix(800.0f * 2, 600.0f * 2);
		lightingShader.setInt("material.specular", 1);
		lightingShader.setFloat("material.shininess", 32.0f);

		// directional light
		lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		for (unsigned i = 0; i < 4; i++) {

			lightingShader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
			lightingShader.setVec3("pointLights[" + std::to_string(i) + "].ambient", 0.05f, 0.05f, 0.05f);
			lightingShader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", 0.8f, 0.8f, 0.8f);
			lightingShader.setVec3("pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
			lightingShader.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
			lightingShader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			lightingShader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032);
		}

		glm::vec3 lightColor = glm::vec4(2.0f, 2.0f, 2.0f, 1);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence

		lightingShader.setVec3("light.ambient", ambientColor);
		lightingShader.setVec3("light.diffuse", diffuseColor);
		lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);


		lightingShader.setVec3("viewPos", defaultCamera.getPosition());



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//end of program
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