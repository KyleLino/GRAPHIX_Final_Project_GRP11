#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include <iostream>

#include "Player.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Model.h"

Player playerObject;
Shader shaderObject;
Camera cameraObject;
Camera cameraObject2;
Light lightObject;
Model sampleObject;
Model sampleObject2;
Model sampleObject3;
Model sampleObject4;
Model sampleObject5;
Model sampleObject6;
Model sampleObject7;

float mod_x = 10.0f;
float mod_y = 0.0f;
float mod_z = 15.0f;
float mod_center = -20.0f;
float mod_a = 0.f;
float mod_b = 0.f;
float mod_position = 0.f;
float speed = 0.001f;
void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W /*&& action == GLFW_PRESS*/) {
        mod_x -= 0.5f;
        mod_y -= 0.5f;
        mod_z -= 0.5f;
        mod_center -= 0.5f;

        cameraObject.setCameraPosition(speed * cameraObject.getCameraCenter() + cameraObject.getCameraPosition());
    }
    if (key == GLFW_KEY_S /*&& action == GLFW_PRESS*/) {
        mod_x += 0.5f;
        mod_y += 0.5f;
        mod_z += 0.5f;
        mod_center -= 0.5f;

        cameraObject.setCameraPosition(speed * -cameraObject.getCameraCenter() + cameraObject.getCameraPosition());
    }

    if (key == GLFW_KEY_A /*&& action == GLFW_PRESS*/) {
       mod_a -= 0.5f;

       cameraObject.setCameraPosition(speed * -glm::normalize(glm::cross(cameraObject.getCameraCenter(), cameraObject.getWorldUp())) + cameraObject.getCameraPosition());
    }
    if (key == GLFW_KEY_D /*&& action == GLFW_PRESS*/) {
        mod_a += 0.5f;

        cameraObject.setCameraPosition(speed * glm::normalize(glm::cross(cameraObject.getCameraCenter(), cameraObject.getWorldUp())) + cameraObject.getCameraPosition());
    }

    if (key == GLFW_KEY_Q /*&& action == GLFW_PRESS*/) {
        playerObject.setPlayerDepth(mod_x += 0.01);
        std::cout << playerObject.getPlayerDepth() << "m" << std::endl;
        mod_b += 0.5f;
        mod_position += 0.5f;
    }
    if (key == GLFW_KEY_E /*&& action == GLFW_PRESS*/) {
        playerObject.setPlayerDepth(mod_x -= 0.01);
        std::cout << playerObject.getPlayerDepth() << "m" << std::endl;
        mod_b -= 0.5f;
        mod_position -= 0.5f;
    }
}

glm::vec3 cameraFront;
bool firstMouse = true;
float lastX = 800.0f / 2.0f;
float lastY = 800.0f / 2.0f;
float offzx = 0.0f;
float offzy = 0.0f;
float yaw = -90.0f;
float pitch = 0.0f;

