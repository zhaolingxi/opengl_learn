#pragma once
#include"common.h"
#include"shader_loader.h"
#include<vector>
class ModelMesh {
public:
	//ModelMesh();

    virtual ~ModelMesh() {};

public:
    /*  ��������  */
    std::vector<GLVertex> vertices_;
    std::vector<unsigned int> indices_;
    std::vector<GLTexture> textures_;
    /*  ����  */
    ModelMesh(std::vector<GLVertex> vertices, std::vector<unsigned int> indices, std::vector<GLTexture> textures);
    void Draw(ShaderLoader shader, unsigned int shaderProgramId);
private:
    /*  ��Ⱦ����  */
    unsigned int VAO, VBO, EBO;
    /*  ����  */
    void setupMesh();
};