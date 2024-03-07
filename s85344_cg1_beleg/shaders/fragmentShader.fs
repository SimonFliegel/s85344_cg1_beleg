
#version 450 core  // 420, 330 core , compatibility

out vec4 fragColor;

in vec2 texCoord;

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

void main() {
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
    //fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
