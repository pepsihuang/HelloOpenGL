//����Ƭ����ɫ��

#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

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
	vec3 position;//��Դλ�� ���ڼ����ķ�������
	vec3 direction;//�۹�ķ�������
	float cutOff;//��Բ׶�й�� ����Ӧ�����й�ǵ�����ֵ
	float outerCutOff;//��Բ׶�й�� ����ƽ����Ե
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	//���Դ��Ҫ�Ĳ���
	float constant;		//������
	float linear;		//һ����
	float quadratic;	//������

};

uniform Light light;

void main()
{
   
   vec3 lightDir = normalize(light.position - FragPos);//��ƬԪָ���Դ
   
   float theta = dot(lightDir, normalize(-light.direction));//���㵱ǰƬԪ����Դ���������ָ��ķ��������нǵ�����ֵ
   //����������ֵ,0�ȱ�ʾ1.0������ֵ, 90�ȱ�ʾ0.0������ֵ
   //��0�ȵ�180�ȵ�����ֵ��ΧΪ1~0~-1
   if(theta > light.cutOff)//������Ҫʹ��'>'
   {
		//������
		vec3 ambient        = light.ambient * vec3(texture(material.diffuse, TexCoords));
		//�������--
		vec3 norm           = normalize(Normal);//�������ı�׼��
		float diff          = max(dot(norm, lightDir), 0.0);//��� ������Ϊ����,˵���Ƕȳ���90��, ������ɫ��û�ж����.
		vec3 diffuse        = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));//texture��������������ɫ
		//���淴���--
		vec3 viewDir        = normalize( viewPos - FragPos);
		vec3 refrectDir     = reflect(-lightDir, norm);
		float spec          = pow( max(dot(viewDir, refrectDir), 0.0), material.shininess );
		//�������ͼ���껹��ʹ��TexCoords������ɫ����ʹ����ָ���ĵڶ�����ͼ�����Ծ�������ֻӰ�������趨�õ������Ч����
		vec3 specular       = light.specular * spec * vec3(texture(material.specular, TexCoords));//��ɫΪ0.0����û�о��淴��
	
		//���Դ���㷨 
		//˥��
		float distance		= length(light.position - FragPos);
		float attenuation	= 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));
		//˥���Թ�Դ������Ӱ��
		//�����Ƴ�˥���Ի������Ӱ��,��Ϊ�����Ȿ���Ѿ�����,�����˥��,���ܾͺڵÿ�������. 
		diffuse		*= attenuation;
		specular	*= attenuation;
		vec3 result = ambient + diffuse + specular;
		FragColor   = vec4(result, 1.0);
   }
   else
   {
   	   //�ھ۹���,����������,���������ط�ɶ��������
	   FragColor = vec4(light.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
   }

}