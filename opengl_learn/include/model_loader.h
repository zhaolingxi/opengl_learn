#pragma once
#include"common.h"
#include"shader_loader.h"
#include"model_mesh.h"

#include <map>
#include<vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

enum ModelType :int {
	OBJ_MODEL = 0x00,
	STL_MODEL = 0x01, // 0x01
	FBX_MODEL = 0x02, // 0x02
};

class ModelLoader {
public:
    ModelLoader(unsigned int type, std::string filePath) {
        loadModel(filePath);
    }

	virtual ~ModelLoader();

    void Draw(ShaderLoader shader, unsigned int shaderProgramId) {
        for (unsigned int i = 0; i < meshes_.size(); i++)
            meshes_[i].Draw(shader, shaderProgramId);
    }

    static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
private:
    /*  模型数据  */
    std::vector<ModelMesh> meshes_;
    std::string directory_;
    std::vector<GLTexture> textures_loaded_;
    /*  函数   */
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    ModelMesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<GLTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);

};