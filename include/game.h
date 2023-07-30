#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<vector>
#include"game_level.h"
#include"ball_object.h"
//#define GAME_H
// 游戏当前的状态

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GMAE_WIN,
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
const float PLAYER_VELOCITY(0.1f);

// 初始化球速度
const glm::vec2 INITIAL_BALL_VELOCITY(0.01f*2, -0.035f*2);
// 球半径
const float BALL_RADIUS = 12.5f;

class game {
public:
	GameState State;
	bool Keys[1024];
	unsigned int  Width, Height;
	std::vector<GameLevel> Levels;
	unsigned int Level;
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


};



