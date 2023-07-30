#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include"shader.h"
#include"texture.h"
#include"game.h"

struct Particle {
    glm::vec2 Position, Velocity;
    glm::vec4 Color;
    float     Life;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

//ParticleGenerator当大量粒子的容器，反复产生杀死粒子
class ParticleGenerator
{
public:
    ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);


    // 更新所有粒子
    void Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
   
    
    // 渲染所有粒子
    void Draw();
private:
    std::vector<Particle> particles;
    unsigned int amount;
    Shader shader;
    Texture2D texture;
    unsigned int VAO;
    // 初始化缓冲和顶点属性
    void init();
    unsigned int firstUnusedParticle();
    // 重生粒子
    void respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

