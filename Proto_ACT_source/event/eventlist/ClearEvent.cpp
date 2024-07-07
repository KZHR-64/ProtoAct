#pragma once
#include "DxLib.h"
#include "ClearEvent.h"

using namespace std;

//コンストラクタ
ClearEvent::ClearEvent(EventManager* man, int waiting, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	wait_time = waiting;
}

//デストラクタ
ClearEvent::~ClearEvent() {

}

//更新
void ClearEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	//待ち時間を過ぎたら終了
	if (wait_time <= time) {
		manager->SetClearFlag(true);
		end_flag = true;
	}
}

//描画
void ClearEvent::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

}