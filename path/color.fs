#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
   
    //FragColor = vec4(lightColor * objectColor, 1.0);


	vec3 norm = normalize(Normal);//�������ı�׼��
	vec3 lightDir = normalize(lightPos - FragPos);//������ߵı�׼�� (���ӹ�Դ��ƬԪ�ĵ�λ����)

	
	float specularStrenght = 0.7;
	vec3 viewDir = normalize( viewPos - FragPos);//���߷�������
	//��Ӧ�����ŷ�����ķ�������
	//��һ������Ҫ���ƬԪָ���Դ����ȡ��. �ڶ�������Ϊ��λ������
	vec3 refrectDir = reflect(-lightDir, norm);

	//���㾵�����
	// 1.���������뷴�������ļн�,����Ҫ����뱣֤Ϊ����.
	// 2. double pow(double x, double y) ���� x �� y ����.
	// 3. '32'����߹�ķ���� ��һ������ķ����Խ�ߣ���������Խǿ��ɢ���Խ�٣��߹��ԽС��
	float spec = pow( max(dot(viewDir, refrectDir), 0.0), 32 );
	vec3 specular = specularStrenght * spec * lightColor;


	float diff = max(dot(norm, lightDir), 0.0);//��� ������Ϊ����,˵���Ƕȳ���90��, ������ɫ��û�ж����.
	vec3 diffuse = diff * lightColor;//�Ӷ����ݽǶȶ��õ�������ߵĹ���

	float ambientStrength = 0.1;//������
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);

}