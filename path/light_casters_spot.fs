//材质片段着色器

#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;

struct Material {
	//由于环境光颜色在绝大多数情况下等于漫反射颜色，所以省略掉存储
	//漫反射光贴图
	sampler2D diffuse;
	//镜面高光纹理贴图
	sampler2D specular;
	float shininess;
};

uniform Material material;

struct Light{
	vec3 position;//光源位置 用于计算光的方向向量
	vec3 direction;//聚光的方向向量
	float cutOff;//内圆锥切光角 这里应该是切光角的余弦值
	float outerCutOff;//外圆锥切光角 用于平滑边缘
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	//点光源需要的参数
	float constant;		//常数项
	float linear;		//一次项
	float quadratic;	//二次项

};

uniform Light light;

void main()
{
   

	//环境光
	vec3 ambient        = light.ambient * vec3(texture(material.diffuse, TexCoords));
	//漫反射光--
	vec3 norm           = normalize(Normal);//法向量的标准化
    vec3 lightDir		= normalize(light.position - FragPos);//从片元指向光源
	float diff          = max(dot(norm, lightDir), 0.0);//点乘 如果结果为负数,说明角度超过90°, 负数颜色是没有定义的.
	vec3 diffuse        = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));//texture方法采样纹理颜色
	//镜面反射光--
	vec3 viewDir        = normalize( viewPos - FragPos);
	vec3 refrectDir     = reflect(-lightDir, norm);
	float spec          = pow( max(dot(viewDir, refrectDir), 0.0), material.shininess );
	//这里的贴图坐标还是使用TexCoords，但颜色采样使用了指定的第二张贴图，所以就能做到只影响我们设定好的区域的效果。
	vec3 specular       = light.specular * spec * vec3(texture(material.specular, TexCoords));//黑色为0.0所以没有镜面反射
	
	//点光源的算法 软边界
	float theta			= dot(lightDir, normalize(-light.direction));
	float epsilon		= light.cutOff - light.outerCutOff;
	float intensity		= clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);//软边界算法
	diffuse				*= intensity;
	specular			*= intensity;
	//衰减
	float distance		= length(light.position - FragPos);
	float attenuation	= 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));//衰减算法
	//衰减对光源分量的影响
	//这里移除衰减对环境光的影响,因为环境光本身已经很弱,如果在衰减,可能就黑得看不到了. 
	diffuse				*= attenuation;
	specular			*= attenuation;
	vec3 result			= ambient + diffuse + specular;
	FragColor			= vec4(result, 1.0);


}