#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#pragma once
class Light
{
private:
    glm::vec3 lightPosition;
    glm::vec3 lightColor;
    glm::vec3 ambientColor;
    float ambientStrength;
    float specStrength;
    float specPhong;

public:
    void setLightPosition(glm::vec3 lightPositionExternal);
    glm::vec3 getLightPosition();
    void setLightColor(glm::vec3 lightColorExternal);
    glm::vec3 getLightColor();
    void setAmbientColor(glm::vec3 ambientColorExternal);
    glm::vec3 getAmbientColor();
    void setAmbientStrength(float ambientStrengthExternal);
    float getAmbientStrength();
    void setSpecStrength(float spectStrengthExternal);
    float getSpecStrength();
    void setSpecPhong(float specPhongExternal);
    float getSpecPhong();
};
