#pragma once
#include "DxLib.h"
#include "BreakBlast.h"

using namespace std;

//コンストラクタ
BreakBlast::BreakBlast(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.0f, 0.0f, 8.0f);
}

//デストラクタ
BreakBlast::~BreakBlast() {

}

//必ず行う更新
void BreakBlast::AbsUpdate() {

}

//消える時の動作
void BreakBlast::Erase(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {

}

//更新
void BreakBlast::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//消滅直前で判定が発生する
	if (end_time == 2) {
		hit_map = true;
	}
}

//描画
void BreakBlast::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
}