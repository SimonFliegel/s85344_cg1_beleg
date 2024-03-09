#version 450 core  // 420, 330 core , compatibility

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 lightPos; // center of sun
uniform vec3 lightColor;

// textures solar system
uniform sampler2D texSun; // 0
uniform sampler2D texMercury;
uniform sampler2D texVenus;
uniform sampler2D texEarth;
uniform sampler2D texMars;
uniform sampler2D texJupiter;
uniform sampler2D texSaturn;
uniform sampler2D texUranus;
uniform sampler2D texNeptune; // 8

uniform int sphereId; // 0-8

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

    if (sphereId == 0) {
        texColor = texture(texSun, texCoord);
    } else if (sphereId == 1) {
        texColor = texture(texMercury, texCoord);
    } else if (sphereId == 2) {
        texColor = texture(texVenus, texCoord);
    } else if (sphereId == 3) {
        texColor = texture(texEarth, texCoord);
    } else if (sphereId == 4) {
        texColor = texture(texMars, texCoord);
    } else if (sphereId == 5) {
        texColor = texture(texJupiter, texCoord);
    } else if (sphereId == 6) {
        texColor = texture(texSaturn, texCoord);
    } else if (sphereId == 7) {
        texColor = texture(texUranus, texCoord);
    } else if (sphereId == 8) {
        texColor = texture(texNeptune, texCoord);
    }
    
    if (sphereId == 0) { // light source
        lightResult = vec3(1.0f, 1.0f, 1.0f);
    }

    fragColor = texColor * vec4(lightResult, 1.0f);
}
