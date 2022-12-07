#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#pragma once
class Camera
{
private:
	glm::mat4 viewMatrix;
	glm::vec3 cameraPosition;
	glm::vec3 worldUp;
	glm::vec3 cameraCenter;
	glm::mat4 projectionMatrix;
	float screenWidth;
	float screenHeight;

public:
	void setViewMatrix();
	glm::mat4 getViewMatrix();
	void setCameraPosition(glm::vec3 cameraPositionExternal);
	glm::vec3 getCameraPosition();
	void setWorldUp(glm::vec3 worldUpExternal);
	glm::vec3 getWorldUp();
	void setCameraCenter(glm::vec3 cameraCenterExternal);
	glm::vec3 getCameraCenter();
	void setPerspective();
	glm::mat4 getPerspective();
	void setScreenWidth(float screenWidthExternal);
	float getScreenWidth();
	void setScreenHeight(float screenHeightExternal);
	float getScreenHeight();
};
