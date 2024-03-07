#include <iostream>
#include <FreeImage.h>

#include "Texture.h"

Texture::Texture(const char* texturePath, GLuint textureUnit, GLenum minificationFilter, GLenum magnificationFilter)
{
	this->texturePath = texturePath;
	this->textureUnit = textureUnit;
	this->minificationFilter = minificationFilter;
	this->magnificationFilter = magnificationFilter;
	loadTexture();
}

void Texture::loadTexture()
{
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(texturePath, 0);

	if (format == -1) {
		std::cout << "Could not find image: " << texturePath << std::endl;
	}
	else if (format == FIF_UNKNOWN) {
		std::cout << "Couldn't determine file format - attempting to get from file extension..." << std::endl;
		format = FreeImage_GetFIFFromFilename(texturePath);
		if (!FreeImage_FIFSupportsReading(format)) {
			std::cout << "Detected image format cannot be read!" << std::endl;
		}
	}

	FIBITMAP* bitmap = FreeImage_Load(format, texturePath);
	

	GLint bitmapWidth = FreeImage_GetWidth(bitmap);
	GLint bitmapHeight = FreeImage_GetHeight(bitmap);

	GLubyte* textureData = (FreeImage_GetBits(bitmap));

	glGenTextures(1, &textureID); // generate a unique texture ID as reference to texture object
	
	bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapWidth, bitmapHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minificationFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnificationFilter);

	FreeImage_Unload(bitmap); // deletes FIBITMAP data

	unbind();
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
}

void Texture::unbind() const // needed? DON'T USE: breaks the program
{
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureID() const
{
	return textureID;
}

GLuint Texture::getTextureUnit() const
{
	return textureUnit;
}