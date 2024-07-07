#pragma once
#include "DxLib.h"
#include "ScrollResetEvent.h"

using namespace std;

//コンストラクタ
ScrollResetEvent::ScrollResetEvent(EventManager* man, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	
}

//デストラクタ
ScrollResetEvent::~ScrollResetEvent() {

}

//更新
void ScrollResetEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {

	//Display::Get_Instance()->ReSetScrollXMax();
	//Display::Get_Instance()->ReSetScrollYMax();
	end_flag = true;
}

//描画
void ScrollResetEvent::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

}