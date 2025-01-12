#pragma once
#include"common.h"
#include"shader_loader.h"
#include<vector>
class ModelMesh {
public:
	//ModelMesh();

    virtual ~ModelMesh() {};

public:
    /*  网格数据  */
    std::vector<GLVertex> vertices_;
    std::vector<unsigned int> indices_;
    std::vector<GLTexture> textures_;
    /*  函数  */
    ModelMesh(std::vector<GLVertex> vertices, std::vector<unsigned int> indices, std::vector<GLTexture> textures);
    void Draw(ShaderLoader shader, unsigned int shaderProgramId);
private:
    /*  渲染数据  */
    unsigned int VAO, VBO, EBO;
    /*  函数  */
    void setupMesh();
};