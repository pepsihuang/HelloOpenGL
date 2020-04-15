#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D ourTexture1; //������
uniform sampler2D ourTexture2; //������

void main()
{
	//texture��������������ɫ ����1���������, ����2��Ӧ��������
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);//���������ĳ�����ɫ,�ͻ���ʾһ�����ɫ

	//mix�Ǹ��ݵ�����������ǰ���������������Բ�ֵ,�˴�0.4�ͷ��ص�һ����ɫ40%+�ڶ�����ɫ60%�Ļ��ɫ
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(TexCoord.x, TexCoord.y)), 0.2);

}