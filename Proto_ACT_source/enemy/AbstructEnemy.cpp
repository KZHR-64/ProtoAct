#pragma once
#include "DxLib.h"
#include "AbstractEnemy.h"
#include <math.h>

using namespace std;

AbstractEnemy::AbstractEnemy(EnemyManager* man, int num, float ini_x, float ini_y) : CharacterBase() {
	manager = man;

	boss_flag = false;
	image_num = num;
	trance = 255;
	hp = 1;
	max_hp = hp;
	x = ini_x;
	y = ini_y;
	base_x = x;
	base_y = y;
	base_enemy = NULL; //本体は基本的にNULL
}

AbstractEnemy::~AbstractEnemy(){

	for (auto &ene : parts) {
		ene->SetEndFlag(true); //パーツを消去
		ene.reset();
	}
	parts.clear();
	hit.clear(); //当たり判定のメモリを解放
}

//本体を取得
AbstractEnemy* AbstractEnemy::GetBase() {
	return base_enemy;
}

//本体を設定
void AbstractEnemy::SetBase(AbstractEnemy* base) {
	base_enemy = base;
}

//位置の調節
void AbstractEnemy::AdjustPosition(shared_ptr<MapChipManager> map, shared_ptr<EffectManager> effect) {
	shared_ptr<AbstractMapChip> mapchip;

	bool step_flag = false; //マップチップに乗っているか
	bool left_hit = false; //左側が当たっているか
	bool right_hit = false; //右側が当たっているか
	bool top_hit = false; //上側が当たっているか
	bool bottom_hit = false; //下側が当たっているか

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
			left_hit = true; //左側が当たったことに
			adjusted = true; //当たったことに
			sub_x = (hit[i].x - hit[i].size) - (mapchip->GetX() + 4.0f * mapchip->GetSizeX());
			x += fabsf(sub_x);
			sx = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			right_hit = true; //右側が当たったことに
			adjusted = true; //当たったことに
			sub_x = (hit[i].x + hit[i].size) - (mapchip->GetX() - 4.0f * mapchip->GetSizeX());
			x -= fabsf(sub_x);
			sx = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//両側が当たっていたら
	if (left_hit && right_hit) {
		hp = 0; //HPを0に
		damaged = true;
		//速度を初期化
		sx = 0.0f;
		sy = 0.0f;
		end_flag = true; //消える
		effect->SetEffect(1, x, y); //爆発
		return;
	}

	//ジャンプ中
	if (jump_flag && !flying_flag) {
		//上昇時間中なら
		if (0 < jump_time) {
			jump_time--; //時間を減少
		}
		else
		{
			if (sy < 0.4f && sy > -0.4f) sy = 0.4f;
			sy += fabsf(sy * 1.3f); //速度を1.3(0.7)倍(飛行中は1.1倍)する
			if (sy > 10.0f) sy = 10.0f;
		}
	}

	y += sy + my; //行く予定の座標を決定
	HitUpdate(); //当たり判定を更新

	//上下との判定
	for (unsigned int i = 0; i < hit.size(); i++) {
		mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			top_hit = true; //上側が当たったことに
			adjusted = true; //当たったことに
			sub_x = (hit[i].y - hit[i].size) - (mapchip->GetY() + 8.0f * mapchip->GetSizeY());
			y += fabsf(sub_x);
			sy = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			bottom_hit = true; //下側が当たったことに
			adjusted = true; //当たったことに
			sub_x = (hit[i].y + hit[i].size) - (mapchip->GetY());
			y -= fabsf(sub_x);
			sy = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//両側が当たっていたら
	if (top_hit && bottom_hit) {
		hp = 0; //HPを0に
		damaged = true;
		//速度を初期化
		sx = 0.0f;
		sy = 0.0f;
		end_flag = true; //消える
		effect->SetEffect(1, x, y); //爆発
		return;
	}

	for (unsigned int i = 0; i < hit.size(); i++)
	{
		mapchip = map->HitCheckBottom(hit[i].x, hit[i].y + 1.0f, hit[i].size); //乗っている足場を設定

		if (mapchip != NULL) {
			jump_flag = false;
			break; //乗っている足場があったら終了
		}
	}
	//ジャンプしていないで空中にいる場合
	if (mapchip == NULL && !jump_flag && !flying_flag) {
		jump_flag = true; //フラグをtrueに
		jump_time = 0; //下降開始
	}
}

//ダメージ処理
void AbstractEnemy::HitDamage(int damage_num, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	//すでにダメージを受けているなら
	if (damaged) {
		return; //終了
	}

	damaged = true;
	damage_time = 18;

	//本体がいるならそっちにダメージ
	if (base_enemy != NULL) {
		base_enemy->HitDamage(damage_num, effect, sound);
		return;
	}

	hp -= damage_num;

	//HPが0になったら
	if (hp <= 0) {
		// 本体がいるならそっちのやられ
		if (base_enemy != NULL) {
			base_enemy->Defeat(effect, sound);
		}
		else {
			Defeat(effect, sound); //やられたときの動作
		}
	}
	//0でなければ
	else {
		sound->PlaySoundEffect(12); //効果音を鳴らす
	}
}

//ボスかを取得
bool AbstractEnemy::GetBossFlag() {
	return boss_flag;
}

//ボスかを設定
void AbstractEnemy::SetBossFlag(int rank) {
	boss_flag = (0 < rank); //格が0以上ならボス
}

//弾に当たっているか
void AbstractEnemy::HitCheckBullet(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (hit.size() <= 0) return;

	for (auto& h : hit) {
		int damage = bullet->HitCheckChara(h.x, h.y, h.size, false, true);

		if (0 < damage && !damaged) {
			//hp -= damage;
			//damaged = true;
			//damage_time = 6;
			HitDamage(damage, effect, sound);
		}
	}
}

//敵に当たっているか
void AbstractEnemy::HitCheckEnemy(float cx, float cy, float hit_size, shared_ptr<EffectManager> effect) {
	if (hit.size() <= 0 || !hit_flag) return;

	for (auto& h : hit) {


	}

}

//キャラクターとの当たり判定
bool AbstractEnemy::HitCheckChara(float cx, float cy, float hit_size, bool check_hit) {
	if (hit.size() <= 0) return false;

	for (auto& h : hit) {

		float dif_x = cx - h.x;
		float dif_y = cy - h.y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + h.size) {
			return true;
		}
	}

	return false;
}

//タイマー関連の更新
void AbstractEnemy::Timer() {
	time++;
	if (0 < damage_time) {
		damage_time--;
		if (damage_time <= 0) {
			damaged = false;
		}
	}
}