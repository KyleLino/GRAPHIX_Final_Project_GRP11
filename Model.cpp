#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#include "Model.h"

void Model::setPosition(float externalPositionX, float externalPositionY, float externalPositionZ) {
    positionX = externalPositionX;
    positionY = externalPositionY;
    positionZ = externalPositionZ;
}

void Model::setRotation(float externalRotationX, float externalRotationY, float externalRotationZ) {
    rotationX = externalRotationX;
    rotationY = externalRotationY;
    rotationZ = externalRotationZ;
}

void Model::setScale(float externalScaleX, float externalScaleY, float externalScaleZ) {
    scaleX = externalScaleX;
    scaleY = externalScaleY;
    scaleZ = externalScaleZ;
}

void Model::drawObject(GLuint VAO1, GLuint VAO2, GLuint texture1, GLuint texture2, GLuint shader1, GLuint shader2, int size1, glm::mat4 viewMatrixExternal, glm::mat4 projectionMatrixExternal, glm::vec3 cameraPositionExternal, glm::vec3 lightPositionExternal, glm::vec3 lightColorExternal, float ambientStrengthExternal, glm::vec3 ambientColorExternal, float specStrengthExternal, float specPhongExternal, float thetaExternal) {
  /*  theta += 0.1f;
    positionZ = -5.0f;*/
    //glm::vec3 CameraPos = glm::vec3(0, 0, 10.0f);
    //glm::vec3 WorldUp = glm::normalize(glm::vec3(0, 1.0f, 0));
    //glm::vec3 CameraCenter = glm::vec3(0, 0, 0);
    glm::mat4 viewMatrix = viewMatrixExternal;

    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glUseProgram(shader2);
    glm::mat4 sky_view = glm::mat4(1.0f);
    // To remove the position of the camera
    // Rotation camera for our skybox
    sky_view = glm::mat4(glm::mat3(viewMatrix));
    unsigned int sky_projectionLoc = glGetUniformLocation(shader2, "projection");
    glUniformMatrix4fv(sky_projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrixExternal));
    unsigned int sky_viewLoc = glGetUniformLocation(shader2, "view");
    glUniformMatrix4fv(sky_viewLoc, 1, GL_FALSE, glm::value_ptr(sky_view));
    glBindVertexArray(VAO2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    glUseProgram(shader1);
    glm::mat4 transformation_matrix = glm::mat4(1.0f);
    transformation_matrix = glm::translate(transformation_matrix, glm::vec3(positionX, positionY, positionZ));
    transformation_matrix = glm::scale(transformation_matrix, glm::vec3(scaleX, scaleY, scaleZ));
    transformation_matrix = glm::rotate(transformation_matrix, glm::radians(thetaExternal), glm::normalize(glm::vec3(rotationX, rotationY, rotationZ)));

    unsigned int lightPosLoc = glGetUniformLocation(shader1, "lightPos");
    glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPositionExternal));
    unsigned int lightColorLoc = glGetUniformLocation(shader1, "lightColor");
    glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColorExternal));
    unsigned int ambientStrLoc = glGetUniformLocation(shader1, "ambientStr");
    glUniform1f(ambientStrLoc, ambientStrengthExternal);
    unsigned int ambientColorLoc = glGetUniformLocation(shader1, "ambientColor");
    glUniform3fv(ambientColorLoc, 1, glm::value_ptr(ambientColorExternal));
    unsigned int cameraPosLoc = glGetUniformLocation(shader1, "cameraPos");
    glUniform3fv(cameraPosLoc, 1, glm::value_ptr(cameraPositionExternal));
    unsigned int specStrLoc = glGetUniformLocation(shader1, "specStr");
    glUniform1f(specStrLoc, specStrengthExternal);
    unsigned int specPhongLoc = glGetUniformLocation(shader1, "specPhong");
    glUniform1f(specPhongLoc, specPhongExternal);

    GLuint tex0Address = glGetUniformLocation(shader1, "tex0");
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(tex0Address, 0);

    unsigned int projectionLoc = glGetUniformLocation(shader1, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrixExternal));
    unsigned int viewLoc = glGetUniformLocation(shader1, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    unsigned int transformationLoc = glGetUniformLocation(shader1, "transform");
    glUniformMatrix4fv(transformationLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));

    glUseProgram(shader1);
    glBindVertexArray(VAO1);
    glDrawArrays(GL_TRIANGLES, 0, size1 / 8);
}
