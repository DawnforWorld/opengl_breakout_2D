#pragma once
#include<iostream>
#include<vector>

#include"game_object.h"

class GameLevel
{
public:
	std::vector<GameObject> Bricks;
	GameLevel(){}
	// 从文件中加载关卡
	void Load(const char* file, unsigned int levelWidth, unsigned int leveHeight);
	// 渲染关卡
	void Draw(SpriteRenderer& renderer);
	// 检查一个关卡是否已完成 (所有非坚硬的瓷砖均被摧毁)
	bool IsCompleted();

private:
	// 由砖块数据初始化关卡
	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int leveHeight);

};