#include "game.h"
#include"resource_manager.h"
#include"sprite_renderer.h"
#include"particle_generator.h"
#include"post_processor.h"

SpriteRenderer* Renderer;
GameObject* Player;
BallObject* Ball;
ParticleGenerator* Particles;
PostProcessor* Effects;

float ShakeTime = 0.0f;

bool CheckCollision(GameObject& one, GameObject& two);
Collision CheckCollision(BallObject& one, GameObject& two);
Direction VectorDirection(glm::vec2 closest);
void ActivatePowerUp(PowerUp& powerUp);




game::game(unsigned int  width, unsigned int  height) :State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

game::~game() {
	delete Renderer;
	delete Player;
	delete Ball;
	delete Particles;
	delete Effects;
}


void game::Init() {
	//load shaders
	ResourceManager::LoadShader("./resource/shader/sprite.vs", "./resource/shader/sprite.frag", nullptr, "sprite");
	ResourceManager::LoadShader("./resource/shader/particle.vs", "./resource/shader/particle.frag", nullptr, "particle");
	ResourceManager::LoadShader("./resource/shader/post_processing.vs", "./resource/shader/post_processing.frag", nullptr, "postprocessing");

	//configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	 
	ResourceManager::GetShader("particle").use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);

	
	//加载纹理
	ResourceManager::LoadTexture("./resource/image/background.jpg", false, "background");
	ResourceManager::LoadTexture("./resource/image/awesomeface.png", true, "face");
	ResourceManager::LoadTexture("./resource/image/block.png", false, "block");
	ResourceManager::LoadTexture("./resource/image/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("./resource/image/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("./resource/image/particle.png", true, "particle");
	ResourceManager::LoadTexture("./resource/image/powerup_speed.png", true, "powerup_speed");
	ResourceManager::LoadTexture("./resource/image/powerup_sticky.png", true, "powerup_sticky");
	ResourceManager::LoadTexture("./resource/image/powerup_increase.png", true, "powerup_increase");
	ResourceManager::LoadTexture("./resource/image/powerup_confuse.png", true, "powerup_confuse");
	ResourceManager::LoadTexture("./resource/image/powerup_chaos.png", true, "powerup_chaos");
	ResourceManager::LoadTexture("./resource/image/powerup_passthrough.png", true, "powerup_passthrough");

	//设置专用于渲染的控制
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 500);
	Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);
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

	glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));


	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS,-BALL_RADIUS * 2.0f);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,ResourceManager::GetTexture("face"));
}


void game::Update(float dt) {
	// 更新对象
	Ball->Move(dt, this->Width);
	// 检测碰撞
	this->DoCollisions();
	// update particles
	Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2.0f));
	if (ShakeTime>0.0f)
	{
		ShakeTime -= dt;
		if (ShakeTime <= 0.0f)
			Effects->Shake = false;
	}
	if (Ball->Position.y >= this->Height) // 球是否接触底部边界？
	{
		this->ResetLevel();
		this->ResetPlayer();
	}

}

void game::ProcessInput(float dt) {
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0.0f) 
			{
				Player->Position.x -= velocity;
				if (Ball->Stuck)
				{
					Ball->Position.x -= velocity;
				}
			}
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
			{
				Player->Position.x += velocity;
				if (Ball->Stuck)
				{
					Ball->Position.x += velocity;
				}
			}
		}
		if (this->Keys[GLFW_KEY_SPACE])
		{
 			Ball->Stuck = false;
		}

	}
}

void game::Render() {
	if(this->State == GAME_ACTIVE)
	{ 
		Effects->BeginRender();
		// 绘制背景
		// 绘制关卡
		// 绘制挡板
		// 绘制粒子
		// 绘制小球
		//draw background
			Renderer->DrawSprite(ResourceManager::GetTexture("background"),
				glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
			//draw level
			this->Levels[this->Level].Draw(*Renderer);
			//draw player
			Player->Draw(*Renderer);

			for (PowerUp& powerUp : this->PowerUps)//渲染道具
				if (!powerUp.Destroyed)
					powerUp.Draw(*Renderer);

			// draw particles
			Particles->Draw();
			//draw ball
			Ball->Draw(*Renderer);


		Effects->EndRender();
		Effects->Render(glfwGetTime());
	}
	
}
void game::ResetLevel()
{
	if (this->Level == 0)
		this->Levels[0].Load("./resource/levels/one.lvl", this->Width, this->Height / 2);
	else if (this->Level == 1)
		this->Levels[1].Load("./resource/levels/two.lvl", this->Width, this->Height / 2);
	else if (this->Level == 2)
		this->Levels[2].Load("./resource/levels/three.lvl", this->Width, this->Height / 2);
	else if (this->Level == 3)
		this->Levels[3].Load("./resource/levels/four.lvl", this->Width, this->Height / 2);
}

void game::ResetPlayer()
{
	// 重置球
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
	// 禁用所有活动电源
	Effects->Chaos = Effects->Confuse = false;
	Ball->PassThrough = Ball->Sticky = false;
	Player->Color = glm::vec3(1.0f);
	Ball->Color = glm::vec3(1.0f);

}


bool IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type);

