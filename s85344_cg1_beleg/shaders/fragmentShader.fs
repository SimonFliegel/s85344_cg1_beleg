
#version 450 core  // 420, 330 core , compatibility


in vec2 texCoord;

//uniform vec3 lightPos; // center of sun
//uniform vec3 lightColor;

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
    //float ambientStrength = 0.01f;
    //vec3 


    if (sphereId == 0) {
        fragColor = texture(texSun, texCoord);
    } else if (sphereId == 1) {
        fragColor = texture(texMercury, texCoord);
    } else if (sphereId == 2) {
        fragColor = texture(texVenus, texCoord);
    } else if (sphereId == 3) {
        fragColor = texture(texEarth, texCoord);
    } else if (sphereId == 4) {
        fragColor = texture(texMars, texCoord);
    } else if (sphereId == 5) {
        fragColor = texture(texJupiter, texCoord);
    } else if (sphereId == 6) {
        fragColor = texture(texSaturn, texCoord);
    } else if (sphereId == 7) {
        fragColor = texture(texUranus, texCoord);
    } else if (sphereId == 8) {
        fragColor = texture(texNeptune, texCoord);
    }
}
