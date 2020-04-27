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
	vec3 specular;
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
	vec3 viewDir = normalize( viewPos - FragPos);//视线方向向量
	//对应的沿着法线轴的反射向量
	//第一个参数要求从片元指向光源所以取反. 第二个参数为单位法向量
	vec3 refrectDir = reflect(-lightDir, norm);

	//计算镜面分量
	// 1.视线向量与反射向量的夹角,并且要求必须保证为正数.
	// 2. double pow(double x, double y) 返回 x 的 y 次幂.
	// 3. '32'代表高光的反光度 。一个物体的反光度越高，反射能力越强，散射得越少，高光点越小。
	float spec = pow( max(dot(viewDir, refrectDir), 0.0), material.shininess );
	vec3 specular = light.specular * (spec * material.specular);
	//镜面反射光 end


	vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}