#include"shader.h"
#include<iostream>


Shader& Shader::use() {
	glUseProgram(this->ID);
	return *this;
}
//Compiles the shader from given source code
void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{

	unsigned int sVertex, sFragment, gShader;
	//vertex shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);//创建着色器
	glShaderSource(sVertex, 1, &vertexSource, NULL);//替换着色器源代码，vertexSource要加载到着色器的源代码的字符串的指针数组。

	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");
	//fragment shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");
	//If geometry shader source code is given ,also compile geometry shader
	if (geometrySource != nullptr)
	{
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}

	//shader program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);//将着色器对象附加到program对象
	glAttachShader(this->ID, sFragment);
	if (geometrySource!=nullptr)
	{
		glAttachShader(this->ID, gShader);
	}
	glLinkProgram(this->ID);//连接一个program对象。
	checkCompileErrors(this->ID, "PROGRAM");

	//delete the sahder as thry're linked into our program now and longer necessery
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource!=nullptr)
	{
		glDeleteShader(gShader);
	}
}

void Shader::SetFloat(const char* name, float value, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform1f(glGetUniformLocation(this->ID, name), value);
	//glGetUniformLocation- 返回统一变量的位置,glUniform为当前程序对象指定Uniform变量的值


}

void Shader::SetInteger(const char* name, int value, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform1i(glGetUniformLocation(this->ID, name), value);
	//glGetUniformLocation- 返回统一变量的位置,glUniform为当前程序对象指定Uniform变量的值
}
void Shader::SetVector2f(const char* name, float x, float y, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
	//glGetUniformLocation- 返回统一变量的位置,glUniform为当前程序对象指定Uniform变量的值
}
void Shader::SetVector2f(const char* name, const glm::vec2 &value, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
	//glGetUniformLocation- 返回统一变量的位置,glUniform为当前程序对象指定Uniform变量的值
}
void Shader::SetVector3f(const char* name, float x, float y, float z,bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform3f(glGetUniformLocation(this->ID, name), x, y,z);
	//glGetUniformLocation- 返回统一变量的位置,glUniform为当前程序对象指定Uniform变量的值
}
void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y,value.z);
	//glGetUniformLocation- 返回统一变量的位置,glUniform为当前程序对象指定Uniform变量的值
}
void Shader::SetVector4f(const char* name, float x, float y, float z,float w, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
	//glGetUniformLocation- 返回统一变量的位置,glUniform为当前程序对象指定Uniform变量的值
}
void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
	//glGetUniformLocation- 返回统一变量的位置,glUniform为当前程序对象指定Uniform变量的值
}
void Shader::SetMatrix4(const char* name, const glm::mat4 &matrix, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	
	//通过一致变量（uniform修饰的变量）引用将一致变量值传入渲染管线。
	//指明矩阵是列优先矩阵（GL_FALSE）还是行优先矩阵（GL_TRUE）。 
	//value_ptr指向由count个元素的数组的指针。
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
	int success;
	char infoLog[1024];
	if (type!="PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);//从着色器对象返回一个参数（用来检测着色器编译是否成功）
		//compile_status:用于检测编译是否成功，成功为GL_TRUE，否则为GL_FALSE.
		//函数将返回的结果存储在输入的第三个参数中，因为这个函数得到的结果有很多种，所以要单独放在第三个参数当中
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);//回着色器对象的信息日志
			std::cout << "| ERROR::SHADER: COMPILE-TIME ERROR:TYPE:" << type << "\n" 
				<<infoLog<<"\n------------------------------------------ - -- - "
				<< std::endl;
		}

	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);//- 从program对象返回一个参数的值
		//GL_LINK_STATUS,如果上一次的 program 链接成功，则返回 GL_TRUE，否则返回 GL_FALSE。
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "\ ERROR::shader:Link_time error: type :" << type << "\n"
				<< infoLog << "\n------------------------------------"
				<< std::endl;
		}
	}



}