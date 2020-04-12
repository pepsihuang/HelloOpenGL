#pragma once

#include <glad/glad.h>
#include <string>

class CShaderFromFile
{
public:
	enum ShaderType {
		_ST_NULL_,
		_ST_Vertex_,
		_ST_Fragment_,
	};
	CShaderFromFile(ShaderType type , const char* filepath);
	~CShaderFromFile();


	void setFloat(const std::string& name, float value) const;
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;


	void use();

private:

	void CheckCompileErr(unsigned int ss, bool isProgramm);

	unsigned int m_id;
	ShaderType m_type;
};
