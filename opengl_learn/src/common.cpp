#include"common.h"
#include"camera_gl.h"

CommonService* CommonService::instance;
void CommonService::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void CommonService::processInput(GLFWwindow* window, GLCamera* camera)
{
    CommonService* service = CommonService::getInstance();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, service->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, service->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, service->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, service->deltaTime);

    //if (camera) {
    //    
    //}
}


GLFWwindow* CommonService::initGLViewWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, CommonService::framebuffer_size_callback);

    return window;
}

void CommonService::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    CommonService* service = CommonService::getInstance();

    if (service->firstMouse)
    {
        service->lastX = xpos;
        service->lastY = ypos;
        service->firstMouse = false;
    }

    float xoffset = xpos - service->lastX;
    float yoffset = service->lastY - ypos; // reversed since y-coordinates go from bottom to top

    service->lastX = xpos;
    service->lastY = ypos;

    if (service->main_camera) {
        service->main_camera->ProcessMouseMovement(xoffset, yoffset);
    }
}


void CommonService::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    CommonService* service = CommonService::getInstance();
    if (service->main_camera) {
        service->main_camera->ProcessMouseScroll(static_cast<float>(yoffset));
    }
}
