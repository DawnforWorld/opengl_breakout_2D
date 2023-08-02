#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<vector>
#include"game_level.h"
#include"ball_object.h"
//#define GAME_H
// ��Ϸ��ǰ��״̬

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
//��ײ��ص�����ʹ��typedef
typedef std::tuple<bool, Direction, glm::vec2> Collision;
// ��ʼ������Ĵ�С
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// ��ʼ�����������
const float PLAYER_VELOCITY(500.0);

// ��ʼ�����ٶ�
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f,-350.0f);
// ��뾶
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

	void Init();	//  ��ʼ����Ϸ״̬���������е���ɫ��/����/�ؿ���
	void ProcessInput(float dt);		//����ProcessInput��������ʹ�ô洢��Keys���������������������
	void Update(float dt);	//������Ϸ����״̬���������/����ƶ���
	void Render();		//����Render����������Ϸ������Ⱦ

	void DoCollisions();//�������ؿ��е�ש���Ƿ�����ײ��
	//�ָ�
	void ResetLevel();
	void ResetPlayer();


};



