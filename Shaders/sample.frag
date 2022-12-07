// Point Light

#version 330 core

uniform sampler2D tex0;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform float ambientStr;
uniform vec3 ambientColor;

uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;

in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;

out vec4 FragColor;

void main(){
    //FragColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);

    // Declare constant, linear, and quadtratic variables
    float constant=0.01f;
    float linear=0.01f;
    float quadratic=0.01f;  

    vec3 normal = normalize(normCoord);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(
        dot(normal, lightDir), 0.0f
    );

    vec3 diffuse = diff * lightColor;

    vec3 ambientCol = ambientStr * ambientColor;

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(
        max(
            dot(reflectDir, viewDir), 0.1f
        ),
    specPhong);

    vec3 specCol = spec * specStr * lightColor;

    // Computes for the distance
    float distance = length(lightPos - fragPos);

    // Computes for the light attenuation
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    // Applies the attenuation
    specCol *= attenuation;
    diffuse *= attenuation;
    ambientCol *= attenuation;

    FragColor = vec4(specCol + diffuse + ambientCol, 1.0f) * texture(tex0, texCoord);
}