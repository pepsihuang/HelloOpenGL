#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D ourTexture; //采样器

void main()
{
	FragColor = texture(ourTexture, TexCoord);//采样纹理颜色 参数1纹理采样器, 参数2对应纹理坐标
}