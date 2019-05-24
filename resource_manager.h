#pragma once

#include <map>
#include <string>
#include <stdio.h>

#include "glad/glad.h"

#include "texture2D.h"
#include "shader.h"

//A static singleton resourcemanger to load shaders and textures
class ResourceManager
{
public:
	//Resource storage
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;

	static Shader& loadShader(const GLchar* vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	static Shader& getShader(std::string name);

	static Texture2D& loadTexture(const GLchar* file, std::string name);
	static Texture2D& getTexture(std::string name);

	//deallocate all resources
	static void clear();
private:
	//Prevent objects
	ResourceManager() {}

	static Shader loadShaderFromFile(const GLchar * vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	static Texture2D loadTextureFromFile(const GLchar *file);
};

