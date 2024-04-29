#pragma once

#include <glew.h>

class Texture
{
public:
	/// <summary>
	/// wraps the texture loading and binding process
	/// </summary>
	/// <param name="texturePath"></param>
	/// <param name="textureUnit"></param>
	/// <param name="wrappingMode">default: GL_REPEAT</param>
	/// <param name="minificationFilter">default: GL_LINEAR</param>
	/// <param name="magnificationFilter">default: GL_LINEAR</param>
	Texture(const char* texturePath, GLuint textureUnit, GLenum wrappingMode = GL_REPEAT, GLenum minificationFilter = GL_LINEAR, GLenum magnificationFilter = GL_LINEAR);
	
	/// <summary>
	/// binds the texture to the texture unit
	/// </summary>
	void bind() const;

	/// <summary>
	/// unbinds the texture from the texture unit
	/// </summary>
	void unbind() const;

	/// <returns>texture-ID of the texture object</returns>
	GLuint getTextureID() const;

	/// <returns>texture unit of the texture object</returns>
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

