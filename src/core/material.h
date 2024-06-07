#pragma once

#include "common.h"

// 纹理创建时只是记录了路径和类型，加载时才会真正创建纹理
// 需要注意预加载
struct Texture
{
    unsigned int ID;
    bool loaded = false;
    string path;
    string name;

    // 默认构造
    Texture(const string path, const string type);
    // 拷贝构造
    Texture(const Texture &other) : ID(other.ID), path(other.path), name(other.name), loaded(other.loaded){}
    // 析构
    ~Texture(){};

    bool operator==(const Texture &other) const
    {
        return this->ID == other.ID;
    }
    bool operator!=(const Texture &other) const
    {
        return this->ID != other.ID;
    }
    void load();
    void bind();
    void unbind();
    void destroy();
    inline unsigned int getID() { return ID; }
};

struct Material
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    vector<Texture> textures;
};
