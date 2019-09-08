#pragma once
#include "Espresso/Scene Manager.h"
#include "Espresso/Camera.h"
#include "Espresso/ShaderProgram.h"
#include "Espresso/XinputManager.h"
#include "Espresso/Scene Manager.h"
#include "Espresso/Cube.h"
#include "Espresso/f16.h"

#define CUBETEST false
#define _CRT_SECURE_NO_WARNINGS

namespace Espresso {

	class TestScene : public Scene {
	public:
		TestScene(bool firstScene);

		bool init() override;
		bool exit() override;
		
		void childUpdate(float dt, Camera& defaultCamera) override;

	private:
		Shader lightingShader{ std::string(std::getenv("EspressoShotPath")) + "Assets/Shaders/lightingShader.vert", std::string(std::getenv("EspressoShotPath")) + "Assets/Shaders/lightingShader.frag" };
		F16 f16{ Mesh(std::string(std::getenv("EspressoShotPath")) + "Assets/Mesh/f16.obj"), lightingShader,nullptr,0 };
#ifdef CUBETEST
		float rotate = 0;
		std::vector<Cube> cubes;
		Texture specularMap;
#endif
	};
}