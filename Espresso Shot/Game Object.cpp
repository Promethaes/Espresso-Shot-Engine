#include "Game Object.h"
#include <cstdarg>
namespace Espresso {

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
	}
	void GameObject::update(float dt)
	{
	}
	void GameObject::updateGO()
	{
	}
	void GameObject::loadTextures()
	{
		for (unsigned i = 0; i < textures.size(); i++) 
			textures[i]->load();
	}
	void GameObject::loadMesh()
	{
		mesh->loadMesh();
	}
}