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
	GLboolean key[1024];
	GLuint Width, Height;

	game(GLuint Width, GLuint Height);
	~game();

	void Init();	//  ��ʼ����Ϸ״̬���������е���ɫ��/����/�ؿ���
	void ProcessInput(GLfloat dt);		//����ProcessInput��������ʹ�ô洢��Keys���������������������
	void Update(GLfloat dt);	//������Ϸ����״̬���������/����ƶ���
	void Render();		//����Render����������Ϸ������Ⱦ

};



