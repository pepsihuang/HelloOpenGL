//����Ƭ����ɫ��

#version 330 core
out vec4 FragColor;

struct Material {
	//���ڻ�������ɫ�ھ����������µ�����������ɫ������ʡ�Ե��洢
	//���������ͼ
	sampler2D diffuse;
	//����߹�������ͼ
	sampler2D specular;
	float shininess;
};

struct DirLight{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;		
	float linear;		
	float quadratic;	
};

struct SpotLight{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;		
	float linear;		
	float quadratic;	
	
	float cutOff;
	float outerCutOff; 
};

#define NR_POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;

//����ǰ������
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
		vec3 norm           = normalize(Normal);//�������ı�׼��
		vec3 viewDir        = normalize( viewPos - FragPos);
		vec3 result			= CalcDirLight(dirLight, norm, viewDir );
		
		for(int i = 0; i < NR_POINT_LIGHTS; ++i)
			result			+= CalcPointLight(pointLight[i],norm, FragPos, viewDir );

		result				+= CalcSpotLight( spotLight, norm, FragPos, viewDir );
		FragColor			= vec4(result, 1.0);

}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{

	
	//������--
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	//�������--
	vec3 norm = (normal);//�������ı�׼��
	vec3 lightDir = normalize(-light.direction);//��Ҫ��ƬԪָ���Դ
	float diff = max(dot(norm, lightDir), 0.0);//��� ������Ϊ����,˵���Ƕȳ���90��, ������ɫ��û�ж����.
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));//texture��������������ɫ

	//���淴���--
	vec3 refrectDir = reflect(-lightDir, norm);
	float spec = pow( max(dot(viewDir, refrectDir), 0.0), material.shininess );
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	return ( ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir		= normalize(light.position - FragPos);//��ƬԪָ���Դ
	float diff          = max(dot(normal, lightDir), 0.0);//��� ������Ϊ����,˵���Ƕȳ���90��, ������ɫ��û�ж����.
	vec3 refrectDir     = reflect(-lightDir, normal);
	float spec          = pow( max(dot(viewDir, refrectDir), 0.0), material.shininess );
	//˥��
	float distance		= length(light.position - FragPos);
	float attenuation	= 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));//˥���㷨

	vec3 ambient        = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse        = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));//texture��������������ɫ
	vec3 specular       = light.specular * spec * vec3(texture(material.specular, TexCoords));//��ɫΪ0.0����û�о��淴��
	//˥���Թ�Դ������Ӱ��
	ambient				*= attenuation;
	diffuse				*= attenuation;
	specular			*= attenuation;
	
	return (ambient + diffuse + specular);

}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
   
	//������
	vec3 ambient        = light.ambient * vec3(texture(material.diffuse, TexCoords));
	//�������--
	vec3 norm           = normalize(normal);//�������ı�׼��
    vec3 lightDir		= normalize(light.position - FragPos);//��ƬԪָ���Դ
	float diff          = max(dot(norm, lightDir), 0.0);//��� ������Ϊ����,˵���Ƕȳ���90��, ������ɫ��û�ж����.
	vec3 diffuse        = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));//texture��������������ɫ
	//���淴���--
	vec3 refrectDir     = reflect(-lightDir, norm);
	float spec          = pow( max(dot(viewDir, refrectDir), 0.0), material.shininess );
	//�������ͼ���껹��ʹ��TexCoords������ɫ����ʹ����ָ���ĵڶ�����ͼ�����Ծ�������ֻӰ�������趨�õ������Ч����
	vec3 specular       = light.specular * spec * vec3(texture(material.specular, TexCoords));//��ɫΪ0.0����û�о��淴��
	
	//���Դ���㷨 ��߽�
	float theta			= dot(lightDir, normalize(-light.direction));
	float epsilon		= light.cutOff - light.outerCutOff;
	float intensity		= clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);//��߽��㷨
	diffuse				*= intensity;
	specular			*= intensity;
	//˥��
	float distance		= length(light.position - FragPos);
	float attenuation	= 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));//˥���㷨
	//˥���Թ�Դ������Ӱ��
	//�����Ƴ�˥���Ի������Ӱ��,��Ϊ�����Ȿ���Ѿ�����,�����˥��,���ܾͺڵÿ�������. 
	diffuse				*= attenuation;
	specular			*= attenuation;
	return (ambient + diffuse + specular);
}
