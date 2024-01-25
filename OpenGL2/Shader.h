#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <iostream>

class Shader {
private:
	// SHADER ID
	unsigned int ID = 0;

	unsigned int createShader(const std::string& shaderSource, char type);
	void checkShaderCompilationErrors(unsigned int shaderID);
	void checkProgramLinkingErrors();
public:
	// constructor
	Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

	// use shaderprogram
	void use();
	// delete shaderprogram
	void del();

	// set uniform values
	void setBoolUniform(const std::string& name, bool value) const;
	void setIntUniform(const std::string& name, int value) const;
	void setFloatUniform(const std::string& name, float value) const;
};
