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


	vec3 norm = normalize(Normal);//法向量的标准化
	vec3 lightDir = normalize(lightPos - FragPos);//定向光线的标准化 (即从光源到片元的单位向量)

	
	float specularStrenght = 0.7;
	vec3 viewDir = normalize( viewPos - FragPos);//视线方向向量
	//对应的沿着法线轴的反射向量
	//第一个参数要求从片元指向光源所以取反. 第二个参数为单位法向量
	vec3 refrectDir = reflect(-lightDir, norm);

	//计算镜面分量
	// 1.视线向量与反射向量的夹角,并且要求必须保证为正数.
	// 2. double pow(double x, double y) 返回 x 的 y 次幂.
	// 3. '32'代表高光的反光度 。一个物体的反光度越高，反射能力越强，散射得越少，高光点越小。
	float spec = pow( max(dot(viewDir, refrectDir), 0.0), 32 );
	vec3 specular = specularStrenght * spec * lightColor;


	float diff = max(dot(norm, lightDir), 0.0);//点乘 如果结果为负数,说明角度超过90°, 负数颜色是没有定义的.
	vec3 diffuse = diff * lightColor;//从而根据角度而得到入射光线的过度

	float ambientStrength = 0.1;//环境光
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);

}