#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glm/glm.hpp"

class Shader
{
public:
	Shader() {}
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	
	Shader& use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
	void compile(const GLchar *vShaderCode, const GLchar* fShaderCode, const GLchar *gShaderCode);

	unsigned int getID() const { return ID; }
private:
	unsigned int ID;

	bool checkError(unsigned int shader, const char* shaderName);
	bool checkLink();
};

