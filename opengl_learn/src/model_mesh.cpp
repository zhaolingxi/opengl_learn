#include"model_mesh.h"

ModelMesh::ModelMesh(std::vector<GLVertex> vertices, 
	std::vector<unsigned int> indices, std::vector<GLTexture> textures) {
    vertices_ = vertices;
    indices_ = indices;
    textures_ = textures;
    setupMesh();
}


void ModelMesh::Draw(ShaderLoader shader, unsigned int shaderProgramId) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < textures_.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // �ڰ�֮ǰ������Ӧ������Ԫ
        // ��ȡ������ţ�diffuse_textureN �е� N��
        std::string number;
        std::string name = textures_[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.setInt(shaderProgramId, ("material." + name + number), i);
        glBindTexture(GL_TEXTURE_2D, textures_[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // ��������
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void ModelMesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(GLVertex), &vertices_[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int),
        &indices_[0], GL_STATIC_DRAW);

    // ����λ��
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)0);
    // ���㷨��
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, Normal));
    // ������������
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, TexCoords));

    glBindVertexArray(0);
}