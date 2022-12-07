#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#pragma once
class Shader
{
private:
	GLuint objectShaderProgram;

public:
	void setObjectShader(GLuint externalObjectShaderProgram);
	GLuint getObjectShader();
};
