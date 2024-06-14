#include <stb_image.h>

#include "common.h"

Texture::Texture(const string path, const string type, bool reverse) :path(path), name(type)
{
    unsigned char *image;
    int width;
    int height;
    int nrChannels;
    // 使用 stb_image.h 加载图片
    stbi_set_flip_vertically_on_load(reverse); // 如果需要，翻转图片
    image = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha); // 加载带有alpha通道的图像
    if (image)
    {
        // 生成纹理
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // 上传纹理到 GPU
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image); // 使用 GL_RGBA
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(image);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy()
{
    glDeleteTextures(1, &ID);
}