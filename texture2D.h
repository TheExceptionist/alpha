#pragma once

#include <glad/glad.h>

class Texture2D
{
public:
	GLuint width, height;

	//Texture format
	GLuint internal_format;
	GLuint image_format;

	GLuint wrap_s; //(x)
	GLuint wrap_t;//(y)

	GLuint filter_min;
	GLuint filter_max;

	Texture2D();

	void generate(GLuint width, GLuint height, unsigned char* data);

	//Binds the texture as the current active GL_TEXTURE_D texture object
	void bind() const;

	GLuint& getID() { return ID; }
private:
	GLuint ID;

};

