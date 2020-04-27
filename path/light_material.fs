//材质片段着色器

#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform vec3 lightPos;
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
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

void main()
{
   
	
	//环境光--
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	//环境光 end

	//漫反射光--
	vec3 norm = normalize(Normal);//法向量的标准化
	vec3 lightDir = normalize(light.position - FragPos);//定向光线的标准化 (即从光源到片元的单位向量)
	float diff = max(dot(norm, lightDir), 0.0);//点乘 如果结果为负数,说明角度超过90°, 负数颜色是没有定义的.
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));//texture方法采样纹理颜色
	//漫反射光 end
	
	//镜面反射光--
	vec3 viewDir = normalize( viewPos - FragPos);
	vec3 refrectDir = reflect(-lightDir, norm);
	float spec = pow( max(dot(viewDir, refrectDir), 0.0), material.shininess );
	//这里的贴图坐标还是使用TexCoords，但颜色采样使用了指定的第二张贴图，所以就能做到影响效果。
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));//黑色为0.0所以没有镜面反射
	//镜面反射光 end


	vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}