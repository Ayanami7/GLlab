#include <stb_image.h>

#include "common.h"

Texture::Texture(const string path)
{
    // 使用 stb_image.h 加载图片
    stbi_set_flip_vertically_on_load(true); // 如果需要，翻转图片
    image = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (image)
    {
        // 生成纹理
        glGenTextures(1, &ID);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void Texture::load()
{
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 上传纹理到 GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::unload()
{
    glDeleteTextures(1, &ID);
}

Texture::~Texture()
{
    stbi_image_free(image);
}