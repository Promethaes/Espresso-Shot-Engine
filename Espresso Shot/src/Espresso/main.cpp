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
#include "Espresso/XinputManager.h"
#include "Espresso/Scene Manager.h"
#include "Espresso/Test Scene.h"
#include "Espresso/f16.h"

#define _CRT_SECURE_NO_WARNINGS
#define Scenes Espresso::Scene::scenes
#define GameObjects Espresso::GameObject::gameObjects

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(Espresso::Camera& defaultCamera, float dt, GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

//settings, might change from globals to something else
float lastX = 400, lastY = 300;
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;

Espresso::Camera* defaultCamera = new Espresso::Camera();

float dt = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
int main() {
	srand(time(0));

	//initialize glfw
#pragma region InitialzeGLFW
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
#pragma endregion



	Espresso::Shader lightingShader(std::string(std::getenv("EspressoShotPath")) + "Assets/Shaders/lightingShader.vert", std::string(std::getenv("EspressoShotPath")) + "Assets/Shaders/lightingShader.frag");

	Sedna::XinputManager* manager = new Sedna::XinputManager();
	Sedna::XinputController* controller = manager->getController(0);

	bool f16Test = true;
	bool sceneTest = true;

	if (f16Test == true)
		sceneTest = true;

	if (f16Test)
		Espresso::F16 f16(Espresso::Mesh(std::string(std::getenv("EspressoShotPath")) + "Assets/Mesh/f16.obj"), lightingShader, manager, 0);

	//run this scene
	if (sceneTest)
		Espresso::TestScene* s = new Espresso::TestScene(true);


	glEnable(GL_DEPTH_TEST);


	//render loop
	while (!glfwWindowShouldClose(window))
	{

		float currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(*defaultCamera, dt, window);
		glClearColor(0.33f, 0.33f, 0.33f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//manager->update();

		for (unsigned i = 0; i < Scenes.size(); i++) {
			if (!Scenes[i]->isInit())
				Scenes[i]->init();
			if (Scenes[i]->isInit())
				Scenes[i]->baseUpdate(dt, *defaultCamera);
		}
		for (auto x : GameObjects)
			x->baseUpdate(dt);




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

	defaultCamera->doMouseMovement(xoffset, yoffset);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);

}