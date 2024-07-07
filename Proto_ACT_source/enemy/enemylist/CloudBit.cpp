#pragma once
#include "DxLib.h"
#include "CloudBit.h"

using namespace std;

//コンストラクタ
CloudBit::CloudBit(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {

	flying_flag = true;
	hit_map = false;

	SetHit(0.0f, 0.0f, 32.0f);
}

//デストラクタ
CloudBit::~CloudBit() {

}

//必ず行う更新
void CloudBit::AbsUpdate() {
	
}

//やられた時の動作
void CloudBit::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //消える
	effect->SetEffect(1, x, y); //爆発
}

//更新
void CloudBit::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//常に全回復
	hp = max_hp;
}

//描画
void CloudBit::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);

	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}