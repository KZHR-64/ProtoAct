#pragma once
#include "DxLib.h"
#include "ControlShoot.h"

using namespace std;

//コンストラクタ
ControlShoot::ControlShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.0f, 0.0f, 16.0f);
	control_flag = true;
}

//デストラクタ
ControlShoot::~ControlShoot() {

}

//必ず行う更新
void ControlShoot::AbsUpdate() {

}

//消える時の動作
void ControlShoot::Erase(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	effect->SetEffect(3, x, y, 0.5f); //エフェクトを発生
}

//更新
void ControlShoot::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//一定時間ごとにエフェクトを発生
	if (time % 6 == 0 && 0 < time) {
		int effect_num = hit_player ? 9 : 8; //自機に当たるかでエフェクトを設定
		effect->SetEffect(effect_num, x, y, 0.2f); //エフェクトを発生
	}

	if (!control_flag) return; //コントロールされていなければ戻る

	//上が押されたら
	if (key->KeyCheckOnce(Up)) {
		angle = -0.5f * PI; //角度を上向きに
	}
	//下が押されたら
	if (key->KeyCheckOnce(Down)) {
		angle = 0.5f * PI; //角度を下向きに
	}
	//右が押されたら
	if (key->KeyCheckOnce(Right)) {
		angle = 0.0f; //角度を右向きに
	}
	//左が押されたら
	if (key->KeyCheckOnce(Left)) {
		angle = PI; //角度を左向きに
	}

	//攻撃ボタンが離されたら
	if (!key->KeyCheck(Attack)) {
		control_flag = false; //操作フラグをfalseに
	}

	SetSpeed(base_speed); //速度を設定
}

//描画
void ControlShoot::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetBulletImage(image_num, 0);
	camera->Draw(x, y, false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}