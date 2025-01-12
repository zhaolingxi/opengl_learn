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
    // ˽�й��캯��
    CommonService() {}

    // ˽�п������캯���͸�ֵ������
    CommonService(const CommonService&) = delete;
    CommonService& operator=(const CommonService&) = delete;

    // ����ʵ��
    static CommonService* instance;

    // ˽�г�Ա����
   

public:
    // ��ȡ����ʵ���ľ�̬����
    static CommonService* getInstance() {
        if (instance == nullptr) {
            instance = new CommonService();
        }
        return instance;
    }

    // ��Ա����
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static GLFWwindow* initGLViewWindow();
    static void processInput(GLFWwindow* window, GLCamera* camera = nullptr);

    // ���ڲ�����Ҫ��̬��Ա�����������Ƴ����Ϊ��ͨ��Ա����
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