#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include <iostream>
#include <string>
#include <sstream>

//���@�ړ��C�x���g

class PlayerMoveEvent : public AbstractEvent {
protected:
	float move_speed; //���x
	float px; //x�����̈ړ���
	float py; //y�����̈ړ���
	float stop_x; //�ړI�̍��W
	float stop_y;
public:
	PlayerMoveEvent(EventManager* man, float x, float y, float speed, bool stop_player, bool stop_enemy); //�R���X�g���N�^(�ړ��ʁA���x�A���@���~�߂邩�A�G���~�߂邩)
	~PlayerMoveEvent(); //�f�X�g���N�^
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //�`��
};
