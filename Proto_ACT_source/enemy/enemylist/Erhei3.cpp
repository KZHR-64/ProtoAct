#pragma once
#include "DxLib.h"
#include "Erhei3.h"

using namespace std;

//コンストラクタ
Erhei3::Erhei3(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 32.0f);
}

//デストラクタ
Erhei3::~Erhei3() {

}

//必ず行う更新
void Erhei3::AbsUpdate() {

}

//やられた時の動作
void Erhei3::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //消える
	effect->SetEffect(1, x, y); //爆発
}

//更新
void Erhei3::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	
	float px = player->GetX(); //自機の座標
	//自機のいる方向を向く
	reverse = px < x;

	//一定時間ごとにミサイルを撃つ
	if (time % 90 == 0 && 0 < time) {
		shared_ptr<AbstractEnemy> missile;
		float shoot_x = (reverse ? -8.0f : 8.0f); //銃口
		float shoot_angle = (reverse ? PI : 0.0f); //向きによって撃つ角度を決定
		missile = manager->SetEnemy(8, x + shoot_x, y - 12.0f); //ミサイルを撃つ
		missile->SetAngle(shoot_angle); //角度を設定
		missile->SetXSpeed(8.0f * cosf(shoot_angle)); //速度を設定
		sound->PlaySoundEffect(9); //効果音を鳴らす
	}
}

//描画
void Erhei3::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	int arm_hundle = image->GetCharaImage(6, 0);
	float arm_x = (reverse) ? 16.0f : -16.0f; //向きに応じて武器の位置を設定

	camera->Draw(x - arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x + arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}