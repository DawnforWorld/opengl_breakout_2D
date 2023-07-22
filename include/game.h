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
	GLboolean key[1024];
	GLuint Width, Height;

	game(GLuint Width, GLuint Height);
	~game();

	void Init();	//  初始化游戏状态（加载所有的着色器/纹理/关卡）
	void ProcessInput(GLfloat dt);		//调用ProcessInput函数，并使用存储在Keys数组里的数据来处理输入
	void Update(GLfloat dt);	//更新游戏设置状态（比如玩家/球的移动）
	void Render();		//调用Render函数来对游戏进行渲染

};



