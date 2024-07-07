#pragma once
#include "DxLib.h"
#include "DesdragudArm.h"

using namespace std;

//コンストラクタ
DesdragudArm::DesdragudArm(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(24.0f, 0.0f, 24.0f);
	SetHit(-24.0f, 0.0f, 24.0f);
	SetHit(48.0f, 0.0f, 24.0f);
	SetHit(-48.0f, 0.0f, 24.0f);
	hit_map = false;

}

//デストラクタ
DesdragudArm::~DesdragudArm() {

}

//必ず行う更新
void DesdragudArm::AbsUpdate() {

}

//やられた時の動作
void DesdragudArm::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //消える
	effect->SetEffect(1, x, y); //爆発
}

//更新
void DesdragudArm::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

}

//描画
void DesdragudArm::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	float draw_angle = (reverse) ? angle * -1.0f : angle;

	camera->Draw(x, y, reverse, draw_angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}