#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include <iostream>
#include <string>
#include <sstream>

//�X�N���[���ʒu�����C�x���g

class ScrollSettingEvent : public AbstractEvent {
protected:
	int px; //x���W
	int py; //y���W
public:
	ScrollSettingEvent(EventManager* man, int x, int y, bool stop_player, bool stop_enemy); //�R���X�g���N�^(���W�A���@���~�߂邩�A�G���~�߂邩)
	~ScrollSettingEvent(); //�f�X�g���N�^
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //�`��
};
