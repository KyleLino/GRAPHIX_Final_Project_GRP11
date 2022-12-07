#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#include "Shader.h"

void Shader::setObjectShader(GLuint externalObjectShaderProgram)
{
	objectShaderProgram = externalObjectShaderProgram;
}

GLuint Shader::getObjectShader()
{
	return objectShaderProgram;
}
