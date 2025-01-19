@shader_fragment
@shader_fragment_uid=trangle01_fs
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor= vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
@shader_end

@shader_fragment
@shader_fragment_uid=trangle02_fs
#version 330 core
in vec4 vertexColor;
out vec4 FragColor;
void main()
{
    FragColor= vertexColor;
}
@shader_end


@shader_fragment
@shader_fragment_uid=trangle03_fs
#version 330 core
uniform vec4 uniColor;  
out vec4 FragColor;
void main()
{
    FragColor= uniColor;
}
@shader_end


@shader_fragment
@shader_fragment_uid=trangle04_fs
#version 330 core
in vec3 vertexColor;  
out vec4 FragColor;
void main()
{
    FragColor=vec4(vertexColor,1.0f);
}
@shader_end


@shader_fragment
@shader_fragment_uid=texturebox01_fs
#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;
void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(vertexColor, 1.0);
}
@shader_end


@shader_fragment
@shader_fragment_uid=textureboxrotate02_fs
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
@shader_end


@shader_fragment
@shader_fragment_uid=materials01_fs
#version 330 core
out vec4 FragColor;
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
in vec3 FragPos;  
in vec3 Normal;  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient;
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 
@shader_end


@shader_fragment
@shader_fragment_uid=lightcube01_fs
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0); // set all 4 vector values to 1.0
}
@shader_end



@shader_fragment
@shader_fragment_uid=modelLoad01_fs
#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D texture_diffuse1;
void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
}
@shader_end
