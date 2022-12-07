#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#include "Camera.h"

void Camera::setViewMatrix() {
	viewMatrix = glm::lookAt(cameraPosition, cameraCenter, worldUp);
}

glm::mat4 Camera::getViewMatrix() {
	return viewMatrix;
}

void Camera::setCameraPosition(glm::vec3 cameraPositionExternal) {
	cameraPosition = cameraPositionExternal;
}

glm::vec3 Camera::getCameraPosition() {
	return cameraPosition;
}

void Camera::setWorldUp(glm::vec3 worldUpExternal) {
	worldUp = worldUpExternal;
}

glm::vec3 Camera::getWorldUp() {
	return worldUp;
}

void Camera::setCameraCenter(glm::vec3 cameraCenterExternal) {
	cameraCenter = cameraCenterExternal;
}

glm::vec3 Camera::getCameraCenter() {
	return cameraCenter;
}

void Camera::setPerspective() {
	projectionMatrix = glm::perspective(glm::radians(60.0f), screenHeight / screenWidth, 0.1f, 100.0f);
}

glm::mat4 Camera::getPerspective() {
	return projectionMatrix;
}

void Camera::setScreenWidth(float screenWidthExternal) {
	screenWidth = screenWidthExternal;
}

float Camera::getScreenWidth() {
	return screenWidth;
}

void Camera::setScreenHeight(float screenHeightExternal) {
	screenHeight = screenHeightExternal;
}

float Camera::getScreenHeight() {
	return screenHeight;
}
