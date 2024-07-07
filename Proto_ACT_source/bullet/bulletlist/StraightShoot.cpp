#pragma once
#include "DxLib.h"
#include "StraightShoot.h"

using namespace std;

//コンストラクタ
StraightShoot::StraightShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.0f, 0.0f, 16.0f);
}

//デストラクタ
StraightShoot::~StraightShoot() {

}

//必ず行う更新
void StraightShoot::AbsUpdate() {

}

//消える時の動作
void StraightShoot::Erase(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	int effect_num = hit_player ? 4 : 3; //自機に当たるかでエフェクトを設定
	effect->SetEffect(effect_num, x, y, 0.5f); //エフェクトを発生
}

//更新
void StraightShoot::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera){
	//一定時間ごとにエフェクトを発生
	if (time % 3 == 0 && 0 < time) {
		int effect_num = hit_player ? 9 : 8; //自機に当たるかでエフェクトを設定
		effect->SetEffect(effect_num, x, y, 0.2f); //エフェクトを発生
	}
}

//描画
void StraightShoot::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetBulletImage(image_num, 0);
	camera->Draw(x, y, false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}