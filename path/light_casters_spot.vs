
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;//������һ���ȵ�������ɫ��,Ȼ��Ӷ�����ɫ�����ݸ�Ƭ����ɫ��
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;//Ƭ�ε�λ�� ����:�Ӷ�����ɫ������Ƭ�ε�λ��,��������ɫ���ڹ�դ����ǰ�����. ��ЩƬ�ε�λ�ô�����?
out vec2 TexCoords;
void main()
{
	FragPos = vec3(model* vec4(aPos, 1.0));//����������ת������������ϵ
	Normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoords = aTexCoords;

	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}