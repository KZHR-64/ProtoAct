#pragma once
#include "DxLib.h"
#include "Cannon2.h"

using namespace std;

//コンストラクタ
Cannon2::Cannon2(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 24.0f);

	barrel_angle = 1.5f * PI;
	AbsUpdate();
}

//デストラクタ
Cannon2::~Cannon2() {

}

//必ず行う更新
void Cannon2::AbsUpdate() {
	float direction = (reverse) ? 1.0f : -1.0f; //向きに応じた計算用
	barrel_x = x + ((-16.0f * cosf(angle + barrel_angle) * direction));
	barrel_y = y + (16.0f * sinf(angle + barrel_angle));
}

//やられた時の動作
void Cannon2::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //消える
	effect->SetEffect(1, x, y); //爆発
}

//更新
void Cannon2::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float px = player->GetX(); //自機の座標
	float py = player->GetY(); //自機の座標

	//自機が回転の中心より上なら
	if (py <= y + 8.0f) {
		//追尾
		barrel_angle = Calculation::HomingSpin(barrel_angle, 0.0125f * PI, x, y, px, py);
	}

	//一定時間ごとに弾を撃つ
	if (time % 120 == 0 && 0 < time) {
		//弾の位置を設定
		float direction = (reverse) ? -1.0f : 1.0f; //向きに応じた計算用
		float bx = x + ((-32.0f * cosf(barrel_angle) * direction));
		float by = y + (32.0f * sinf(barrel_angle));

		bullet->SetBullet(5, bx, by, 12.0f, barrel_angle); //弾を発射
		sound->PlaySoundEffect(7); //効果音を鳴らす
	}
}

//描画
void Cannon2::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	int barrel_hundle = image->GetCharaImage(image_num, 1);
	camera->Draw(barrel_x, barrel_y, false, barrel_angle, barrel_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}