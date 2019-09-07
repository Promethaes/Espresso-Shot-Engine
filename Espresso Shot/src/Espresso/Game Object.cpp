#include "Espresso/Game Object.h"
namespace Espresso {

	std::vector<GameObject*> GameObject::gameObjects = {};
	GameObject::GameObject(const Shader& SHADER, const std::vector<Texture*>& textures, const std::vector<Mesh*>& meshs)
		:shader(SHADER)
	{
		//mesh = new Mesh(MESH);

		this->textures = textures;
		this->meshs = meshs;

		loadTextures();
		loadMesh();

		gameObjects.push_back(this);
	}
	void GameObject::baseUpdate(float dt)
	{
		childUpdate(dt);
	}
	void GameObject::draw()
	{
		glUseProgram(shader.getId());

		for (unsigned i = 0; i < textures.size(); i++) {
			if (textures[i]->type == TextureType::DiffuseMap)
				textures[i]->bind(0);
			else if (textures[i]->type == TextureType::SpecularMap)
				textures[i]->bind(1);
		}

		for (unsigned i = 0; i < meshs.size(); i++) {
			meshs[i]->modelMatrix = shader.loadModelMatrix(std::nullopt, std::nullopt, std::nullopt, std::nullopt);
			meshs[i]->draw();
		}



		for (unsigned i = 0; i < textures.size(); i++) {
			if (textures[i]->type == TextureType::DiffuseMap)
				textures[i]->unbind(0);
			else if (textures[i]->type == TextureType::SpecularMap)
				textures[i]->unbind(1);
		}
	}
	void GameObject::loadTextures()
	{
		if (!loadedTextures) {

			for (unsigned i = 0; i < textures.size(); i++) {
				if (textures[i]->load())
					continue;
				else
					return;
			}
			loadedTextures = true;
		}

	}
	void GameObject::loadMesh()
	{
		if (!loadedMesh) {

			for (unsigned i = 0; i < meshs.size(); i++) {
				if (meshs[i]->loadMesh())
					continue;
				else
					return;
			}
			loadedMesh = true;
		}
	}
}