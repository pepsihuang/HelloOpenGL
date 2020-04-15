#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D ourTexture1; //采样器
uniform sampler2D ourTexture2; //采样器

void main()
{
	//texture方法采样纹理颜色 参数1纹理采样器, 参数2对应纹理坐标
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);//后面新增的乘上颜色,就会显示一个混合色

	//mix是根据第三个参数对前两个参数进行线性插值,此处0.4就返回第一个颜色40%+第二个颜色60%的混合色
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(TexCoord.x, TexCoord.y)), 0.2);

}