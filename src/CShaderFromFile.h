#pragma once

#include <glad/glad.h>
#include <string>

class CShaderFromFile
{
public:

	CShaderFromFile( const char* vefilepath, const char* fragfilepath);
	~CShaderFromFile();


	void setFloat(const std::string& name, float value) const;
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;


	void use();

private:

	void CheckCompileErr(unsigned int ss, const std::string& str);

	unsigned int m_id;
};
