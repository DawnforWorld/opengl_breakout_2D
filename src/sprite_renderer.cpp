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
	//׼���任
	this->shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.SetMatrix4("model", model);
	this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);//���ü��������Ԫ
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);


}


void SpriteRenderer::initRenderData()
{
	//����VAO VBO
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

	glGenVertexArrays(1, &this->quadVAO);//���ɶ��������������,����Ϊ1��ָ��һ�����飬�����д洢���ɵĶ��������������
	glGenBuffers(1, &VBO);//�ú����������ɻ�������������Ƶ�һ��������Ҫ���ɵĻ��������������ڶ�����Ҫ���������洢����������Ƶ�����

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//��һ�����ǻ����������ͣ��ڶ�����������Ҫ�󶨵Ļ����������ƣ�Ҳ������������һ�����������ɵ����ƣ�ʹ�øú������������󶨵�OpenGL�����Ļ������Ա�ʹ��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Ϊ�������VBO��IBO �ȣ�����ռ䲢�洢����
	
	glBindVertexArray(this->quadVAO); //��һ�������������
	glEnableVertexAttribArray(0);//�����location = 0 ��Ӧ
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}