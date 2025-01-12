@shader_vertex 
@shader_vertex_uid=trangle01_vs
#version 330 core
layout (location=0) in vec3 aPos;
void main()
{
	gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);
}
@shader_end

@shader_vertex
@shader_vertex_uid=trangle02_vs
#version 330 core
layout (location=0) in vec3 aPos;
out vec4 vertexColor;
void main()
{
	gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);
	vertexColor= vec4(0.5, 0.0, 0.0, 1.0);
}
@shader_end


@shader_vertex
@shader_vertex_uid=trangle03_vs
#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
out vec3 vertexColor;
void main()
{
	gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);
	vertexColor= aColor;
}
@shader_end


@shader_vertex
@shader_vertex_uid=textureBox01_vs
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec3 vertexColor;
out vec2 TexCoord;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aColor;
    TexCoord = aTexCoord;
}
@shader_end


@shader_vertex
@shader_vertex_uid=textureBoxRotate01_vs
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
uniform mat4 transform;
out vec3 vertexColor;
out vec2 TexCoord;
void main()
{
    gl_Position = transform*vec4(aPos, 1.0);
    vertexColor = aColor;
    TexCoord = aTexCoord;
}
@shader_end


@shader_vertex
@shader_vertex_uid=modelLoad01_vs
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
out vec2 TexCoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
@shader_end
