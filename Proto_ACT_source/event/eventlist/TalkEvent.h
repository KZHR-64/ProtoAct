#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

//��b�C�x���g

class TalkEvent : public AbstractEvent {
protected:
	std::string chara_name; //�L�����N�^�[��
	std::string message; //����
public:
	TalkEvent(EventManager* man, std::string, std::string, bool stop_player, bool stop_enemy); //�R���X�g���N�^(�L�������A���́A���@���~�߂邩�A�G���~�߂邩)
	~TalkEvent(); //�f�X�g���N�^
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //�`��
};
