#pragma once
#include "DxLib.h"
#include "EnemyManager.h"
#include "enemylist/NoMove.h"
#include "enemylist/Erhei1.h"
#include "enemylist/Erhei2.h"
#include "enemylist/Erhei3.h"
#include "enemylist/Erhei4.h"
#include "enemylist/Kurhei1.h"
#include "enemylist/Kurhei2.h"
#include "enemylist/Cannon1.h"
#include "enemylist/Cannon2.h"
#include "enemylist/Missile.h"
#include "enemylist/HomingMissile.h"
#include "enemylist/FallBomb.h"
#include "enemylist/FallBomb2.h"
#include "enemylist/DekaKurhei.h"
#include "enemylist/Desdragud.h"
#include "enemylist/DesdragudArm.h"
#include "enemylist/RaidCloud.h"
#include "enemylist/CloudBit.h"
#include <math.h>

using namespace std;

EnemyManager::EnemyManager(){
	midboss_flag = false;
	boss_flag = false;
	boss_battle = false;
	SetData();
}

EnemyManager::~EnemyManager(){
	enemy.clear();
	enemy_data.clear();
	standby_enemy.clear();
}

//初期化
void EnemyManager::Reset(){
	midboss_flag = false;
	boss_flag = false;
	enemy.clear();
	standby_enemy.clear();
}

//敵情報の設定
void EnemyManager::SetData() {
	int num;

	ifstream ifs("data/enemy/enemy_data.csv");

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		// 改行コードを削除
		if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
		if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

		stringstream ss{ str };
		getline(ss, s, ','); //カンマまで読み込む
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ','); //カンマまで読み込む
		enemy_data[num].type = atoi(s.c_str()); //種類を取得
		getline(ss, s, ','); //カンマまで読み込む
		enemy_data[num].hp = atoi(s.c_str()); //HPを取得
		getline(ss, s, ','); //カンマまで読み込む
		enemy_data[num].image = atoi(s.c_str()); //画像の番号を取得
		getline(ss, s, ','); //カンマまで読み込む
		enemy_data[num].size_x = atoi(s.c_str()); //横の大きさを取得
		getline(ss, s, ','); //カンマまで読み込む
		enemy_data[num].size_y = atoi(s.c_str()); //縦の大きさを取得
		getline(ss, s, ','); //カンマまで読み込む
		enemy_data[num].rank = atoi(s.c_str()); //格を取得
	}
	ifs.close();
}

//消えるか確認
void EnemyManager::EraseCheck(shared_ptr<Camera> camera) {
	if (enemy.size() == 0) return;
	float left = (float)camera->GetScrollX() - 64.0f; //画面左端
	float right = (float)camera->GetScrollX() + (float)WINDOW_X + 64.0f; //画面右端
	float top = (float)camera->GetScrollY() - 64.0f; //画面上
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y + 64.0f; //画面底

	for (auto ene = enemy.begin(); ene != enemy.end();) {
		bool erase_flag; //消えるフラグ
		float x = (*ene)->GetX();
		float y = (*ene)->GetY();
		float size_x = 128.0f;// *(*ene)->GetSizeX();
		float size_y = 128.0f;// *(*ene)->GetSizeY();
		int end_time = (*ene)->GetEndTime(); //消えるまでの時間

		//画面外なら消す
		erase_flag = (x < left - size_x || right + size_x < x || y < top - size_y || bottom + size_y < y) && (*ene)->GetBase() == NULL && !(*ene)->GetBossFlag();

		//消えるまでの時間が0より大きいなら
		if (0 < end_time) {
			end_time--; //時間を減らす
			//時間が0になったら消える
			if (end_time <= 0) erase_flag = true;
			(*ene)->SetEndTime(end_time); //時間を設定
		}

		//消去フラグがtrueなら消去
		if (erase_flag) {
			(*ene)->SetEndFlag(true);
		}
		ene++;
	}

	for (auto ene = enemy.begin(); ene != enemy.end();) {
		//消去フラグがtrueなら消去
		if ((*ene)->GetEndFlag()) {
			ene = enemy.erase(ene);
		}
		else {
			ene++;
		}
	}
}

//敵をマップに配置
void EnemyManager::SetStandby(std::string file_name) {
	int row = 0; //行
	int col = 0; //列
	StandbyEnemyDataStruct sta{};

	ifstream ifs(file_name);

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		//カンマ区切りで行を読み込み
		while (getline(ss, s, ',')) {

			//読み込んだ数値が-1でなければ
			int num = atoi(s.c_str());
			if (num != -1) {
				sta.flag = false; //フラグはfalse
				sta.num = atoi(s.c_str()); //番号を設定
				sta.x = col * 32.0f + (enemy_data[sta.num].size_x * 4.0f); //x座標を設定
				sta.y = row * 32.0f + 32.0f - (enemy_data[sta.num].size_y * 8.0f); //y座標を設定
				standby_enemy.emplace_back(sta);
			}
			col++; //列数を増やす
		}

		//列数をリセットして行数を増やす
		col = 0;
		row++;
	}

	ifs.close();
}

