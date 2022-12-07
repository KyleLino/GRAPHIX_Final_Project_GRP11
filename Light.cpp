#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#include "Light.h"

void Light::setLightPosition(glm::vec3 lightPositionExternal) {
	lightPosition = lightPositionExternal;
}

glm::vec3 Light::getLightPosition() {
	return lightPosition;
}

void Light::setLightColor(glm::vec3 lightColorExternal) {
	lightColor = lightColorExternal;
}

glm::vec3 Light::getLightColor() {
	return lightColor;
}

void Light::setAmbientColor(glm::vec3 ambientColorExternal) {
	ambientColor = ambientColorExternal;
}

glm::vec3 Light::getAmbientColor() {
	return ambientColor;
}

void Light::setAmbientStrength(float ambientStrengthExternal) {
	ambientStrength = ambientStrengthExternal;
}

float Light::getAmbientStrength() {
	return ambientStrength;
}

void Light::setSpecStrength(float specStrengthExternal) {
	specStrength = specStrengthExternal;
}

float Light::getSpecStrength() {
	return specStrength;
}

void Light::setSpecPhong(float specPhongExternal) {
	specPhong = specPhongExternal;
}

float Light::getSpecPhong() {
	return specPhong;
}
