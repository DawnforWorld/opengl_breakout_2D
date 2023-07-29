#include "game.h"
#include"resource_manager.h"
#include"sprite_renderer.h"

SpriteRenderer* Renderer;
GameObject* Player;




game::game(unsigned int  width, unsigned int  height) :State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

game::~game() {
	delete Renderer;
	delete Player;
}


void game::Init() {
	//load shaders
	ResourceManager::LoadShader("./resource/shader/sprite.vs", "./resource/shader/sprite.frag", nullptr, "sprite");
	//configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	//设置专用于渲染的控制
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	
	
	//加载纹理
	ResourceManager::LoadTexture("./resource/image/background.jpg", false, "background");
	ResourceManager::LoadTexture("./resource/image/awesomeface.png", false, "face");
	ResourceManager::LoadTexture("./resource/image/block.png", false, "block");
	ResourceManager::LoadTexture("./resource/image/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("./resource/image/paddle.png", true, "paddle");


	//加载关卡
	GameLevel one; one.Load("./resource/levels/one.lvl", this->Width, this->Height / 2);
	GameLevel two; two.Load("./resource/levels/two.lvl", this->Width, this->Height / 2);
	GameLevel three; three.Load("./resource/levels/three.lvl", this->Width, this->Height / 2);
	GameLevel four; four.Load("./resource/levels/four.lvl", this->Width, this->Height / 2);

	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;

	glm::vec2 playerPos = glm::vec2(
		this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
		this->Height - PLAYER_SIZE.y
	);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));



}
void game::Update(float dt) {

}

void game::ProcessInput(float dt) {
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0.0f)
				Player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
		}
	}
}

void game::Render() {
	if(this->State == GAME_ACTIVE)
	{ 
		//draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("background"),
			glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
		//draw level
		this->Levels[this->Level].Draw(*Renderer);
		//draw player
		Player->Draw(*Renderer);
	}
	
}