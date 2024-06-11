#include "material.h"

Texture::Texture(const string path, const string type) :path(path), name(type)
{
    // empty operation
}

void Texture::bind(int unit)
{
    this->unit = unit;
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind()
{
    this->unit = -1;
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy()
{
    glDeleteTextures(1, &ID);
}