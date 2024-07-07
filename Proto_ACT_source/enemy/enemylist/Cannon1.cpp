#pragma once
#include "DxLib.h"
#include "Cannon1.h"

using namespace std;

//コンストラクタ
Cannon1::Cannon1(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 24.0f);
}

//デストラクタ
Cannon1::~Cannon1() {

}

//必ず行う更新
void Cannon1::AbsUpdate() {

}

//やられた時の動作
void Cannon1::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //消える
	effect->SetEffect(1, x, y); //爆発
}

//更新
void Cannon1::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	//一定時間ごとに弾を撃つ
	if (time % 120 == 0 && 0 < time) {
		bullet->SetBullet(5, x, y - 32.0f, 12.0f, -0.5f * PI); //弾を発射
		sound->PlaySoundEffect(7); //効果音を鳴らす
	}
}

//描画
void Cannon1::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	int barrel_hundle = image->GetCharaImage(image_num, 1);
	camera->Draw(x, y - 16.0f, false, -0.5f * PI, barrel_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}