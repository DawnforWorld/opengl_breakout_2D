#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<vector>
#include"game_level.h"
#include"ball_object.h"
#include"powerup.h"



// 游戏当前的状态

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
//碰撞相关的数据使用typedef
typedef std::tuple<bool, Direction, glm::vec2> Collision;
// 初始化挡板的大小
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// 初始化当班的速率
const float PLAYER_VELOCITY(500.0);

// 初始化球速度
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f,-350.0f);
// 球半径
const float BALL_RADIUS = 12.5f;





class game {
public:
	GameState State;
	bool Keys[1024];
	unsigned int  Width, Height;
	std::vector<GameLevel> Levels;
	unsigned int Level;
	unsigned int Lives;
	bool KeysProcessed[1024];

	std::vector<PowerUp>  PowerUps;//跟踪游戏中被激活的道具的类型、持续时间、相关效果等状态，将它们存储在一个容器内
	game(unsigned int  Width, unsigned int  Height);
	~game();

	

	void Init();	//  初始化游戏状态（加载所有的着色器/纹理/关卡）
	void ProcessInput(float dt);		//调用ProcessInput函数，并使用存储在Keys数组里的数据来处理输入
	void Update(float dt);	//更新游戏设置状态（比如玩家/球的移动）
	void Render();		//调用Render函数来对游戏进行渲染

	void DoCollisions();//检查球与关卡中的砖块是否发生碰撞。
	//恢复
	void ResetLevel();
	void ResetPlayer();
	//道具
	void SpawnPowerUps(GameObject& block);//给定的砖块位置生成一个道具
	void UpdatePowerUps(float dt);//管理所有当前被激活的道具。


};



