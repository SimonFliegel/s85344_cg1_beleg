#version 450 core  // 420, 330 core , compatibility

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 lightPos; // center of sun
uniform vec3 lightColor;

uniform sampler2D texWood; // 10
uniform sampler2D texMetal; // 11
uniform sampler2D texLight; // 12

uniform int objectId; // 0: room, 1: lampstand, 2: lightbulb

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

    if (objectId == 0) {
        texColor = texture(texWood, texCoord);
    } else if (objectId == 1) {
        texColor = texture(texMetal, texCoord);
    } else if (objectId == 2) {
        texColor = texture(texLight, texCoord);
    }

    //fragColor = texColor * vec4(lightResult, 1.0f);

    fragColor = texColor;

    //fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); // red (debugging)

}
