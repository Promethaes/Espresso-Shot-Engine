#pragma once
#include "Espresso/Scene Manager.h"
#include "Espresso/Camera.h"
#include "Espresso/ShaderProgram.h"
#include "Espresso/XinputManager.h"
#include "Espresso/Scene Manager.h"
#include "Espresso/Cube.h"
#include "Espresso/f16.h"

#define CUBETEST false

namespace Espresso {

	class TestScene : public Scene {
	public:
		TestScene(bool firstScene);

		bool init() override;
		bool exit() override;
		
		void childUpdate(float dt, Camera& defaultCamera) override;

	private:
		Shader lightingShader{ "../Assets/Shaders/lightingShader.vert", "../Assets/Shaders/lightingShader.frag" };
		F16 f16{ Mesh("../Assets/Mesh/f16.obj"), lightingShader,nullptr,0 };
#ifdef CUBETEST
		float rotate = 0;
		std::vector<Cube> cubes;
		Texture specularMap;
#endif
	};
}