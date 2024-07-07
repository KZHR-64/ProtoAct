#pragma once
#include "DxLib.h"
#include "FallBomb.h"

using namespace std;

//コンストラクタ
FallBomb::FallBomb(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(16.0f, 0.0f, 16.0f);
	SetHit(-16.0f, 0.0f, 16.0f);

	angle = 0.5f * PI;
	reverse = false;
}

//デストラクタ
FallBomb::~FallBomb() {

}

//必ず行う更新
void FallBomb::AbsUpdate() {
}

//やられた時の動作
void FallBomb::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //消える
	effect->SetEffect(1, x, y); //爆発
}

//更新
void FallBomb::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//着地したら爆発
	if (0 < time && !jump_flag) {
		bullet->SetBullet(8, x, y, 0.0f, 0.0f); //爆発を出す
		end_flag = true; //消える
	}

	//一定時間ごとにエフェクトを発生
	if (time % 12 == 0) {
		shared_ptr <AbstractEffect> eff;
		float ex = x + -32.0f * cosf(angle);
		float ey = y + -32.0f * sinf(angle);
		eff = effect->SetEffect(10, ex, ey, 0.5f);
		eff->SetAngle(angle - 0.5f * PI);
	}
}

//描画
void FallBomb::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}