#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<vector>
#include"game_level.h"
//#define GAME_H
// ��Ϸ��ǰ��״̬

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GMAE_WIN,
};
// ��ʼ������Ĵ�С
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);

// ��ʼ�����������
const float PLAYER_VELOCITY(1.0f);

class game {
public:
	GameState State;
	bool Keys[1024];
	unsigned int  Width, Height;
	std::vector<GameLevel> Levels;
	unsigned int Level;
	game(unsigned int  Width, unsigned int  Height);
	~game();

	void Init();	//  ��ʼ����Ϸ״̬���������е���ɫ��/����/�ؿ���
	void ProcessInput(float dt);		//����ProcessInput��������ʹ�ô洢��Keys���������������������
	void Update(float dt);	//������Ϸ����״̬���������/����ƶ���
	void Render();		//����Render����������Ϸ������Ⱦ

};



