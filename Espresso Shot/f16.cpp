#include "f16.h"
#include "Events.h"
#include "Input.h"
namespace Espresso {
	F16::F16(const Mesh& MESH, const Shader& SHADER)
		:GameObject(MESH, SHADER, 1, new Texture("Assets/Textures/Metal_specmap.png", TextureType::SpecularMap))
	{
		id = "F16";
	}

	void F16::update(float dt)
	{
		if (isEvent(Events::W))
			f16Pos += model[0] * 2.5f * dt;
		if (isEvent(Events::A)) {
			f16RotationV -= glm::vec3(1, 0, 0);
			f16Rotationfloat -= 0.005f;
		}
		if (isEvent(Events::D)) {
			f16RotationV += glm::vec3(1, 0, 0);
			f16Rotationfloat += 0.005f;
		}
		if (isEvent(Events::Q)) {
			f16RotationV -= glm::vec3(0, 1, 0);
			f16Rotationfloat -= 0.005f;
		}
		if (isEvent(Events::E)) {
			f16RotationV += glm::vec3(0, 1, 0);
			f16Rotationfloat += 0.005f;
		}
		if (isEvent(Events::C)) {
			f16RotationV -= glm::vec3(0, 0, 1);
			f16Rotationfloat -= 0.005f;
		}
		if (isEvent(Events::Z)) {
			f16RotationV += glm::vec3(0, 0, 1);
			f16Rotationfloat += 0.005f;
		}
		draw();
	}

	void Espresso::F16::draw()
	{
		glUseProgram(shader.getId());

		for (unsigned i = 0; i < textures.size(); i++) {
			if (textures[i]->type == TextureType::DiffuseMap)
				textures[i]->bind(0);
			else if (textures[i]->type == TextureType::SpecularMap)
				textures[i]->bind(1);
		}

		model = shader.loadModel(true, false, true, f16Pos, 0, f16RotationV, f16Rotationfloat);
		mesh->draw();

		for (unsigned i = 0; i < textures.size(); i++) {
			if (textures[i]->type == TextureType::DiffuseMap)
				textures[i]->unbind(0);
			else if (textures[i]->type == TextureType::SpecularMap)
				textures[i]->unbind(1);
		}
	}
}
