#include "Espresso/Game Object.h"
#include <cstdarg>
namespace Espresso {

	std::vector<GameObject*> GameObject::gameObjects = {};
	GameObject::GameObject(const Mesh& MESH, const Shader& SHADER, unsigned numTextures, ...)
		:shader(SHADER)
	{
		mesh = new Mesh(MESH);

		va_list args;
		va_start(args, numTextures);
		for (unsigned i = 0; i < numTextures; i++)
			textures.push_back(va_arg(args, Texture*));

		va_end(args);

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

		model = shader.loadModelMatrix(std::nullopt,std::nullopt,std::nullopt,std::nullopt);
		mesh->draw();

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
		if (!loadedMesh)
			loadedMesh = mesh->loadMesh();
	}
}