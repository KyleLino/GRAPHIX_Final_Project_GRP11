#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#pragma once
class Model
{
private:
	float positionX = 0.0f;
	float positionY = 0.0f;
	float positionZ = 0.0f;
	float rotationX = 0.0f;
	float rotationY = 1.0f;
	float rotationZ = 0.0f;
	float scaleX = 0.01f;
	float scaleY = 0.01f;
	float scaleZ = 0.01f;
	glm::mat4 projection_matrix = glm::perspective(glm::radians(60.0f), 800.0f / 800.0f, 0.1f, 100.0f);
	glm::vec3 CameraPos = glm::vec3(0, 0, 10.0f);
	glm::vec3 WorldUp = glm::normalize(glm::vec3(0, 1.0f, 0));
	glm::vec3 CameraCenter = glm::vec3(0, 0, 0);
	glm::mat4 viewMatrix;
	glm::mat4 transformation_matrix = glm::mat4(1.0f);
	glm::vec3 lightPos = glm::vec3(-10, 3, 0);
	glm::vec3 lightColor = glm::vec3(1, 1, 1);
	float ambientStr = 0.1f;
	glm::vec3 ambientColor = glm::vec3(1, 1, 1);
	float specStr = 0.5f;
	float specPhong = 16.0f;
	float theta = 90.0f;

public:
	void setPosition(float externalPositionX, float externalPositionY, float externalPositionZ);
	void setRotation(float externalRotationX, float externalRotationY, float externalRotationZ);
	void setScale(float externalScaleX, float externalScaleY, float externalScaleZ);
	void drawObject(GLuint VAO1, GLuint VAO2, GLuint texture1, GLuint texture2, GLuint shader1, GLuint shader2, int size1, glm::mat4 viewMatrixExternal, glm::mat4 projectionMatrixExternal, glm::vec3 cameraPositionExternal, glm::vec3 lightPositionExternal, glm::vec3 lightColorExternal, float ambientStrengthExternal, glm::vec3 ambientColorExternal, float specStrengthExternal, float specPhongExternal, float thetaExternal);
};