void game::UpdatePowerUps(float dt)
{
	for (PowerUp& powerUp : this->PowerUps)
	{
		powerUp.Position += powerUp.Velocity * dt;
		if (powerUp.Activated)
		{
			powerUp.Duration -= dt;

			if (powerUp.Duration <= 0.0f)
			{
				// 之后会将这个道具移除
				powerUp.Activated = false;
				// 停用效果
				if (powerUp.Type == "sticky")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "sticky"))
					{	// 仅当没有其他sticky效果处于激活状态时重置，以下同理
						Ball->Sticky = false;
						Player->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "pass-through")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "pass-through"))
					{
						Ball->PassThrough = false;
						Ball->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "confuse")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "confuse"))
					{
						Effects->Confuse = false;
					}
				}
				else if (powerUp.Type == "chaos")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "chaos"))
					{
						Effects->Chaos = false;
					}
				}
			}
		}
	}
	this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
		[](const PowerUp& powerUp) { return powerUp.Destroyed && !powerUp.Activated; }
	), this->PowerUps.end());
}

bool ShouldSpawn(unsigned int chance)
{
	unsigned int random = rand() % chance;
	return random == 0;
}

void game::SpawnPowerUps(GameObject& block)
{
	if (ShouldSpawn(75)) 
		this->PowerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")));
	if (ShouldSpawn(15)) 
		this->PowerUps.push_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")));
	if (ShouldSpawn(15))
		this->PowerUps.push_back(PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")));
}

void ActivatePowerUp(PowerUp& powerUp)
{
	if (powerUp.Type == "speed")
	{
		Ball->Velocity *= 1.2;
	}
	else if (powerUp.Type == "sticky")
	{
		Ball->Sticky = true;
		Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
	}
	else if (powerUp.Type == "pass-through")
	{
		Ball->PassThrough = true;
		Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
	}
	else if (powerUp.Type == "pad-size-increase")
	{
		Player->Size.x += 50;
	}
	else if (powerUp.Type == "confuse")
	{
		if (!Effects->Chaos)
			Effects->Confuse = true; // 只在chaos未激活时生效，chaos同理
	}
	else if (powerUp.Type == "chaos")
	{
		if (!Effects->Confuse)
			Effects->Chaos = true;
	}
}


void game::DoCollisions()
{
	for (GameObject& box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision)) // /如果collision 是 true
			{
				//  如果砖块不是实心就销毁砖块
				if (!box.IsSolid)
				{
					box.Destroyed = true;
					this->SpawnPowerUps(box);

				}
				//  碰撞处理
				else
				{
					// 如果是实心的砖块则激活shake特效
					ShakeTime = 0.05f;
					Effects->Shake = true;
				}
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);

				if (!(Ball->PassThrough && !box.IsSolid))
				{
					if (dir == LEFT || dir == RIGHT) // 水平方向碰撞
					{
						Ball->Velocity.x = -Ball->Velocity.x; // 反转水平速度
						//  重定位
						float penetration = Ball->Radius - std::abs(diff_vector.x);
						if (dir == LEFT)
							Ball->Position.x += penetration; // 将球右移
						else
							Ball->Position.x -= penetration; // 左移
					}
					else // 垂直方向碰撞
					{
						Ball->Velocity.y = -Ball->Velocity.y; // reverse vertical velocity
						// relocate
						float penetration = Ball->Radius - std::abs(diff_vector.y);
						if (dir == UP)
							Ball->Position.y -= penetration; // 上移
						else
							Ball->Position.y += penetration; // 下移
					}
				}
				
			}
		}
	}
	//检查powerup碰撞
	for (PowerUp& powerUp : this->PowerUps)
	{
		if (!powerUp.Destroyed)
		{
			if (powerUp.Position.y >= this->Height)
				powerUp.Destroyed = true;
			if (CheckCollision(*Player, powerUp))
			{	// 道具与挡板接触，激活它！
				ActivatePowerUp(powerUp);
				powerUp.Destroyed = true;
				powerUp.Activated = true;
			}
		}
	}

	//玩家垫子的碰撞
	Collision result = CheckCollision(*Ball, *Player);
	if (!Ball->Stuck && std::get<0>(result))
	{
		// 检查碰到了挡板的哪个位置，并根据碰到哪个位置来改变速度
		float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
		float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
		float percentage = distance / (Player->Size.x / 2.0f);
		// 依据结果移动
		float strength = 2.0f;
		glm::vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		//Ball->Velocity.y = -Ball->Velocity.y;

		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
		Ball->Velocity.y = -1 * abs(Ball->Velocity.y);//粘板问题

		Ball->Stuck = Ball->Sticky;
	}

	
}






bool CheckCollision(GameObject& one, GameObject& two) 
{
	// x轴方向碰撞
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// y轴方向碰撞
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// 只有两个轴向都有碰撞时才碰撞
	return collisionX && collisionY;
}

Collision CheckCollision(BallObject& one, GameObject& two) 
{
	// 获取圆的中心 
	glm::vec2 center(one.Position + one.Radius);
	// 计算AABB的信息（中心、半边长）
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y
	);
	// 获取两个中心的差矢量
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// AABB_center加上clamped这样就得到了碰撞箱上距离圆最近的点closest
	glm::vec2 closest = aabb_center + clamped;
	// 获得圆心center和最近点closest的矢量并判断是否 length <= radius
	difference = closest - center;


	if (glm::length(difference) <= one.Radius)
		return std::make_tuple(true, VectorDirection(difference), difference);
	else
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));


}

Direction VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),  // 上
		glm::vec2(1.0f, 0.0f),  // 右
		glm::vec2(0.0f, -1.0f), // 下
		glm::vec2(-1.0f, 0.0f)  // 左
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}




bool IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type)
{
	for (const PowerUp& powerUp : powerUps)
	{
		if (powerUp.Activated)
			if (powerUp.Type == type)
				return true;
	}
	return false;
}