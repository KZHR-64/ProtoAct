#pragma once
#include "DxLib.h"
#include "MissEvent.h"

using namespace std;

//�R���X�g���N�^
MissEvent::MissEvent(EventManager* man, int waiting, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	wait_time = waiting;
}

//�f�X�g���N�^
MissEvent::~MissEvent() {

}

//�X�V
void MissEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	//�҂����Ԃ��߂�����I��
	if (wait_time <= time) {
		manager->SetRestartFlag(true);
		end_flag = true;
	}

	//�C�x���g�J�n��
	if (time == 0) {
		float px = player->GetX();
		float py = player->GetY();
		sound->StopBgm();
		player->SetXSpeed(0.0f);
		player->SetYSpeed(0.0f);
		player->SetDrawFlag(false);
		effect->SetEffect(1, px, py); //����
	}

}

//�`��
void MissEvent::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

}