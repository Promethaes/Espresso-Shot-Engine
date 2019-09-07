#include "Espresso/f16.h"
#include "Espresso/Events.h"
#include "Espresso/Input.h"
namespace Espresso {
	F16::F16(const Mesh& MESH, const Shader& SHADER, const Sedna::XinputManager* manager, unsigned controllerIndex)
		:GameObject(SHADER, std::vector<Texture*>{new Texture("../Assets/Textures/Metal_specmap.png", TextureType::SpecularMap), new Texture("../Assets/Textures/container2.png", TextureType::SpecularMap)},
							std::vector<Mesh*>	 {new Mesh("../Assets/Mesh/f16.obj")})
	{
		id = "F16";
		if (manager != nullptr)
			controller = manager->getController(controllerIndex);
	}
	void F16::childUpdate(float dt)
	{

		if (isEvent(Events::W))
			f16Pos += meshs.back()->modelMatrix[0] * 2.5f * dt;
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

		for (auto x : meshs) {

			x->modelMatrix = shader.loadModelMatrix(f16Pos, std::nullopt, f16RotationV, f16Rotationfloat);
			x->draw();
		}

		for (unsigned i = 0; i < textures.size(); i++) {
			if (textures[i]->type == TextureType::DiffuseMap)
				textures[i]->unbind(0);
			else if (textures[i]->type == TextureType::SpecularMap)
				textures[i]->unbind(1);
		}
	}
}
