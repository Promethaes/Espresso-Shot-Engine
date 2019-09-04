#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <string>
namespace Espresso {
	enum TextureType {
		DiffuseMap = 0,
		SpecularMap
	};
	class Texture {
	public:
		Texture(std::string PATH,const TextureType& type);
		bool load();
		unsigned getTextureId() const { return texture; }
		void bind(unsigned textureSlot) {
			glActiveTexture(GL_TEXTURE + textureSlot);
			glBindTexture(GL_TEXTURE_2D, texture);
		}
		void unbind(unsigned textureSlot) {
			glActiveTexture(GL_TEXTURE + textureSlot);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		TextureType type;
	private:
		std::string path;
		unsigned texture;
	};
}