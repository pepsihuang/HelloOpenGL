//顶点着色器代码
#version 330 core
layout (location = 0) in vec3 aPos;

//layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float xoffset;

void main()
{

	vec3 pos = aPos;
	pos.x += xoffset;
	pos.y += xoffset;
	pos.z += xoffset;
	gl_Position = vec4( pos, 1.0);
	ourColor = pos;
}
