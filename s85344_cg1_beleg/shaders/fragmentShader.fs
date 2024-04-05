#version 450 core  // 420, 330 core , compatibility

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 lightPos; // center of sun
uniform vec3 lightColor;

uniform sampler2D texWood;


out vec4 fragColor;

void main() {
    // ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f); // ?
    vec3 diffuse = diff * lightColor;

    vec3 lightResult = ambient + diffuse;

    vec4 texColor;
    texColor = texture(texWood, texCoord);

    fragColor = texColor * vec4(lightResult, 1.0f);

}
