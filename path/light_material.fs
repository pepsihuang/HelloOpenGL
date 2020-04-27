//����Ƭ����ɫ��

#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
	//���ڻ�������ɫ�ھ����������µ�����������ɫ������ʡ�Ե��洢
	//���������ͼ
	sampler2D diffuse;
	//����߹�������ͼ
	sampler2D specular;
	float shininess;
};

uniform Material material;

struct Light{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

void main()
{
   
	
	//������--
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	//������ end

	//�������--
	vec3 norm = normalize(Normal);//�������ı�׼��
	vec3 lightDir = normalize(light.position - FragPos);//������ߵı�׼�� (���ӹ�Դ��ƬԪ�ĵ�λ����)
	float diff = max(dot(norm, lightDir), 0.0);//��� ������Ϊ����,˵���Ƕȳ���90��, ������ɫ��û�ж����.
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));//texture��������������ɫ
	//������� end
	
	//���淴���--
	vec3 viewDir = normalize( viewPos - FragPos);
	vec3 refrectDir = reflect(-lightDir, norm);
	float spec = pow( max(dot(viewDir, refrectDir), 0.0), material.shininess );
	//�������ͼ���껹��ʹ��TexCoords������ɫ����ʹ����ָ���ĵڶ�����ͼ�����Ծ�������Ӱ��Ч����
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));//��ɫΪ0.0����û�о��淴��
	//���淴��� end


	vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}