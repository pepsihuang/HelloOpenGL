
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;//数据是一定先到顶点着色器,然后从顶点着色器传递给片段着色器


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;//片段的位置 疑问:从顶点着色器发送片段的位置,但顶点着色器在光栅化的前面完成. 那些片段的位置从哪来?

void main()
{
	FragPos = vec3(model* vec4(aPos, 1.0));//将顶点坐标转换成世界坐标系
	Normal = aNormal;

	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}