//敵の配置
shared_ptr<AbstractEnemy> EnemyManager::SetEnemy(int num, float ini_x, float ini_y, AbstractEnemy* base) {
	shared_ptr<AbstractEnemy> new_enemy;

	switch (enemy_data[num].type)
	{
	case 0:
		new_enemy = make_shared<NoMove>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 1:
		new_enemy = make_shared<Erhei1>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 2:
		new_enemy = make_shared<Erhei2>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 3:
		new_enemy = make_shared<Erhei3>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 4:
		new_enemy = make_shared<Erhei4>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 6:
		new_enemy = make_shared<Kurhei1>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 7:
		new_enemy = make_shared<Kurhei2>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 8:
		new_enemy = make_shared<Missile>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 9:
		new_enemy = make_shared<HomingMissile>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 10:
		new_enemy = make_shared<FallBomb>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 11:
		new_enemy = make_shared<FallBomb2>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 14:
		new_enemy = make_shared<Cannon1>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 15:
		new_enemy = make_shared<Cannon2>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 32:
		new_enemy = make_shared<DekaKurhei>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 33:
		new_enemy = make_shared<RaidCloud>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 34:
		new_enemy = make_shared<CloudBit>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 35:
		new_enemy = make_shared<Desdragud>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 36:
		new_enemy = make_shared<DesdragudArm>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	default:
		new_enemy = make_shared<NoMove>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	}

	new_enemy->SetHp(enemy_data[num].hp); //HPを設定
	new_enemy->SetMaxHp(enemy_data[num].hp); //最大HPを設定
	new_enemy->SetBase(base); //本体を設定
	new_enemy->SetBossFlag(enemy_data[num].rank); //ボスかを設定

	//格によってフラグを立てる
	if (enemy_data[num].rank == 1) midboss_flag = true;
	if (2 <= enemy_data[num].rank){
		boss_flag = true;
		boss_battle = true;
	}

	enemy.emplace_back(new_enemy);

	return new_enemy;
}

//敵が出現できるか確認
void EnemyManager::SpawnCheck(shared_ptr<Camera> camera) {
	if (standby_enemy.size() == 0) return;
	float left = (float)camera->GetScrollX() - 64.0f; //画面左端
	float right = (float)camera->GetScrollX() + (float)WINDOW_X + 64.0f; //画面右端
	float top = (float)camera->GetScrollY() - 64.0f; //画面上
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y + 64.0f; //画面底

	for (unsigned int i = 0; i < standby_enemy.size(); i++) {
		int num = standby_enemy[i].num;
		float x = 4.0f * enemy_data[num].size_x; //判定用
		float y = 4.0f * enemy_data[num].size_y; //判定用

		//敵が出現していなくて範囲内にあるなら
		if (!standby_enemy[i].flag && (0.0f < standby_enemy[i].x - left && standby_enemy[i].x - right < 0.0f && 0.0f < standby_enemy[i].y - top && standby_enemy[i].y - bottom < 0.0f)) {
			standby_enemy[i].flag = true; //出現済みに
			SetEnemy(num, standby_enemy[i].x, standby_enemy[i].y); //敵を出現させる
		}

		//出現済みで範囲外にあるなら
		if (standby_enemy[i].flag && (4.0f * x < left - standby_enemy[i].x || 4.0f * x < standby_enemy[i].x - right || 4.0f * y < top - standby_enemy[i].y || 4.0f * y < standby_enemy[i].y - bottom)) {
			standby_enemy[i].flag = false; //出現していない扱いに
		}
	}
}

//キャラクターとの当たり判定
bool EnemyManager::HitCheckChara(float cx, float cy, float hit_size, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, int damage) {
	for (auto &ene : enemy) {
		if (ene->GetHp() <= 0) continue; //HPが0なら飛ばす
		if (ene->HitCheckChara(cx, cy, hit_size)) {
			if (0 < damage) {
				ene->HitDamage(damage, effect, sound);
			}
			return true;
		}
	}
	return false;
}

//弾に当たっているか
void EnemyManager::HitCheckBullet(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (enemy.size() == 0) return;

	for (auto &ene : enemy) {
		if (ene->GetEndFlag() || ene->GetHp() <= 0) continue; //消えるかHPが0なら飛ばす
		ene->HitCheckBullet(bullet, effect, sound);
	}
}

//敵に当たっているか
void EnemyManager::HitCheckEnemy(std::shared_ptr<EffectManager> effect) {
	if (enemy.size() == 0) return;

	for (auto &ene : enemy) {
		float x = ene->GetX();
		float y = ene->GetY();
		for (auto &ene2 : enemy) {
			if (ene == ene2) continue; //同じなら飛ばす
			ene2->HitCheckEnemy(x, y, 32.0f, effect);
		}
	}
}

//ボス戦中か取得
bool EnemyManager::GetBossFlag() {
	return (boss_flag || midboss_flag);
}

//ボスを倒したか取得
bool EnemyManager::GetBeatBoss() {
	return (boss_battle && !boss_flag);
}

//更新
void EnemyManager::Update(shared_ptr<MapChipManager> map, shared_ptr<BulletManager> bullet, shared_ptr<Player> player, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	if (enemy.empty()) {
		boss_flag = false;
		midboss_flag = false;
		return;
	}

	bool boss = false; //ボスがいるか

	for (auto &ene : enemy) {
		ene->Update(player, bullet, effect, sound, camera); //動作する

		ene->AbsUpdate();
		ene->Timer();
		
		ene->AdjustPosition(map, effect);
		
		if (ene->GetBossFlag()) boss = true; //ボスがいればフラグはtrue
	}

	//ボスがいないならボス戦フラグをfalseに
	if (!boss) {
		boss_flag = false;
		midboss_flag = false;
	}

	EraseCheck(camera); //敵を消すか確認
}

//描画
void EnemyManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	//if (0 < standby_enemy.size()) DrawFormatString(320, 128, GetColor(255, 0, 0), "%d %d %f", boss_flag, midboss_flag, standby_enemy.size());

	if (enemy.empty()) return;
	for (auto &ene : enemy) {
		//無敵時間中は点滅する
		if (ene->GetDamaged()) {
			ene->SetTrance(192);
			
		} else {
			ene->SetTrance(256);
		}
		//本体がないもののみ描画(他は本体に任せる)
		if (ene->GetBase() == NULL) {
			ene->Draw(image, camera);
		}
		ene->DrawHit(camera);
	}
}