// These are the mouse callback interaction
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    offzx = xoffset;
    offzy = yoffset;

    float sensitivity = 0.5f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    offzx = direction.x;
    offzy = direction.y;

    cameraFront = glm::normalize(direction);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    float screenWidth = 800.0f;
    float screenHeight = 800.0f;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    GLfloat UV[]{
        0.f, 1.f,
        0.f, 0.f,
        1.f, 1.f,
        1.f, 0.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 1.f,
        0.f, 0.f
    };

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGL();

    stbi_set_flip_vertically_on_load(true);
    int img_width, img_height, color_channels;
    unsigned char* tex_bytes = stbi_load("3D/Abstract.jpg", &img_width, &img_height, &color_channels, 0);
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes);

    int img_width2, img_height2, color_channels2;
    unsigned char* tex_bytes2 = stbi_load("3D/octopus_texture.jpeg", &img_width2, &img_height2, &color_channels2, 0);
    GLuint texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width2, img_height2, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes2);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes2);

    int img_width3, img_height3, color_channels3;
    unsigned char* tex_bytes3 = stbi_load("3D/OkounTexture.png", &img_width3, &img_height3, &color_channels3, 0);
    GLuint texture3;
    glGenTextures(1, &texture3);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture3);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width3, img_height3, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_bytes3);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes3);

    int img_width4, img_height4, color_channels4;
    unsigned char* tex_bytes4 = stbi_load("3D/wood.jpg", &img_width4, &img_height4, &color_channels4, 0);
    GLuint texture4;
    glGenTextures(1, &texture4);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width4, img_height4, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes4);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes4);

    int img_width5, img_height5, color_channels5;
    unsigned char* tex_bytes5 = stbi_load("3D/texture0.jpg", &img_width5, &img_height5, &color_channels5, 0);
    GLuint texture5;
    glGenTextures(1, &texture5);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture5);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width5, img_height5, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes5);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes5);

    int img_width6, img_height6, color_channels6;
    unsigned char* tex_bytes6 = stbi_load("3D/gws_texture.jpeg", &img_width6, &img_height6, &color_channels6, 0);
    GLuint texture6;
    glGenTextures(1, &texture6);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture6);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width6, img_height6, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes6);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes6);

    int img_width7, img_height7, color_channels7;
    unsigned char* tex_bytes7 = stbi_load("3D/texture_shark.jpg", &img_width7, &img_height7, &color_channels7, 0);
    GLuint texture7;
    glGenTextures(1, &texture7);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture7);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width7, img_height7, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes7);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes7);

    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, Key_Callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();
    std::fstream fragSrc("Shaders/sample.frag");
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &v, NULL);
    glCompileShader(vertShader);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    std::fstream skybox_vertSrc("Shaders/skybox.vert");
    std::stringstream skybox_vertBuff;
    skybox_vertBuff << skybox_vertSrc.rdbuf();
    std::string skybox_vertS = skybox_vertBuff.str();
    const char* skybox_v = skybox_vertS.c_str();
    std::fstream skybox_fragSrc("Shaders/skybox.frag");
    std::stringstream skybox_fragBuff;
    skybox_fragBuff << skybox_fragSrc.rdbuf();
    std::string skybox_fragS = skybox_fragBuff.str();
    const char* skybox_f = skybox_fragS.c_str();
    GLuint skybox_vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(skybox_vertShader, 1, &skybox_v, NULL);
    glCompileShader(skybox_vertShader);
    GLuint skybox_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(skybox_fragShader, 1, &skybox_f, NULL);
    glCompileShader(skybox_fragShader);
    GLuint skybox_shaderProgram = glCreateProgram();
    glAttachShader(skybox_shaderProgram, skybox_vertShader);
    glAttachShader(skybox_shaderProgram, skybox_fragShader);
    glLinkProgram(skybox_shaderProgram);

        /*
      7--------6
     /|       /|
    4--------5 |
    | |      | |
    | 3------|-2
    |/       |/
    0--------1
    */
    //Vertices for the cube
    float skyboxVertices[]{
        -1.f, -1.f, 1.f, //0
        1.f, -1.f, 1.f,  //1
        1.f, -1.f, -1.f, //2
        -1.f, -1.f, -1.f,//3
        -1.f, 1.f, 1.f,  //4
        1.f, 1.f, 1.f,   //5
        1.f, 1.f, -1.f,  //6
        -1.f, 1.f, -1.f  //7
    };

    //Skybox Indices
    unsigned int skyboxIndices[]{
        1,2,6,
        6,5,1,

        0,4,7,
        7,3,0,

        4,5,6,
        6,7,4,

        0,3,2,
        2,1,0,

        0,1,5,
        5,4,0,

        3,7,6,
        6,2,3
    };

    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);

    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &skyboxIndices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    std::string facesSkybox[]{
        "Skybox/uw_rt.jpg",
        "Skybox/uw_lf.jpg",
        "Skybox/uw_up.jpg",
        "Skybox/uw_dn.jpg",
        "Skybox/uw_ft.jpg",
        "Skybox/uw_bk.jpg"
    };

    unsigned int skyboxTex;

    glGenTextures(1, &skyboxTex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++) {
        int w, h, skyCChannel;
        stbi_set_flip_vertically_on_load(false);

        unsigned char* data = stbi_load(
            facesSkybox[i].c_str(),
            &w,
            &h,
            &skyCChannel,
            0
        );

        if (data) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                w,
                h,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
        }
    }

    std::string path = "3D/Mouse.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning, error;
    tinyobj::attrib_t attributes;
    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &materials,
        &warning,
        &error,
        path.c_str()
    );
    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        mesh_indices.push_back(
            shapes[0].mesh.indices[i].vertex_index
        );
    }
    std::vector<GLfloat> fullVertexData;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData = shapes[0].mesh.indices[i];
        int vertexIndex = vData.vertex_index * 3;
        int normalsIndex = vData.normal_index * 3;
        int uvIndex = vData.texcoord_index * 2;

        fullVertexData.push_back(attributes.vertices[vertexIndex]);
        fullVertexData.push_back(attributes.vertices[vertexIndex+1]);
        fullVertexData.push_back(attributes.vertices[vertexIndex+2]);

        fullVertexData.push_back(attributes.normals[normalsIndex]);
        fullVertexData.push_back(attributes.normals[normalsIndex + 1]);
        fullVertexData.push_back(attributes.normals[normalsIndex + 2]);

        fullVertexData.push_back(attributes.texcoords[uvIndex]);
        fullVertexData.push_back(attributes.texcoords[uvIndex+1]);
    }

    std::string path2 = "3D/Octopus.obj";
    std::vector<tinyobj::shape_t> shapes2;
    std::vector<tinyobj::material_t> materials2;
    std::string warning2, error2;
    tinyobj::attrib_t attributes2;
    bool success2 = tinyobj::LoadObj(
        &attributes2,
        &shapes2,
        &materials2,
        &warning2,
        &error2,
        path2.c_str()
    );
    std::vector<GLuint> mesh_indices2;
    for (int i = 0; i < shapes2[0].mesh.indices.size(); i++) {
        mesh_indices2.push_back(
            shapes2[0].mesh.indices[i].vertex_index
        );
    }
    std::vector<GLfloat> fullVertexData2;
    for (int i = 0; i < shapes2[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData2 = shapes2[0].mesh.indices[i];
        int vertexIndex2 = vData2.vertex_index * 3;
        int normalsIndex2 = vData2.normal_index * 3;
        int uvIndex2 = vData2.texcoord_index * 2;

        fullVertexData2.push_back(attributes2.vertices[vertexIndex2]);
        fullVertexData2.push_back(attributes2.vertices[vertexIndex2 + 1]);
        fullVertexData2.push_back(attributes2.vertices[vertexIndex2 + 2]);

        fullVertexData2.push_back(attributes2.normals[normalsIndex2]);
        fullVertexData2.push_back(attributes2.normals[normalsIndex2 + 1]);
        fullVertexData2.push_back(attributes2.normals[normalsIndex2 + 2]);

        fullVertexData2.push_back(attributes.texcoords[uvIndex2]);
        fullVertexData2.push_back(attributes.texcoords[uvIndex2 + 1]);
    }

    std::string path3 = "3D/bass.obj";
    std::vector<tinyobj::shape_t> shapes3;
    std::vector<tinyobj::material_t> materials3;
    std::string warning3, error3;
    tinyobj::attrib_t attributes3;
    bool success3 = tinyobj::LoadObj(
        &attributes3,
        &shapes3,
        &materials3,
        &warning3,
        &error3,
        path3.c_str()
    );
    std::vector<GLuint> mesh_indices3;
    for (int i = 0; i < shapes3[0].mesh.indices.size(); i++) {
        mesh_indices3.push_back(
            shapes3[0].mesh.indices[i].vertex_index
        );
    }
    std::vector<GLfloat> fullVertexData3;
    for (int i = 0; i < shapes3[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData3 = shapes3[0].mesh.indices[i];
        int vertexIndex3 = vData3.vertex_index * 3;
        int normalsIndex3 = vData3.normal_index * 3;
        int uvIndex3 = vData3.texcoord_index * 2;

        fullVertexData3.push_back(attributes3.vertices[vertexIndex3]);
        fullVertexData3.push_back(attributes3.vertices[vertexIndex3 + 1]);
        fullVertexData3.push_back(attributes3.vertices[vertexIndex3 + 2]);

        fullVertexData3.push_back(attributes3.normals[normalsIndex3]);
        fullVertexData3.push_back(attributes3.normals[normalsIndex3 + 1]);
        fullVertexData3.push_back(attributes3.normals[normalsIndex3 + 2]);

        fullVertexData3.push_back(attributes3.texcoords[uvIndex3]);
        fullVertexData3.push_back(attributes3.texcoords[uvIndex3 + 1]);
    }

    std::string path4 = "3D/boat.obj";
    std::vector<tinyobj::shape_t> shapes4;
    std::vector<tinyobj::material_t> materials4;
    std::string warning4, error4;
    tinyobj::attrib_t attributes4;
    bool success4 = tinyobj::LoadObj(
        &attributes4,
        &shapes4,
        &materials4,
        &warning4,
        &error4,
        path4.c_str()
    );
    std::vector<GLuint> mesh_indices4;
    for (int i = 0; i < shapes4[0].mesh.indices.size(); i++) {
        mesh_indices4.push_back(
            shapes4[0].mesh.indices[i].vertex_index
        );
    }
    std::vector<GLfloat> fullVertexData4;
    for (int i = 0; i < shapes4[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData4 = shapes4[0].mesh.indices[i];
        int vertexIndex4 = vData4.vertex_index * 3;
        int normalsIndex4 = vData4.normal_index * 3;
        int uvIndex4 = vData4.texcoord_index * 2;

        fullVertexData4.push_back(attributes4.vertices[vertexIndex4]);
        fullVertexData4.push_back(attributes4.vertices[vertexIndex4 + 1]);
        fullVertexData4.push_back(attributes4.vertices[vertexIndex4 + 2]);

        fullVertexData4.push_back(attributes4.normals[normalsIndex4]);
        fullVertexData4.push_back(attributes4.normals[normalsIndex4 + 1]);
        fullVertexData4.push_back(attributes4.normals[normalsIndex4 + 2]);

        fullVertexData4.push_back(attributes4.texcoords[uvIndex4]);
        fullVertexData4.push_back(attributes4.texcoords[uvIndex4 + 1]);
    }

    std::string path5 = "3D/bamboo_shark.obj";
    std::vector<tinyobj::shape_t> shapes5;
    std::vector<tinyobj::material_t> materials5;
    std::string warning5, error5;
    tinyobj::attrib_t attributes5;
    bool success5 = tinyobj::LoadObj(
        &attributes5,
        &shapes5,
        &materials5,
        &warning5,
        &error5,
        path5.c_str()
    );
    std::vector<GLuint> mesh_indices5;
    for (int i = 0; i < shapes5[0].mesh.indices.size(); i++) {
        mesh_indices5.push_back(
            shapes5[0].mesh.indices[i].vertex_index
        );
    }
    std::vector<GLfloat> fullVertexData5;
    for (int i = 0; i < shapes5[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData5 = shapes5[0].mesh.indices[i];
        int vertexIndex5 = vData5.vertex_index * 3;
        int normalsIndex5 = vData5.normal_index * 3;
        int uvIndex5 = vData5.texcoord_index * 2;

        fullVertexData5.push_back(attributes5.vertices[vertexIndex5]);
        fullVertexData5.push_back(attributes5.vertices[vertexIndex5 + 1]);
        fullVertexData5.push_back(attributes5.vertices[vertexIndex5 + 2]);

        fullVertexData5.push_back(attributes5.normals[normalsIndex5]);
        fullVertexData5.push_back(attributes5.normals[normalsIndex5 + 1]);
        fullVertexData5.push_back(attributes5.normals[normalsIndex5 + 2]);

        fullVertexData5.push_back(attributes5.texcoords[uvIndex5]);
        fullVertexData5.push_back(attributes5.texcoords[uvIndex5 + 1]);
    }

    std::string path6 = "3D/person.obj";
    std::vector<tinyobj::shape_t> shapes6;
    std::vector<tinyobj::material_t> materials6;
    std::string warning6, error6;
    tinyobj::attrib_t attributes6;
    bool success6 = tinyobj::LoadObj(
        &attributes6,
        &shapes6,
        &materials6,
        &warning6,
        &error6,
        path6.c_str()
    );
    std::vector<GLuint> mesh_indices6;
    for (int i = 0; i < shapes6[0].mesh.indices.size(); i++) {
        mesh_indices6.push_back(
            shapes6[0].mesh.indices[i].vertex_index
        );
    }
    std::vector<GLfloat> fullVertexData6;
    for (int i = 0; i < shapes6[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData6 = shapes6[0].mesh.indices[i];
        int vertexIndex6 = vData6.vertex_index * 3;
        int normalsIndex6 = vData6.normal_index * 3;
        int uvIndex6 = vData6.texcoord_index * 2;

        fullVertexData6.push_back(attributes6.vertices[vertexIndex6]);
        fullVertexData6.push_back(attributes6.vertices[vertexIndex6 + 1]);
        fullVertexData6.push_back(attributes6.vertices[vertexIndex6 + 2]);

        fullVertexData6.push_back(attributes6.normals[normalsIndex6]);
        fullVertexData6.push_back(attributes6.normals[normalsIndex6 + 1]);
        fullVertexData6.push_back(attributes6.normals[normalsIndex6 + 2]);

        fullVertexData6.push_back(attributes6.texcoords[uvIndex6]);
        fullVertexData6.push_back(attributes6.texcoords[uvIndex6 + 1]);
    }

    std::string path7 = "3D/Shark.obj";
    std::vector<tinyobj::shape_t> shapes7;
    std::vector<tinyobj::material_t> materials7;
    std::string warning7, error7;
    tinyobj::attrib_t attributes7;
    bool success7 = tinyobj::LoadObj(
        &attributes7,
        &shapes7,
        &materials7,
        &warning7,
        &error7,
        path7.c_str()
    );
    std::vector<GLuint> mesh_indices7;
    for (int i = 0; i < shapes7[0].mesh.indices.size(); i++) {
        mesh_indices7.push_back(
            shapes7[0].mesh.indices[i].vertex_index
        );
    }
    std::vector<GLfloat> fullVertexData7;
    for (int i = 0; i < shapes7[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData7 = shapes7[0].mesh.indices[i];
        int vertexIndex7 = vData7.vertex_index * 3;
        int normalsIndex7 = vData7.normal_index * 3;
        int uvIndex7 = vData7.texcoord_index * 2;

        fullVertexData7.push_back(attributes7.vertices[vertexIndex7]);
        fullVertexData7.push_back(attributes7.vertices[vertexIndex7 + 1]);
        fullVertexData7.push_back(attributes7.vertices[vertexIndex7 + 2]);

        fullVertexData7.push_back(attributes7.normals[normalsIndex7]);
        fullVertexData7.push_back(attributes7.normals[normalsIndex7 + 1]);
        fullVertexData7.push_back(attributes7.normals[normalsIndex7 + 2]);

        fullVertexData7.push_back(attributes7.texcoords[uvIndex7]);
        fullVertexData7.push_back(attributes7.texcoords[uvIndex7 + 1]);
    }

    GLfloat vertices[]{
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    GLuint indices[]{
        0, 1, 2
    };
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * fullVertexData.size(),
        fullVertexData.data(),
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );
    GLintptr normPtr = 3 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr
    );
    GLintptr uvPtr = 6 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint VAO2, VBO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData2.size(),
        fullVertexData2.data(),
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );
    GLintptr normPtr2 = 3 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr2
    );
    GLintptr uvPtr2 = 6 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr2
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint VAO3, VBO3;
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);
    glBindVertexArray(VAO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData3.size(),
        fullVertexData3.data(),
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );
    GLintptr normPtr3 = 3 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr3
    );
    GLintptr uvPtr3 = 6 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr3
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint VAO4, VBO4;
    glGenVertexArrays(1, &VAO4);
    glGenBuffers(1, &VBO4);
    glBindVertexArray(VAO4);
    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData4.size(),
        fullVertexData4.data(),
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );
    GLintptr normPtr4 = 3 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr4
    );
    GLintptr uvPtr4 = 6 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr4
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint VAO5, VBO5;
    glGenVertexArrays(1, &VAO5);
    glGenBuffers(1, &VBO5);
    glBindVertexArray(VAO5);
    glBindBuffer(GL_ARRAY_BUFFER, VBO5);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData5.size(),
        fullVertexData5.data(),
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );
    GLintptr normPtr5 = 3 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr5
    );
    GLintptr uvPtr5 = 6 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr5
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint VAO6, VBO6;
    glGenVertexArrays(1, &VAO6);
    glGenBuffers(1, &VBO6);
    glBindVertexArray(VAO6);
    glBindBuffer(GL_ARRAY_BUFFER, VBO6);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData6.size(),
        fullVertexData6.data(),
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );
    GLintptr normPtr6 = 3 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr6
    );
    GLintptr uvPtr6 = 6 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr6
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint VAO7, VBO7;
    glGenVertexArrays(1, &VAO7);
    glGenBuffers(1, &VBO7);
    glBindVertexArray(VAO7);
    glBindBuffer(GL_ARRAY_BUFFER, VBO7);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT)* fullVertexData7.size(),
        fullVertexData7.data(),
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)0
    );
    GLintptr normPtr7 = 3 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normPtr7
    );
    GLintptr uvPtr7 = 6 * sizeof(GL_FLOAT);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr7
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat3 identity_matrix3 = glm::mat3(1.0f);
    glm::mat4 identity_matrix4 = glm::mat4(1.0f);
    float x, y, z;
    x = y = z = 0.0f;
    float scale_x, scale_y, scale_z;
    scale_x = scale_y = scale_z = 0.01f;
    float rot_x, rot_y, rot_z;
    rot_x = rot_y = rot_z = 0.0f;
    rot_y = 1.0f;
    float theta = 0.0f;
    z = -5.0f;
    glm::mat4 projection_matrix = glm::perspective(glm::radians(60.0f), screenHeight/screenWidth, 0.1f, 100.0f);

    glm::vec3 lightPos = glm::vec3(-10, 3, 0);
    glm::vec3 lightColor = glm::vec3(1, 1, 1);

    float ambientStr = 0.1f;
    glm::vec3 ambientColor = lightColor;

    float specStr = 0.5f;
    float specPhong = 16.0f;

    cameraObject.setScreenWidth(screenWidth);
    cameraObject.setScreenHeight(screenHeight);
    cameraObject.setPerspective();
    cameraObject.setCameraPosition(glm::vec3(0.0f,0.0f,10.0f));
    cameraObject.setWorldUp(glm::vec3(0.0f, 1.0f, 0.0f));
    cameraObject.setCameraCenter(glm::vec3(0.0f, 0.0f, 0.0f));
    cameraObject.setViewMatrix();

    lightObject.setLightPosition(glm::vec3(-10, 3, 0));
    lightObject.setLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
    lightObject.setAmbientStrength(0.1f);
    lightObject.setAmbientColor(glm::vec3(1.0f, 1.0f, 1.0f));
    lightObject.setSpecStrength(0.5f);
    lightObject.setSpecPhong(16.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        theta += 0.1f;

        lightObject.setLightColor(glm::vec3(0.0f, 1.0f, 0.0f));
        lightObject.setAmbientColor(glm::vec3(0.0f, 1.0f, 0.0f));
        cameraObject.setCameraPosition(glm::vec3(mod_a, mod_b, mod_x));
        cameraObject.setCameraCenter(glm::vec3(mod_a,mod_b, mod_center));
        lightObject.setLightPosition(glm::vec3(mod_a, mod_b, mod_z));

        cameraObject.setCameraCenter(glm::vec3(mod_a, mod_b, mod_x) + cameraFront);
        //cameraObject.setCameraPosition(glm::vec3(mod_a, mod_b, mod_x) - cameraFront);
        cameraObject.setViewMatrix();

        sampleObject.setPosition(mod_a, mod_b, mod_y);
        sampleObject.setRotation(0.0f, 1.0f, 0.0f);
        sampleObject.setScale(1.0f, 1.0f, 1.0f);
        sampleObject.drawObject(VAO4, skyboxVAO, texture4, skyboxTex, shaderProgram, skybox_shaderProgram, fullVertexData4.size(), cameraObject.getViewMatrix(), cameraObject.getPerspective(), cameraObject.getCameraPosition(), lightObject.getLightPosition(), lightObject.getLightColor(), lightObject.getAmbientStrength(), lightObject.getAmbientColor(), lightObject.getSpecStrength(), lightObject.getSpecPhong(), 90.0f);

        sampleObject2.setPosition(3.0f, 0.0f, 0.0f);
        sampleObject2.setRotation(0.0f, 1.0f, 0.0f);
        sampleObject2.setScale(1.0f, 1.0f, 1.0f);
        sampleObject2.drawObject(VAO2, skyboxVAO, texture2, skyboxTex, shaderProgram, skybox_shaderProgram, fullVertexData2.size(), cameraObject.getViewMatrix(), cameraObject.getPerspective(), cameraObject.getCameraPosition(), lightObject.getLightPosition(), lightObject.getLightColor(), lightObject.getAmbientStrength(), lightObject.getAmbientColor(), lightObject.getSpecStrength(), lightObject.getSpecPhong(), theta);
        
        sampleObject3.setPosition(-3.0f, 0.0f, -20.0f);
        sampleObject3.setRotation(0.0f, 1.0f, 0.0f);
        sampleObject3.setScale(0.5f, 0.5f, 0.5f);
        sampleObject3.drawObject(VAO3, skyboxVAO, texture3, skyboxTex, shaderProgram, skybox_shaderProgram, fullVertexData3.size(), cameraObject.getViewMatrix(), cameraObject.getPerspective(), cameraObject.getCameraPosition(), lightObject.getLightPosition(), lightObject.getLightColor(), lightObject.getAmbientStrength(), lightObject.getAmbientColor(), lightObject.getSpecStrength(), lightObject.getSpecPhong(), theta);

        sampleObject4.setPosition(3.0f, 3.0f, -40.0f);
        sampleObject4.setRotation(0.0f, 1.0f, 0.0f);
        sampleObject4.setScale(0.01f, 0.01f, 0.01f);
        sampleObject4.drawObject(VAO, skyboxVAO, texture, skyboxTex, shaderProgram, skybox_shaderProgram, fullVertexData.size(), cameraObject.getViewMatrix(), cameraObject.getPerspective(), cameraObject.getCameraPosition(), lightObject.getLightPosition(), lightObject.getLightColor(), lightObject.getAmbientStrength(), lightObject.getAmbientColor(), lightObject.getSpecStrength(), lightObject.getSpecPhong(), theta);

        sampleObject5.setPosition(-3.0f, 3.0f, -60.0f);
        sampleObject5.setRotation(0.0f, 1.0f, 0.0f);
        sampleObject5.setScale(0.01f, 0.01f, 0.01f);
        sampleObject5.drawObject(VAO5, skyboxVAO, texture7, skyboxTex, shaderProgram, skybox_shaderProgram, fullVertexData5.size(), cameraObject.getViewMatrix(), cameraObject.getPerspective(), cameraObject.getCameraPosition(), lightObject.getLightPosition(), lightObject.getLightColor(), lightObject.getAmbientStrength(), lightObject.getAmbientColor(), lightObject.getSpecStrength(), lightObject.getSpecPhong(), theta);

        sampleObject6.setPosition(3.0f, -3.0f, -80.0f);
        sampleObject6.setRotation(0.0f, 1.0f, 0.0f);
        sampleObject6.setScale(1.01f, 1.01f, 1.01f);
        sampleObject6.drawObject(VAO6, skyboxVAO, texture5, skyboxTex, shaderProgram, skybox_shaderProgram, fullVertexData6.size(), cameraObject.getViewMatrix(), cameraObject.getPerspective(), cameraObject.getCameraPosition(), lightObject.getLightPosition(), lightObject.getLightColor(), lightObject.getAmbientStrength(), lightObject.getAmbientColor(), lightObject.getSpecStrength(), lightObject.getSpecPhong(), theta);

        sampleObject6.setPosition(-3.0f, -3.0f, -100.0f);
        sampleObject6.setRotation(0.0f, 1.0f, 0.0f);
        sampleObject6.setScale(0.05f, 0.05f, 0.05f);
        sampleObject6.drawObject(VAO7, skyboxVAO, texture6, skyboxTex, shaderProgram, skybox_shaderProgram, fullVertexData7.size(), cameraObject.getViewMatrix(), cameraObject.getPerspective(), cameraObject.getCameraPosition(), lightObject.getLightPosition(), lightObject.getLightColor(), lightObject.getAmbientStrength(), lightObject.getAmbientColor(), lightObject.getSpecStrength(), lightObject.getSpecPhong(), theta);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}