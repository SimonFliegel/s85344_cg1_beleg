#pragma once

#include <glew.h>

class Texture
{
	public:
	Texture(const char* texturePath, GLuint textureUnit, GLenum wrappingMode = GL_REPEAT, GLenum minificationFilter = GL_LINEAR, GLenum magnificationFilter = GL_LINEAR);
	void bind() const;
	void unbind() const;
	GLuint getTextureID() const;
	GLuint getTextureUnit() const;

private:
	GLuint textureID;
	GLuint textureUnit;
	const char* texturePath;
	GLenum wrappingMode;
	GLenum minificationFilter;
	GLenum magnificationFilter;
	void loadTexture();
};

