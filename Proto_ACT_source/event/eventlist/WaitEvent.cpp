#pragma once
#include "DxLib.h"
#include "WaitEvent.h"

using namespace std;

//コンストラクタ
WaitEvent::WaitEvent(EventManager* man, int waiting, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	wait_time = waiting;
}

//デストラクタ
WaitEvent::~WaitEvent() {

}

//更新
void WaitEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){
	//待ち時間を過ぎたら終了
	if (wait_time <= time) {
		end_flag = true;
	}
}

//描画
void WaitEvent::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

}