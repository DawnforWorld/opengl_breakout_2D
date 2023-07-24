#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#define GAME_H
// 游戏当前的状态

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GMAE_WIN,
};


class game {
public:
	GameState State;
	bool Keys[1024];
	unsigned int  Width, Height;

	game(unsigned int  Width, unsigned int  Height);
	~game();

	void Init();	//  初始化游戏状态（加载所有的着色器/纹理/关卡）
	void ProcessInput(float dt);		//调用ProcessInput函数，并使用存储在Keys数组里的数据来处理输入
	void Update(float dt);	//更新游戏设置状态（比如玩家/球的移动）
	void Render();		//调用Render函数来对游戏进行渲染

};



