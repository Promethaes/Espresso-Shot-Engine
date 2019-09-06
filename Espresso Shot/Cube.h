#pragma once
#include "Espresso/Texture.h"
#include <glm/glm.hpp>
#include <vector>
namespace Espresso {

	class Cube {
	public:

		Cube(float* verts, const unsigned sizeOfArray, Texture* TEXTURERECT,bool irregularVertData = false );

		void draw();
		Texture getTexture() const { return textureRect; }
		glm::vec3 position;
	private:
		void bindBuffers(float * verts,const unsigned sizeOfArray);
		void bindVertPointers();

		Texture textureRect;

		//static bool VAOExist;
		unsigned VAO;
		unsigned VBO, EBO;
		bool irregularVertData;
	};
}