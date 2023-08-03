#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "shader.h"

class PostProcessor
{
public:
    Shader PostProcessingShader;
    Texture2D Texture;
    unsigned int Width, Height;

    bool Confuse, Chaos, Shake;
    PostProcessor(Shader shader, unsigned int width, unsigned int height);
    // ����Ⱦ��Ϸ֮ǰ׼����������֡�������
    void BeginRender();
    // ����Ⱦ���ݴ洢������������
    void EndRender();
    // ��Ⱦ�������ı���
    void Render(float time);
private:
    //��Ⱦ״̬
    unsigned int MSFBO, FBO; 
    unsigned int RBO;
    unsigned int VAO;
    // ��ʼ���ı�������Ⱦ�´���
    void initRenderData();
};