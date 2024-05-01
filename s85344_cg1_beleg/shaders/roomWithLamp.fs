#version 450 core  // 420, 330 core , compatibility

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 viewPos;

// primary light source (lamp)
uniform vec3 primaryLightPos;
uniform vec3 primaryLightColor;

// external light source (sun)
uniform vec3 externalLightPos; // external light source position
uniform vec3 externalLightColor;

// textures room
uniform sampler2D texWall; // 10
uniform sampler2D texFloor; // 11
uniform sampler2D texMetal; // 20
uniform sampler2D texLight; // 21

uniform int objectId; // 0: walls, 1: floor, 2: lamp stand, 3: light bulb (light source)

out vec4 fragColor;

void main() {
    // @see https://learnopengl.com/Lighting/Basic-Lighting

    // ambient
    float ambientStrength = 0.5f; // when primary light is on
    
    float primaryDiffuseStrength = 1.0f;
    float primarySpecularStrength = 0.6f;

    float externalDiffuseStrength = 0.2f;
    float externalSpecularStrength = 0.25f;

    vec3 ambient = ambientStrength * primaryLightColor;

    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    // diffuse (primary light source)
    vec3 lightDir = normalize(primaryLightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * primaryLightColor * primaryDiffuseStrength;

    // specular (primary light source)
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = primarySpecularStrength * spec * primaryLightColor;

    vec3 primaryLightResult = diffuse + specular;
    
    // external light source
    vec3 externalLightResult = vec3(0.0f, 0.0f, 0.0f); // default value for non-existing external light source
    if (externalLightColor != vec3(0.0f, 0.0f, 0.0f)) // external light source is set
    {
        // diffuse (external light source)
        vec3 externalLightDir = normalize(externalLightPos - fragPos);
        float externalDiff = max(dot(norm, externalLightDir), 0.0f);
        vec3 externalDiffuse = externalDiff * externalLightColor * externalDiffuseStrength;

        // specular (external light source)
        vec3 externalReflectDir = reflect(-externalLightDir, norm);
        float externalSpec = pow(max(dot(viewDir, externalReflectDir), 0.0), 32);
        vec3 externalSpecular = externalSpec * externalLightColor * externalSpecularStrength;

        externalLightResult = externalDiffuse + externalSpecular;
    }

        
    vec3 lightResult = ambient + primaryLightResult + externalLightResult;
    
    vec4 texColor;

    if (objectId == 0)
    {
        texColor = texture(texWall, texCoord);
    }
    else if (objectId == 1) 
    {
        texColor = texture(texFloor, texCoord);
    }
    else if (objectId == 2)
    {
        texColor = texture(texMetal, texCoord);
    }
    else if (objectId == 3) 
    {
        texColor = texture(texLight, texCoord);
    } 
    else
    {
        texColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); // red (debugging)
    }
    
    if (objectId == 3) // primary light source
    { 
        if (primaryLightColor != vec3(0.0f, 0.0f, 0.0f)) 
        {
            lightResult = primaryLightColor; // when primary light is on
        } else {
            lightResult = lightResult; // when primary light is off
        }
    }

    fragColor = texColor * vec4(lightResult, 1.0f);
}
