#include"common.h"
#include"shader_loader.h"
#include"model_loader.h"
#include"camera_gl.h"
#include"vertex_shape.h"
#include"zz_backup.h"
#include<filesystem>





int main()
{
    CommonService* service = CommonService::getInstance();
    service->main_camera = new GLCamera(glm::vec3(0.0f, 0.0f, 3.0f));
    auto window= CommonService::initGLViewWindow();


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, CommonService::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, CommonService::mouse_callback);
 //   glfwSetScrollCallback(window, CommonService::scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
        shader_loader_vs.setMat4F(shaderProgram,"view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shader_loader_vs.setMat4F(shaderProgram,"model", model);
        ourModel.Draw(shader_loader_vs, shaderProgram);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



