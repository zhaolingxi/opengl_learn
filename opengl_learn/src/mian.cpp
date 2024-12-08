#include"common.h"
#include"shader_loader.h"
#include"vertex_shape.h"
#include"zz_backup.h"
#include"texture_loader.h"


int main()
{
    auto window= CommonService::initGLViewWindow();

    TextureLoader texture_loader_2d(TextureType::Texture_2D);
    int texture = texture_loader_2d.loadTexture("D:/Code/work/learning_opengl/opengl_learn/assert/wall.jpg");

    ShaderLoader shader_loader_vs(ShaderType::VERTEX_SHADER, "D:/Code/work/learning_opengl/opengl_learn/shader/vertexsh01.vs");
    ShaderLoader shader_loader_fs(ShaderType::FRAGMENT_SHADER, "D:/Code/work/learning_opengl/opengl_learn/shader/fragmentsh01.fs");
    auto map_vs = shader_loader_vs.getShaderIDMap();
    unsigned int shaderProgram = shader_loader_vs.attachShader({ "textureBox01_vs" });
    auto map_fs = shader_loader_fs.getShaderIDMap();
    shader_loader_fs.attachShader({ "texturebox01_fs" }, shaderProgram);

    ShaderLoader::linkShader(shaderProgram);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureProjectVertices), textureProjectVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(textureProjectIndices), textureProjectIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    while (!glfwWindowShouldClose(window))
    {
        CommonService::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}



