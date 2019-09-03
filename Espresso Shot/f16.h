#pragma once
#include "Game Object.h"
namespace Espresso {
	class F16 :public GameObject {
	public:
		F16(const Mesh& MESH, const Shader& SHADER);

		void update(float dt) override;
		void draw() override;
	private:
		glm::vec4 f16Pos = glm::vec4(0,0,0,1);
		glm::vec3 f16RotationV = glm::vec3(1,1,1);
		float f16Rotationfloat = 0.0f;

	};
}