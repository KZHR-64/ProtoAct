#pragma once
#include "DxLib.h"
#include "AbstractBullet.h"
#include <math.h>

using namespace std;

AbstractBullet::AbstractBullet(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : CharacterBase() {
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
	base_speed = ini_speed;
	angle = ini_angle;
	SetSpeed(ini_speed);
	damage = 0;
	hit_player = false;
	hit_enemy = false;
	hit_map = false;
	breakable = false;
	break_power = 1;
}

AbstractBullet::~AbstractBullet(){
	hit.clear(); //当たり判定のメモリを解放
}

//ダメージ値を返す
int AbstractBullet::GetDamage() {
	return damage;
}

//ダメージ値を設定
void AbstractBullet::SetDamage(int set_damage) {
	damage = set_damage;
}

//壊せるかを取得
bool AbstractBullet::GetBreakable() {
	return breakable;
}

//壊せるかを設定
void AbstractBullet::SetBreakable(bool flag) {
	breakable = flag;
}

//自機に当たるかを取得
bool AbstractBullet::GetHitPlayer() {
	return hit_player;
}

//自機に当たるかを設定
void AbstractBullet::SetHitPlayer(bool flag) {
	hit_player = flag;
}

//敵に当たるかを取得
bool AbstractBullet::GetHitEnemy() {
	return hit_enemy;
}

//敵に当たるかを設定
void AbstractBullet::SetHitEnemy(bool flag) {
	hit_enemy = flag;
}

//マップチップに当たるかを取得
bool AbstractBullet::GetHitMap() {
	return hit_map;
}

//マップチップに当たるかを設定
void AbstractBullet::SetHitMap(bool flag) {
	hit_map = flag;
}

//マップチップの破壊力を返す
int AbstractBullet::GetBreakPower() {
	return break_power;
}

//マップチップの破壊力を設定
void AbstractBullet::SetBreakPower(int set_power) {
	break_power = set_power;
}

//キャラクターとの当たり判定
int AbstractBullet::HitCheckChara(float cx, float cy, float hit_size) {
	if (hit.size() <= 0) return -1;

	for (auto &h : hit) {
		float dif_x = cx - h.x;
		float dif_y = cy - h.y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + h.size) {
			//壊せる弾なら消す
			if (breakable) {
				end_flag = true;
			}
			return damage;
		}
	}

	return -1;
}

//マップチップとの当たり判定
void AbstractBullet::HitCheckMap(shared_ptr<MapChipManager> map) {
	if (hit.size() <= 0) return;

	for (auto& h : hit) {
		if (map->HitCheck(h.x, h.y, h.size, break_power)) {
			//壊せる弾なら消す
			if (breakable) {
				end_flag = true;
			}
		}
	}
}