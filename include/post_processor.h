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
    // 在渲染游戏之前准备后处理器的帧缓冲操作
    void BeginRender();
    // 将渲染数据存储到纹理坐标中
    void EndRender();
    // 渲染后处理器四边形
    void Render(float time);
private:
    //渲染状态
    unsigned int MSFBO, FBO; 
    unsigned int RBO;
    unsigned int VAO;
    // 初始换四边形以渲染下处理
    void initRenderData();
};