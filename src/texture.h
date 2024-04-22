#pragma once
#include <stb_image.h>
#include "common.h"

struct Texture
{
    unsigned int ID;
    int width;
    int height;
    int nrChannels;

    Texture(string path);
    ~Texture();
    void bind();
    void unbind();
    inline unsigned int getID() { return ID; }
    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
    inline int getNrChannels() { return nrChannels; }
};