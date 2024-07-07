#pragma once
#include "DxLib.h"
#include "BulletManager.h"
#include "bulletlist/StraightShoot.h"
#include "bulletlist/ControlShoot.h"
#include "bulletlist/RocketHand.h"
#include "bulletlist/Aura.h"
#include "bulletlist/BreakBlast.h"
#include "bulletlist/LockShoot.h"
#include "bulletlist/BombBlast.h"

using namespace std;

BulletManager::BulletManager(){
	SetData();
}

BulletManager::~BulletManager(){
	bullet.clear();
	bullet_data.clear();
}

//初期化
void BulletManager::Reset(){
	bullet.clear();
}

//弾情報の設定
void BulletManager::SetData() {
	int num;
	ifstream ifs("data/bullet/bullet_data.csv");

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
		bullet_data[num].type = atoi(s.c_str()); //種類を取得
		getline(ss, s, ','); //カンマまで読み込む
		bullet_data[num].image = atoi(s.c_str()); //画像の番号を取得
		getline(ss, s, ','); //カンマまで読み込む
		bullet_data[num].breakable = (1 == atoi(s.c_str())); //壊せるかを取得
		getline(ss, s, ','); //カンマまで読み込む
		bullet_data[num].hit_player = (1 == atoi(s.c_str())); //自機に当たるかを取得
		getline(ss, s, ','); //カンマまで読み込む
		bullet_data[num].hit_enemy = (1 == atoi(s.c_str())); //敵に当たるかを取得
		getline(ss, s, ','); //カンマまで読み込む
		bullet_data[num].hit_map = (1 == atoi(s.c_str())); //マップチップに当たるかを取得
		getline(ss, s, ','); //カンマまで読み込む
		bullet_data[num].damage = atoi(s.c_str()); //ダメージ値を取得得
		getline(ss, s, ','); //カンマまで読み込む
		bullet_data[num].break_power = atoi(s.c_str()); //壊す力を取得
	}
	ifs.close();

}

//消えるか確認
void BulletManager::EraseCheck(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	if (bullet.empty()) return;
	float left = (float)camera->GetScrollX(); //画面左端
	float right = (float)camera->GetScrollX() + (float)WINDOW_X; //画面右端
	float top = (float)camera->GetScrollY(); //画面上
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y; //画面底

	for (auto bul = bullet.begin(); bul != bullet.end();) {
		bool erase_flag; //消えるフラグ
		float x = (*bul)->GetX();
		float y = (*bul)->GetY();
		int end_time = (*bul)->GetEndTime(); //消えるまでの時間
		
		//画面外なら消す
		erase_flag = (x < left - 64.0f || right + 64.0f < x || y < top - 64.0f || bottom + 64.0f < y);

		//消えるまでの時間が0より大きいなら
		if (0 < end_time) {
			end_time--; //時間を減らす
			//時間が0になったら消える
			if (end_time <= 0) erase_flag = true;
			(*bul)->SetEndTime(end_time); //時間を設定
		}

		//消去フラグがtrueなら消去
		if ((*bul)->GetEndFlag() || erase_flag) {
			//画面外による消滅でなければ
			if (!erase_flag) {
				(*bul)->Erase(effect, sound); //消えるときの動作
			}
			bul = bullet.erase(bul);
		}
		else {
			bul++;
		}
	}
}

//弾の配置
shared_ptr<AbstractBullet> BulletManager::SetBullet(int num, float ini_x, float ini_y, float speed, float angle) {
	shared_ptr<AbstractBullet> new_bullet;

	switch (bullet_data[num].type)
	{
	case 0:
		new_bullet = make_shared<StraightShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 1:
		new_bullet = make_shared<ControlShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 2:
		new_bullet = make_shared<RocketHand>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 3:
		new_bullet = make_shared<Aura>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 4:
		new_bullet = make_shared<BreakBlast>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 5:
		new_bullet = make_shared<LockShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 8:
		new_bullet = make_shared<BombBlast>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	default:
		new_bullet = make_shared<StraightShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	}

	new_bullet->SetDamage(bullet_data[num].damage); //ダメージ値を設定
	new_bullet->SetBreakable(bullet_data[num].breakable); //壊せるか設定
	new_bullet->SetHitPlayer(bullet_data[num].hit_player); //自機に当たるか設定
	new_bullet->SetHitEnemy(bullet_data[num].hit_enemy); //敵に当たるか設定
	new_bullet->SetHitMap(bullet_data[num].hit_map); //マップチップに当たるか設定
	new_bullet->SetBreakPower(bullet_data[num].break_power); //マップチップを壊す力を設定

	bullet.emplace_back(new_bullet);
	
	return new_bullet;
}

//マップチップとの当たり判定
void BulletManager::HitCheckMap(shared_ptr<MapChipManager> map) {
	if (bullet.empty()) return;
	for (auto &bul : bullet) {
		if (!bul->GetHitMap()) continue;
		bul->HitCheckMap(map);
	}
}

//キャラクターとの当たり判定
int BulletManager::HitCheckChara(float cx, float cy, float hit_size, bool check_player, bool check_enemy) {
	int damage = 0; //ダメージ値
	for (auto &bul : bullet) {
		if (!((check_player && bul->GetHitPlayer()) || (check_enemy && bul->GetHitEnemy()))) continue;
		int bullet_damage = bul->HitCheckChara(cx, cy, hit_size); //ダメージ値
		//ダメージ値があり、前のものより大きいなら
		if (damage < bullet_damage) {
			damage = bullet_damage; //ダメージ値を更新
		}
	}
	return damage;
}

//更新
void BulletManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera){
	if (bullet.empty()) return;
	for (auto &bul : bullet) {
		
		bul->Update(player, enemy, item, effect, key, sound, camera);
		
		bul->SetX(bul->GetX() + bul->GetXSpeed());
		bul->SetY(bul->GetY() + bul->GetYSpeed());
		int time = bul->GetTime();
		time++;
		bul->SetTime(time);
		bul->HitUpdate();
	}

	EraseCheck(effect, sound, camera); //弾を消すか確認
}

//描画
void BulletManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	if (bullet.empty()) return;
	for (auto &bul : bullet) {
		bul->Draw(image, camera);
		bul->DrawHit(camera);
	}
	//DrawFormatString(64, 96, GetColor(255, 255, 255), "%d", bullet.size());
}