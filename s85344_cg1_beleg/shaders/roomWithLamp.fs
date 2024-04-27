#version 450 core  // 420, 330 core , compatibility

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 lightPos; // center of sun
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform sampler2D texWood; // 10
uniform sampler2D texMetal; // 11
uniform sampler2D texLight; // 12

uniform int objectId; // 0: room, 1: lampstand, 2: lightbulb (light source)

out vec4 fragColor;

void main() {
    // @see https://learnopengl.com/Lighting/Basic-Lighting

    // ambient
    float ambientStrength = 0.1f;
    float specularStrength = 0.6f;

    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f); // ?
    vec3 diffuse = diff * lightColor;

    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
        
    vec3 lightResult = ambient + diffuse + specular;
    
    vec4 texColor;

    if (objectId == 0) {
        texColor = texture(texWood, texCoord);
    } else if (objectId == 1) {
        texColor = texture(texMetal, texCoord);
    } else if (objectId == 2) {
        texColor = texture(texLight, texCoord);
    } else {
        texColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); // red (debugging)
    }
    
    if (objectId == 2) { // light source
        lightResult = lightColor;
    }

    fragColor = texColor * vec4(lightResult, 1.0f);
}
