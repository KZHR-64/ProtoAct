#pragma once
#include "DxLib.h"
#include "AbstractItem.h"
#include <math.h>

using namespace std;

AbstractItem::AbstractItem(ItemManager* man, int num, float ini_x, float ini_y) : CharacterBase() {
	manager = man;

	time = 0;
	live_flag = true;
	end_time = -1;
	end_flag = false;
	image_num = num;
	x = ini_x;
	y = ini_y;
	base_x = x;
	base_y = y;
	angle = 0.0f;
	SetSpeed(0.0f);
	hit_player = false;
	hit_enemy = false;
	hit_map = false;
}

AbstractItem::~AbstractItem(){

}

//自機に当たるかを取得
bool AbstractItem::GetHitPlayer() {
	return hit_player;
}

//自機に当たるかを設定
void AbstractItem::SetHitPlayer(bool flag) {
	hit_player = flag;
}

//敵に当たるかを取得
bool AbstractItem::GetHitEnemy() {
	return hit_enemy;
}

//敵に当たるかを設定
void AbstractItem::SetHitEnemy(bool flag) {
	hit_enemy = flag;
}

//マップチップに当たるかを取得
bool AbstractItem::GetHitMap() {
	return hit_map;
}

//マップチップに当たるかを設定
void AbstractItem::SetHitMap(bool flag) {
	hit_map = flag;
}

//プレイヤーとの当たり判定
bool AbstractItem::HitCheckPlayer(std::shared_ptr<Player> player) {
	for (auto& h : hit) {
		if (player->HitCheckItem(h.x, h.y, h.size)) {
			return true;
		}
	}

	return false;
}

//マップチップとの当たり判定
void AbstractItem::HitCheckMap(shared_ptr<MapChipManager> map) {
	/*shared_ptr<AbstractMapChip> mapchip;

	float sub_x = 0.0f; //足場にどれだけめり込んでいるか

	//乗っている足場の速度の合計
	float mx = map->GetPlusSpeedX(hit.x, hit.y + 1.0f, hit.size);
	float my = map->GetPlusSpeedY(hit.x, hit.y + 1.0f, hit.size);

	x += sx + mx; //行く予定の座標を決定

	//左右との判定
	mapchip = map->HitCheckLeft(hit.x, hit.y, hit.size);
	while (mapchip != NULL) {
		sub_x = (hit.x - hit.size) - (mapchip->GetX() + 4.0f * mapchip->GetSizeX());
		x += fabsf(sub_x);
		sx = 0.0f;
		HitUpdate();
		mapchip = map->HitCheckLeft(hit.x, hit.y, hit.size);
	}
	mapchip = map->HitCheckRight(hit.x, hit.y, hit.size);
	while (mapchip != NULL) {
		sub_x = (hit.x + hit.size) - (mapchip->GetX() - 4.0f * mapchip->GetSizeX());
		x -= fabsf(sub_x);
		sx = 0.0f;
		HitUpdate();
		mapchip = map->HitCheckRight(hit.x, hit.y, hit.size);
	}

	//浮いていないなら
	//if (!flying_flag) {
		if (sy < 0.4f && sy > -0.4f) sy = 0.4f;
		sy += fabsf(sy * 1.3f); //速度を1.3(0.7)倍(飛行中は1.1倍)する
		if (sy > 10.0f) sy = 10.0f;
	//}

	y += sy + my; //行く予定の座標を決定
	HitUpdate(); //当たり判定を更新

	//上下との判定
	mapchip = map->HitCheckTop(hit.x, hit.y, hit.size);
	while (mapchip != NULL) {
		sub_x = (hit.y - hit.size) - (mapchip->GetY() + 8.0f * mapchip->GetSizeY());
		y += fabsf(sub_x);
		sy = 0.0f;
		HitUpdate();
		mapchip = map->HitCheckTop(hit.x, hit.y, hit.size);
	}
	mapchip = map->HitCheckBottom(hit.x, hit.y, hit.size);
	while (mapchip != NULL) {
		sub_x = (hit.y + hit.size) - (mapchip->GetY());
		y -= fabsf(sub_x);
		sy = 0.0f;
		HitUpdate();
		mapchip = map->HitCheckBottom(hit.x, hit.y, hit.size);
	}*/
	shared_ptr<AbstractMapChip> mapchip;

	float sub_x = 0.0f; //足場にどれだけめり込んでいるか

	//乗っている足場の速度の合計
	float mx = 0.0f;
	float my = 0.0f;

	for (unsigned int i = 0; i < hit.size(); i++) {
		//乗っている足場の速度の合計
		mx += map->GetPlusSpeedX(hit[i].x, hit[i].y + 1.0f, hit[i].size);
		my += map->GetPlusSpeedY(hit[i].x, hit[i].y + 1.0f, hit[i].size);
	}

	adjusted = false; //当たったかは一旦falseに

	angle += spin_speed; //回転

	x += sx + mx; //行く予定の座標を決定

	HitUpdate(); //当たり判定を更新

	//左右との判定
	for (unsigned int i = 0; i < hit.size(); i++) {
		mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			adjusted = true; //当たったことに
			sub_x = (hit[i].x - hit[i].size) - (mapchip->GetX() + 4.0f * mapchip->GetSizeX());
			x += fabsf(sub_x);
			sx = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			adjusted = true; //当たったことに
			sub_x = (hit[i].x + hit[i].size) - (mapchip->GetX() - 4.0f * mapchip->GetSizeX());
			x -= fabsf(sub_x);
			sx = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//浮いていないなら
	//if (!flying_flag) {
	if (sy < 0.4f && sy > -0.4f) sy = 0.4f;
	sy += fabsf(sy * 1.3f); //速度を1.3(0.7)倍(飛行中は1.1倍)する
	if (sy > 10.0f) sy = 10.0f;
	//}

	y += sy + my; //行く予定の座標を決定
	HitUpdate(); //当たり判定を更新

	//上下との判定
	for (unsigned int i = 0; i < hit.size(); i++) {
		mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			adjusted = true; //当たったことに
			sub_x = (hit[i].y - hit[i].size) - (mapchip->GetY() + 8.0f * mapchip->GetSizeY());
			y += fabsf(sub_x);
			sy = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			adjusted = true; //当たったことに
			sub_x = (hit[i].y + hit[i].size) - (mapchip->GetY());
			y -= fabsf(sub_x);
			sy = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		}
	}
}

//キャラクターとの当たり判定
bool AbstractItem::HitCheckChara(float cx, float cy, float hit_size) {
	if (hit.size() <= 0) return false;

	for (auto &h : hit) {
		float dif_x = cx - h.x;
		float dif_y = cy - h.y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + h.size) {
			return true;
		}
	}

	return false;
}