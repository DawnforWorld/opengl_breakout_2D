#include"sprite_renderer.h"


SpriteRenderer::SpriteRenderer( Shader &shader)
{
	this->shader = shader;
	this->initRenderData();

}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}


void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
	//准备变换
	this->shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.SetMatrix4("model", model);
	this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);//设置激活的纹理单元
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);


}


void SpriteRenderer::initRenderData()
{
	//配置VAO VBO
	unsigned int VBO;
	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);//生成顶点数组对象名称,数量为1，指定一个数组，在其中存储生成的顶点数组对象名称
	glGenBuffers(1, &VBO);//该函数用来生成缓冲区对象的名称第一个参数是要生成的缓冲对象的数量，第二个是要输入用来存储缓冲对象名称的数组

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//第一个就是缓冲对象的类型，第二个参数就是要绑定的缓冲对象的名称，也就是我们在上一个函数里生成的名称，使用该函数将缓冲对象绑定到OpenGL上下文环境中以便使用
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //为缓冲对象（VBO，IBO 等）分配空间并存储数据
	
	glBindVertexArray(this->quadVAO); //绑定一个顶点数组对象
	glEnableVertexAttribArray(0);//这个和location = 0 对应
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}