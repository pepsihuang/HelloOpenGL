#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
   
    //FragColor = vec4(lightColor * objectColor, 1.0);



	vec3 norm = normalize(Normal);//�������ı�׼��
	vec3 lightDir = normalize(lightPos - FragPos);//������ߵı�׼��

	float diff = max(dot(norm, lightDir), 0.0);//��� ������Ϊ����,˵���Ƕȳ���90��, ������ɫ��û�ж����.
	vec3 diffuse = diff * lightColor;//�Ӷ����ݽǶȶ��õ�������ߵĹ���

	float ambientStrength = 0.1;//������
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);

}