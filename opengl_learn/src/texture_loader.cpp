#include"texture_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

TextureLoader::TextureLoader(TextureType type)
{
    type_ =type;
}


TextureLoader::~TextureLoader() {
    for (auto&& it : name_id_map_) {
        //glDeleteShader(it.second);
    }
}


int TextureLoader::loadTexture(std::string filePath) {
    unsigned int texture;
    glGenTextures(1, &texture);
    if (type_ == TextureType::Texture_2D) {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    name_id_map_.insert({ filePath ,texture });
    return texture;
}