#pragma once
#include "Espresso/Mesh.h"
#include "Espresso/ShaderProgram.h"
#include "Espresso/Texture.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
namespace Espresso {
	class GameObject {
	public:
		GameObject(const Shader& SHADER, const std::vector<Texture*>& textures, const std::vector<Mesh*>& meshs);

		void baseUpdate(float dt);
		void setShader(const Shader& SHADER) {
			shader = SHADER;
			shader.createProgram();
		}

		static std::vector<GameObject*> gameObjects;

		std::string id;
		void loadTextures();
		void loadMesh();
	protected:
		virtual void draw();
		bool loadedTextures = false;
		bool loadedMesh = false;

		std::vector<Texture*> textures;
		std::vector<Mesh*> meshs;
		Shader shader;
	private:
		virtual void childUpdate(float dt) = 0;

	};
}