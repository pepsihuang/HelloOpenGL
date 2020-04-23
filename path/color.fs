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



	vec3 norm = normalize(Normal);//法向量的标准化
	vec3 lightDir = normalize(lightPos - FragPos);//定向光线的标准化

	float diff = max(dot(norm, lightDir), 0.0);//点乘 如果结果为负数,说明角度超过90°, 负数颜色是没有定义的.
	vec3 diffuse = diff * lightColor;//从而根据角度而得到入射光线的过度

	float ambientStrength = 0.1;//环境光
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);

}