#include "resource_manager.h"
#include "filesystem.h"

//Define static variables
std::map<std::string, Texture2D>    ResourceManager::textures;
std::map<std::string, Shader>       ResourceManager::shaders;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Shader& ResourceManager::loadShader(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile, std::string name)
{
	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return shaders[name];
}

Shader& ResourceManager::getShader(std::string name)
{
	return shaders[name];
}

Texture2D& ResourceManager::loadTexture(const GLchar * file, std::string name)
{
	textures[name] = loadTextureFromFile(file);
	return textures[name];
}

Texture2D& ResourceManager::getTexture(std::string name)
{
	return textures[name];
}

void ResourceManager::clear()
{
	for (auto iter : shaders)
		glDeleteProgram(iter.second.getID());

	for (auto iter : textures)
		glDeleteTextures(1, &iter.second.getID());
}

Shader ResourceManager::loadShaderFromFile(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try
	{
		std::ifstream vertexShaderFile(Filesystem::getShadersDir() + vShaderFile);
		std::ifstream fragmentShaderFile(Filesystem::getShadersDir() + fShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		#ifdef _DEBUG
			std::cout << "Current Directory: " << __FILE__ << "\nVertex Code:\n" << vertexCode << "\nFragment Code:\n" << fragmentCode << std::endl;
		#endif // DEBUG


		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}

	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();

	Shader shader;
	shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar * file)
{
	Texture2D texture;

	int width, height, numChannels;
	std::string filename = Filesystem::getTextureDir() + file;

	unsigned char* image = stbi_load(filename.c_str(), &width, &height, &numChannels, 0);

	if (image == NULL)
		std::cout << "Cannot load file: " << "\nError: " << stbi_failure_reason() << std::endl;
	else
	{
#ifdef _DEBUG
		std::cout << "Found file!" << std::endl;
#endif
	}

	if (numChannels == 4)
	{
		texture.internal_format = GL_RGBA;
		texture.image_format = GL_RGBA;
	}

	texture.generate(width, height, image);
	stbi_image_free(image);

	return texture;
}
