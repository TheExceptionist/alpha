#include "resource_manager.h"
#include "filesystem.h"

//Define static variables
std::map<std::string, Texture2D>    ResourceManager::textures;
std::map<std::string, Shader>       ResourceManager::shaders;
std::map<int, Texture2D>    ResourceManager::chars;


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void ResourceManager::clear()
{
	for (auto iter : shaders)
		glDeleteProgram(iter.second.getID());

	for (auto iter : textures)
		glDeleteTextures(1, &iter.second.getID());

	for (auto iter : chars)
		glDeleteTextures(1, &iter.second.getID());
}


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

Texture2D & ResourceManager::getChar(const int code, const bool is_ascii)
{
	int charcode = is_ascii ? charToCharset(code) : code;
	return chars[charcode];
}

void ResourceManager::loadCharset()
{
	for (int i = 0; i < NUM_CHAR_SET; i++)
	{
		std::string filename = char_set_names[i] + char_set_extension;
		chars[i] = loadTextureFromFile(filename.c_str());
	}
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

	int width, height, num_channels;
	std::string filename = Filesystem::getTextureDir() + file;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(filename.c_str(), &width, &height, &num_channels, 0);

	std::cout << "Loading file... " << file << std::endl;

	if (image == NULL)
		std::cout << "Cannot load file: " << file << "\nError: " << stbi_failure_reason() << std::endl;
	else
	{
		std::cout << "Found file: " << file << "!" << std::endl;
	}

#ifdef _DEBUG
	std::cout << "Num channels: " << num_channels << std::endl;
#endif

	if (num_channels == 4)
	{
		texture.internal_format = GL_RGBA;
		texture.image_format = GL_RGBA;
	}

	texture.generate(width, height, image);
	stbi_image_free(image);

	return texture;
}

int ResourceManager::charToCharset(const char code)
{
	switch (code)
	{
	case '0':
	{
		return CHAR_ZERO;
	}
	case '1':
	{
		return CHAR_ONE;
	}
	case '2':
	{
		return CHAR_TWO;
	}
	case '3':
	{
		return CHAR_THREE;
	}
	case '4':
	{
		return CHAR_FOUR;
	}
	case '5':
	{
		return CHAR_FIVE;
	}
	case '6':
	{
		return CHAR_SIX;
	}
	case '7':
	{
		return CHAR_SEVEN;
	}
	case '8':
	{
		return CHAR_EIGHT;
	}
	case '9':
	{
		return CHAR_NINE;
	}
	case '+':
	{
		return CHAR_PLUS;
	}
	case '-':
	{
		return CHAR_MINUS;
	}
	case '*':
	{
		return CHAR_STAR;
	}
	case '/':
	{
		return CHAR_SLASH;
	}
	case '.':
	{
		return CHAR_PERIOD;
	}
	case '!':
	{
		return CHAR_CURVED_DOWN_EXCLAIM;
	}
	case '?':
	{
		return CHAR_QUESTION;
	}
	case '"':
	{
		return CHAR_QUOTATION;
	}
	case '\'':
	{
		return CHAR_APOSTROPHE;
	}
	case ',':
	{
		return CHAR_COMMA;
	}
	case ':':
	{
		return CHAR_COLON;
	}
	case '(':
	{
		return CHAR_LEFT_PARATHESIS;
	}
	case ')':
	{
		return CHAR_RIGHT_PARATHESIS;
	}

	case 'a':
	{
		return CHAR_A;
	}
	case 'b':
	{
		return CHAR_B;
	}
	case 'c':
	{
		return CHAR_C;
	}
	case 'd':
	{
		return CHAR_D;
	}
	case 'e':
	{
		return CHAR_E;
	}
	case 'f':
	{
		return CHAR_F;
	}
	case 'g':
	{
		return CHAR_G;
	}
	case 'h':
	{
		return CHAR_H;
	}
	case 'i':
	{
		return CHAR_I;
	}
	case 'j':
	{
		return CHAR_J;
	}
	case 'k':
	{
		return CHAR_K;
	}
	case 'l':
	{
		return CHAR_L;
	}
	case 'm':
	{
		return CHAR_M;
	}
	case 'n':
	{
		return CHAR_N;
	}
	case 'o':
	{
		return CHAR_O;
	}
	case 'p':
	{
		return CHAR_P;
	}
	case 'q':
	{
		return CHAR_Q;
	}
	case 'r':
	{
		return CHAR_R;
	}
	case 's':
	{
		return CHAR_S;
	}
	case 't':
	{
		return CHAR_T;
	}
	case 'u':
	{
		return CHAR_U;
	}
	case 'v':
	{
		return CHAR_V;
	}
	case 'w':
	{
		return CHAR_W;
	}
	case 'x':
	{
		return CHAR_X;
	}
	case 'y':
	{
		return CHAR_Y;
	}
	case 'z':
	{
		return CHAR_Z;
	}
	case 'A':
	{
		return CHAR_UPPER_A;
	}
	case 'B':
	{
		return CHAR_UPPER_B;
	}
	case 'C':
	{
		return CHAR_UPPER_C;
	}
	case 'D':
	{
		return CHAR_UPPER_D;
	}
	case 'E':
	{
		return CHAR_UPPER_E;
	}
	case 'F':
	{
		return CHAR_UPPER_F;
	}
	case 'G':
	{
		return CHAR_UPPER_G;
	}
	case 'H':
	{
		return CHAR_UPPER_H;
	}
	case 'I':
	{
		return CHAR_UPPER_I;
	}
	case 'J':
	{
		return CHAR_UPPER_J;
	}
	case 'K':
	{
		return CHAR_UPPER_K;
	}
	case 'L':
	{
		return CHAR_UPPER_L;
	}
	case 'M':
	{
		return CHAR_UPPER_M;
	}
	case 'N':
	{
		return CHAR_UPPER_N;
	}
	case 'O':
	{
		return CHAR_UPPER_O;
	}
	case 'P':
	{
		return CHAR_UPPER_P;
	}
	case 'Q':
	{
		return CHAR_UPPER_Q;
	}
	case 'R':
	{
		return CHAR_UPPER_R;
	}
	case 'S':
	{
		return CHAR_UPPER_S;
	}
	case 'T':
	{
		return CHAR_UPPER_T;
	}
	case 'U':
	{
		return CHAR_UPPER_U;
	}
	case 'V':
	{
		return CHAR_UPPER_V;
	}
	case 'W':
	{
		return CHAR_UPPER_W;
	}
	case 'X':
	{
		return CHAR_UPPER_X;
	}
	case 'Y':
	{
		return CHAR_UPPER_Y;
	}
	case 'Z':
	{
		return CHAR_UPPER_Z;
	}
	}
}