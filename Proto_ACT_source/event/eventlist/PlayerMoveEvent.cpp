#pragma once
#include "DxLib.h"
#include "PlayerMoveEvent.h"

using namespace std;

//コンストラクタ
PlayerMoveEvent::PlayerMoveEvent(EventManager* man, float speed, float x, float y, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	move_speed = speed;
	px = x;
	py = y;
}

//デストラクタ
PlayerMoveEvent::~PlayerMoveEvent() {

}

//更新
void PlayerMoveEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	float x = player->GetX();
	float y = player->GetY();
	float angle = atan2f(stop_y - y, stop_x - x);

	//始めの処理
	if (time == 0) {
		//目標の座標を設定
		stop_x = x + px;
		stop_y = y + py;
	}

	player->SetXSpeed(move_speed * cosf(angle));
	player->SetYSpeed(move_speed * sinf(angle));

	//目的地に近づいたら終了
	if (fabsf(stop_x - x) < move_speed && fabsf(stop_y - y) < move_speed) {
		player->SetX(stop_x);
		player->SetY(stop_y);
		player->SetXSpeed(0.0f);
		player->SetYSpeed(0.0f);
		end_flag = true;
	}

}

//描画
void PlayerMoveEvent::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

}