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
		GameObject(const Mesh& MESH, const Shader& SHADER, unsigned numTextures,...);

		virtual void update(float dt);
		void updateGO();
		virtual void draw() = 0;
		void setShader(const Shader& SHADER) {
			shader = SHADER;
			shader.createProgram();
		}

		std::string id;
		void loadTextures();
		void loadMesh();
	protected:
		std::vector<Texture*> textures;
		Mesh* mesh = nullptr;
		Shader shader;
		glm::mat4 model = glm::mat4(1.0);

	};
}