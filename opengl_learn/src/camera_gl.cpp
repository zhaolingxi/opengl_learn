#include"camera_gl.h"

GLCamera::GLCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

GLCamera::~GLCamera() {

}