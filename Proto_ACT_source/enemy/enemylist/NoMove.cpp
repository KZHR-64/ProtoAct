#pragma once
#include "DxLib.h"
#include "NoMove.h"

using namespace std;

//コンストラクタ
NoMove::NoMove(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 32.0f);
}

//デストラクタ
NoMove::~NoMove() {

}

//必ず行う更新
void NoMove::AbsUpdate() {
	
}

//やられた時の動作
void NoMove::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //消える
	effect->SetEffect(1, x, y); //爆発
}

//更新
void NoMove::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	float px = player->GetX(); //自機の座標
	//自機のいる方向を向く
	reverse = px < x;
}

//描画
void NoMove::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	int arm_hundle = image->GetCharaImage(5, 0);
	float arm_x = (reverse) ? 16.0f : -16.0f; //向きに応じて武器の位置を設定

	camera->Draw(x - arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x + arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}