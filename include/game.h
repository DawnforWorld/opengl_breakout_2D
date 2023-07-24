#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#define GAME_H
// ��Ϸ��ǰ��״̬

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

	void Init();	//  ��ʼ����Ϸ״̬���������е���ɫ��/����/�ؿ���
	void ProcessInput(float dt);		//����ProcessInput��������ʹ�ô洢��Keys���������������������
	void Update(float dt);	//������Ϸ����״̬���������/����ƶ���
	void Render();		//����Render����������Ϸ������Ⱦ

};



