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
	sVertex = glCreateShader(GL_VERTEX_SHADER);//������ɫ��
	glShaderSource(sVertex, 1, &vertexSource, NULL);//�滻��ɫ��Դ���룬vertexSourceҪ���ص���ɫ����Դ������ַ�����ָ�����顣

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
	glAttachShader(this->ID, sVertex);//����ɫ�����󸽼ӵ�program����
	glAttachShader(this->ID, sFragment);
	if (geometrySource!=nullptr)
	{
		glAttachShader(this->ID, gShader);
	}
	glLinkProgram(this->ID);//����һ��program����
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
	//glGetUniformLocation- ����ͳһ������λ��,glUniformΪ��ǰ�������ָ��Uniform������ֵ


}

void Shader::SetInteger(const char* name, int value, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform1i(glGetUniformLocation(this->ID, name), value);
	//glGetUniformLocation- ����ͳһ������λ��,glUniformΪ��ǰ�������ָ��Uniform������ֵ
}
void Shader::SetVector2f(const char* name, float x, float y, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
	//glGetUniformLocation- ����ͳһ������λ��,glUniformΪ��ǰ�������ָ��Uniform������ֵ
}
void Shader::SetVector2f(const char* name, const glm::vec2 &value, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
	//glGetUniformLocation- ����ͳһ������λ��,glUniformΪ��ǰ�������ָ��Uniform������ֵ
}
void Shader::SetVector3f(const char* name, float x, float y, float z,bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform3f(glGetUniformLocation(this->ID, name), x, y,z);
	//glGetUniformLocation- ����ͳһ������λ��,glUniformΪ��ǰ�������ָ��Uniform������ֵ
}
void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y,value.z);
	//glGetUniformLocation- ����ͳһ������λ��,glUniformΪ��ǰ�������ָ��Uniform������ֵ
}
void Shader::SetVector4f(const char* name, float x, float y, float z,float w, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
	//glGetUniformLocation- ����ͳһ������λ��,glUniformΪ��ǰ�������ָ��Uniform������ֵ
}
void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
	//glGetUniformLocation- ����ͳһ������λ��,glUniformΪ��ǰ�������ָ��Uniform������ֵ
}
void Shader::SetMatrix4(const char* name, const glm::mat4 &matrix, bool useShader) {
	if (useShader)
	{
		this->use();
	}
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	
	//ͨ��һ�±�����uniform���εı��������ý�һ�±���ֵ������Ⱦ���ߡ�
	//ָ�������������Ⱦ���GL_FALSE�����������Ⱦ���GL_TRUE���� 
	//value_ptrָ����count��Ԫ�ص������ָ�롣
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
	int success;
	char infoLog[1024];
	if (type!="PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);//����ɫ�����󷵻�һ�����������������ɫ�������Ƿ�ɹ���
		//compile_status:���ڼ������Ƿ�ɹ����ɹ�ΪGL_TRUE������ΪGL_FALSE.
		//���������صĽ���洢������ĵ����������У���Ϊ��������õ��Ľ���кܶ��֣�����Ҫ�������ڵ�������������
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);//����ɫ���������Ϣ��־
			std::cout << "| ERROR::SHADER: COMPILE-TIME ERROR:TYPE:" << type << "\n" 
				<<infoLog<<"\n------------------------------------------ - -- - "
				<< std::endl;
		}

	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);//- ��program���󷵻�һ��������ֵ
		//GL_LINK_STATUS,�����һ�ε� program ���ӳɹ����򷵻� GL_TRUE�����򷵻� GL_FALSE��
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "\ ERROR::shader:Link_time error: type :" << type << "\n"
				<< infoLog << "\n------------------------------------"
				<< std::endl;
		}
	}



}