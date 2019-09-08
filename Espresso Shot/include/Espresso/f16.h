#pragma once
#include "Espresso/Game Object.h"
#include "Espresso/XinputManager.h"
namespace Espresso {
	class F16 :public GameObject {
	public:
		F16(const Mesh& MESH, const Shader& SHADER, const Sedna::XinputManager* manager,unsigned controllerIndex);

		void childUpdate(float dt) override;
	private:
		void draw() override;
		Sedna::XinputController* controller = nullptr;
		glm::vec4 f16Pos = glm::vec4(0,0,0,1);
		glm::vec3 f16RotationV = glm::vec3(1,1,1);
		float f16Rotationfloat = 0.0f;
		glm::mat4 f16ModelMat = glm::mat4(1.0f);

	};
}