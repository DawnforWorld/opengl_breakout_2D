#include"resource_manager.h"
#define STB_IMAGE_IMPLEMENTATION
#include<sstream>
#include<fstream>
#include"stb_image.h"
#include<iostream>


std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string ,Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) {

	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}
Shader& ResourceManager::GetShader(std::string name)
{
	return Shaders[name];

}
Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name) {
	Textures[name] = loadTextureFromFile(file, alpha);

	return Textures[name];
}
Texture2D& ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}
void ResourceManager::Clear()
{
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try
	{
		// open file
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		//read file's buffer contents into stream
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		//close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// 将流转化为字符串
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		//if geometry shader path is present,also load a geometry shader
		
		if (gShaderFile!=nullptr)
		{
			
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
			//std::cout << "dasdada" << std::endl;
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERRPR::SHADER: Failed to read shader files" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();


	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

	return shader;


}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
	// create texture object
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}

	// load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
	
	texture.Generate(width, height, data);
	
	stbi_image_free(data);
	return texture;
}