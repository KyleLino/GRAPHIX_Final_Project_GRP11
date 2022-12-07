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

#include "Camera.h"
#include "Light.h"
#include "Model.h"

Camera cameraObject;
Light lightObject;
Model sampleObject;
Model sampleObject2;

float mod_x = 0.0f;
float mod_y = 0.0f;
float mod_z = -5.0f;
void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_D /*&& action == GLFW_PRESS*/) {
        mod_x += 10.0f;
    }
    if (key == GLFW_KEY_A /*&& action == GLFW_PRESS*/) {
        mod_x -= 10.0f;
    }

    if (key == GLFW_KEY_W /*&& action == GLFW_PRESS*/) {
        mod_z += 0.2f;
    }
    if (key == GLFW_KEY_S /*&& action == GLFW_PRESS*/) {
        mod_z -= 0.2f;
    }

    if (key == GLFW_KEY_UP /*&& action == GLFW_PRESS*/) {
        mod_y += 0.3f;
    }
    if (key == GLFW_KEY_DOWN /*&& action == GLFW_PRESS*/) {
        mod_y -= 0.3f;
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    float screenWidth = 600.0f;
    float screenHeight = 600.0f;
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
    unsigned char* tex_bytes2 = stbi_load("3D/partenza.jpg", &img_width2, &img_height2, &color_channels2, 0);
    GLuint texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width2, img_height2, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes2);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes2);

    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, Key_Callback);

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
        sampleObject.setPosition(0.0f, 0.0f, 0.0f);
        sampleObject.setRotation(0.0f, 1.0f, 0.0f);
        sampleObject.setScale(0.01f, 0.01f, 0.01f);
        sampleObject.drawObject(VAO, skyboxVAO, texture, skyboxTex, shaderProgram, skybox_shaderProgram, fullVertexData.size(), cameraObject.getViewMatrix(), cameraObject.getPerspective(), cameraObject.getCameraPosition(), lightObject.getLightPosition(), lightObject.getLightColor(), lightObject.getAmbientStrength(), lightObject.getAmbientColor(), lightObject.getSpecStrength(), lightObject.getSpecPhong(), theta);
        
        sampleObject2.setPosition(3.0f, 0.0f, 0.0f);
        sampleObject2.setRotation(0.0f, 1.0f, 0.0f);
        sampleObject2.setScale(2.0f, 2.0f, 2.0f);
        sampleObject2.drawObject(VAO2, skyboxVAO, texture2, skyboxTex, shaderProgram, skybox_shaderProgram, fullVertexData2.size(), cameraObject.getViewMatrix(), cameraObject.getPerspective(), cameraObject.getCameraPosition(), lightObject.getLightPosition(), lightObject.getLightColor(), lightObject.getAmbientStrength(), lightObject.getAmbientColor(), lightObject.getSpecStrength(), lightObject.getSpecPhong(), theta);
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