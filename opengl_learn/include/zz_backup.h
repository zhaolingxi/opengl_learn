#pragma once
#include"common.h"
#include"shader_loader.h"
#include"vertex_shape.h"
#include"texture_loader.h"


void drawDynamicDoubleTriangle(GLFWwindow* window){
    ShaderLoader shader_loader_vs(ShaderType::VERTEX_SHADER, "D:/Code/work/learning_opengl/opengl_learn/shader/vertexsh01.vs");
    ShaderLoader shader_loader_fs(ShaderType::FRAGMENT_SHADER, "D:/Code/work/learning_opengl/opengl_learn/shader/fragmentsh01.fs");
    auto map_vs = shader_loader_vs.getShaderIDMap();
    unsigned int shaderProgram = shader_loader_vs.attachShader({"trangle01_vs"});
    auto map_fs = shader_loader_fs.getShaderIDMap();
    shader_loader_fs.attachShader({ "trangle03_fs" }, shaderProgram);

    ShaderLoader::linkShader(shaderProgram);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(doubleTriangle), doubleTriangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(doubleTriangleIndices), doubleTriangleIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window))
    {
        CommonService::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // ¸üÐÂuniformÑÕÉ«
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        ShaderLoader::setUnifromF(shaderProgram, "uniColor", greenValue);

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}

void drawColorfulTriangle(GLFWwindow* window) {
    ShaderLoader shader_loader_vs(ShaderType::VERTEX_SHADER, "D:/Code/work/learning_opengl/opengl_learn/shader/vertexsh01.vs");
    ShaderLoader shader_loader_fs(ShaderType::FRAGMENT_SHADER, "D:/Code/work/learning_opengl/opengl_learn/shader/fragmentsh01.fs");
    auto map_vs = shader_loader_vs.getShaderIDMap();
    unsigned int shaderProgram = shader_loader_vs.attachShader({ "trangle03_vs" });
    auto map_fs = shader_loader_fs.getShaderIDMap();
    shader_loader_fs.attachShader({ "trangle04_fs" }, shaderProgram);


    ShaderLoader::linkShader(shaderProgram);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleWithColorVertices), triangleWithColorVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(shaderProgram);

    while (!glfwWindowShouldClose(window))
    {
        CommonService::processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

void drawTextureSquare(GLFWwindow* window) {
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
}

void drawTextureSquareRotate(GLFWwindow* window) {
    TextureLoader texture_loader_2d(TextureType::Texture_2D);
    int texture = texture_loader_2d.loadTexture("D:/Code/work/learning_opengl/opengl_learn/assert/wall.jpg");

    ShaderLoader shader_loader_vs(ShaderType::VERTEX_SHADER, "D:/Code/work/learning_opengl/opengl_learn/shader/vertexsh01.vs");
    ShaderLoader shader_loader_fs(ShaderType::FRAGMENT_SHADER, "D:/Code/work/learning_opengl/opengl_learn/shader/fragmentsh01.fs");
    auto map_vs = shader_loader_vs.getShaderIDMap();
    unsigned int shaderProgram = shader_loader_vs.attachShader({ "textureBoxRotate01_vs" });
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

        // create transformations
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        ShaderLoader::setMat4F(shaderProgram, "transform", transform);


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
}

void drawTextureColor(GLFWwindow* window) {
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
}

void drawModelNanosuit(GLFWwindow* window) {
    CommonService* service = CommonService::getInstance();
    service->main_camera = new GLCamera(glm::vec3(0.0f, 0.0f, 40.0f));

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, CommonService::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, CommonService::mouse_callback);
    glfwSetScrollCallback(window, CommonService::scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return ;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    ShaderLoader shader_loader_vs(ShaderType::VERTEX_SHADER, "D:/Code/work/learning_opengl/opengl_learn/shader/vertexsh01.vs");
    ShaderLoader shader_loader_fs(ShaderType::FRAGMENT_SHADER, "D:/Code/work/learning_opengl/opengl_learn/shader/fragmentsh01.fs");
    auto map_vs = shader_loader_vs.getShaderIDMap();
    unsigned int shaderProgram = shader_loader_vs.attachShader({ "modelLoad01_vs" });
    auto map_fs = shader_loader_fs.getShaderIDMap();
    shader_loader_fs.attachShader({ "modelLoad01_fs" }, shaderProgram);
    ShaderLoader::linkShader(shaderProgram);

    // load models
    // -----------
    std::string model_path = ASSERT_PATH;
    model_path += "/nanosuit/nanosuit.obj";
    ModelLoader ourModel(ModelType::OBJ_MODEL, model_path);


    // draw in wireframe
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        service->deltaTime = currentFrame - service->lastFrame;
        service->lastFrame = currentFrame;

        // input
        // -----
        CommonService::processInput(window, service->main_camera);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(service->main_camera->Zoom), (float)service->SCR_WIDTH / (float)service->SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = service->main_camera->GetViewMatrix();
        shader_loader_vs.setMat4F(shaderProgram, "projection", projection);
        shader_loader_vs.setMat4F(shaderProgram, "view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shader_loader_vs.setMat4F(shaderProgram, "model", model);
        ourModel.Draw(shader_loader_vs, shaderProgram);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}