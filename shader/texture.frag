#version 330 core
out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 color;            
    float diffuseIntensity;     
    float specularIntensity;    
};
uniform vec3 ambientColor;  // 环境光颜色
uniform float ambientIntensity;  // 环境光强度

uniform vec3 viewPos;
uniform Material material;

// Maximum number of lights
const int MAX_LIGHTS = 4;
uniform int numLights;
uniform Light lights[MAX_LIGHTS];

void main()
{
    vec3 ambient = ambientColor * ambientIntensity;

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; ++i) {
        // Diffuse
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = lights[i].color * (diff * material.diffuse * lights[i].diffuseIntensity);

        // Specular
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = lights[i].color * (spec * material.specular * lights[i].specularIntensity);

        // 综合光照
        result += diffuse + specular;
    }

    // 加上环境光照
    result += ambient;

    // 使用材质的漫反射纹理
    vec4 texColor = texture(material.diffuse, TexCoords);
    FragColor = vec4(texColor.rgb * result, texColor.a);
}