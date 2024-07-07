#pragma once
#include "DxLib.h"
#include "WaitEvent.h"

using namespace std;

//�R���X�g���N�^
WaitEvent::WaitEvent(EventManager* man, int waiting, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	wait_time = waiting;
}

//�f�X�g���N�^
WaitEvent::~WaitEvent() {

}

//�X�V
void WaitEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){
	//�҂����Ԃ��߂�����I��
	if (wait_time <= time) {
		end_flag = true;
	}
}

//�`��
void WaitEvent::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

}