#pragma once
#include "DxLib.h"
#include "FallBomb2.h"

using namespace std;

//コンストラクタ
FallBomb2::FallBomb2(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(16.0f, 0.0f, 16.0f);
	SetHit(-16.0f, 0.0f, 16.0f);

	angle = 1.5f * PI;
	reverse = false;
	hit_map = false;
	flying_flag = true;
	SetSpeed(8.0f);
}

//デストラクタ
FallBomb2::~FallBomb2() {

}

//必ず行う更新
void FallBomb2::AbsUpdate() {
}

//やられた時の動作
void FallBomb2::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //消える
	effect->SetEffect(1, x, y); //爆発
}

//更新
void FallBomb2::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//着地したら爆発
	if (0 < time && adjusted) {
		bullet->SetBullet(8, x, y, 0.0f, 0.0f); //爆発を出す
		end_flag = true; //消える
	}

	float px = player->GetX(); //自機のx座標
	float top = (float)camera->GetScrollY(); //画面上

	//一定時間ごとにエフェクトを発生
	if (time % 12 == 0) {
		shared_ptr <AbstractEffect> eff;
		float ex = x + -32.0f * cosf(angle);
		float ey = y + -32.0f * sinf(angle);
		eff = effect->SetEffect(10, ex, ey, 0.5f);
		eff->SetAngle(angle - 0.5f * PI);
	}

	//画面外に出たら
	if (y < top - 32.0f && sy < -1.0f) {
		time = 0;
		SetSpeed(0.0f);
	}

	//画面外に出てからしばらく経ったら
	if (time == 12 && -0.1f < sy) {
		x = px - 64.0f + (float)GetRand(128);
		angle = 0.5f * PI; //角度を設定
		SetSpeed(4.0f);
		hit_map = true;
	}
}

//描画
void FallBomb2::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}