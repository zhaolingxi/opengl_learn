#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include<vector>
#include <iostream>

class GLCamera;



class CommonService {
private:
    // 私有构造函数
    CommonService() {}

    // 私有拷贝构造函数和赋值操作符
    CommonService(const CommonService&) = delete;
    CommonService& operator=(const CommonService&) = delete;

    // 单例实例
    static CommonService* instance;

    // 私有成员变量
   

public:
    // 获取单例实例的静态方法
    static CommonService* getInstance() {
        if (instance == nullptr) {
            instance = new CommonService();
        }
        return instance;
    }

    // 成员函数
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static GLFWwindow* initGLViewWindow();
    static void processInput(GLFWwindow* window, GLCamera* camera = nullptr);

    // 由于不再需要静态成员变量，可以移除或改为普通成员变量
    GLCamera* main_camera{nullptr};

    unsigned int SCR_WIDTH = 800;
    unsigned int SCR_HEIGHT = 600;
    bool firstMouse = true;
    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};

struct GLVertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct GLTexture {
    unsigned int id;
    std::string type;
    std::string path;
};