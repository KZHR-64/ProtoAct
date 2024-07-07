#pragma once
#include "DxLib.h"
#include "HomingMissile.h"

using namespace std;

//コンストラクタ
HomingMissile::HomingMissile(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(16.0f, 0.0f, 16.0f);
	SetHit(-16.0f, 0.0f, 16.0f);

	reverse = false;
	flying_flag = true;
}

//デストラクタ
HomingMissile::~HomingMissile() {

}

//必ず行う更新
void HomingMissile::AbsUpdate() {
}

//やられた時の動作
void HomingMissile::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //消える
	effect->SetEffect(1, x, y); //爆発
}

//更新
void HomingMissile::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float px = player->GetX(); //自機の座標
	float py = player->GetY(); //自機の座標

	//着地したら爆発
	if (0 < time && adjusted) {
		Defeat(effect, sound);
	}

	if (30 < time && time < 300) {
		angle = Calculation::HomingSpin(angle, 0.01f * PI, x, y, px, py); //自機を追尾
	}
	//速度を設定
	SetSpeed(4.0f);
}

//描画
void HomingMissile::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}