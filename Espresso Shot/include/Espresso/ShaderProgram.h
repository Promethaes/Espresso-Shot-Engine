#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string>
namespace Espresso {

	class Camera;

	class Shader {
	public:

		Shader() = default;
		Shader(std::string VERTSHADERSOURCE, std::string FRAGSHADERSOURCE);

		//only call this function if you can't call the constructor for some reason
		void createShader(const std::string& VERTSHADERSOURCE, std::string FRAGSHADERSOURCE);
		//get the program 
		unsigned getId() const { return shaderProgram; }
		void setVec3(const std::string&name, const float x, const float y, const float z) const;
		void setVec3(const std::string &name, const glm::vec3 &value) const;
		void setVec4(const std::string& name, const glm::vec3& value) const;
		void setFloat(const std::string &name, const float& value) const;
		void setInt(const std::string& name, const int& value)const;

		void createProgram();
		//not sure if i should be making these functions but we're gonna try it anyways

		glm::mat4 loadModelMatrix(bool transform = false,bool scale = false, bool rotate = false,const glm::vec3& translatiom = glm::vec3(0, 0, 0),float scaleBy = 0.0f,const glm::vec3& rotateBy = glm::vec3(0,0,0),float rotationAngle = 0.0f);
		void loadModelMatrix(const glm::mat4& model);
		void loadViewMatrix(Camera& defaultCamera);
		void loadProjectionMatrix(float width, float height);
	private:
		//compiles the shader that you pass in
		void compileShader(unsigned shader, const char* tempString);


		unsigned shaderProgram;
		unsigned vertexShader;
		std::string vertexShaderSource;
		std::string fragmentShaderSource;
		unsigned fragmentShader;
	};
}
