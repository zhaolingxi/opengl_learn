@shader_vertex 
@shader_vertex_uid=trangle01_vs
#version 400 core
layout (location=0) in vec3 aPos;
void main()
{
	gl_Postion=vec4(aPos.x,aPos.y,aPos.z,1.0);
}
@shader_end

@shader_vertex
@shader_vertex_uid=trangle02_vs
#version 400 core
layout (location=0) in vec3 aPos;
void main()
{
	gl_Postion=vec4(aPos.x,aPos.y,aPos.z,2.0);
}
@shader_end

@shader_fragment
@shader_fragment_uid=trangle01_fs
#version 400 core
out vec4 FragColor;
void main()
{
    FragColor= vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
@shader_end