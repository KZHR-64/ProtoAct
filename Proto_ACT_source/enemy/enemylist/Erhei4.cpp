#pragma once
#include "DxLib.h"
#include "Erhei4.h"

using namespace std;

//コンストラクタ
Erhei4::Erhei4(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 32.0f);
}

//デストラクタ
Erhei4::~Erhei4() {

}

//必ず行う更新
void Erhei4::AbsUpdate() {

}

//やられた時の動作
void Erhei4::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //消える
	effect->SetEffect(1, x, y); //爆発
}

//更新
void Erhei4::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	//一定時間経過していないなら
	if (time < 120) {
		float px = player->GetX(); //自機の座標
		//自機のいる方向を向く
		reverse = px < x;
	}
	//一定時間経過したら
	else
	{
		float max_speed = (reverse) ? -12.0f : 12.0f;
		if (fabsf(sx) < 0.5f) {
			//速度を設定
			sx = (reverse) ? -1.0f : 1.0f;
		}
		sx *= 1.05f;  //徐々に加速
		//上限を設定
		if (fabsf(max_speed) < fabsf(sx)) {
			sx = max_speed;
		}
	}
}

//描画
void Erhei4::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	int arm_hundle = image->GetCharaImage(7, 0);
	float arm_x = (reverse) ? 16.0f : -16.0f; //向きに応じて武器の位置を設定

	camera->Draw(x - arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x + arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}