#pragma once
#include "DxLib.h"
#include "BeamWall.h"

using namespace std;

//コンストラクタ
BeamWall::BeamWall(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	
}

//デストラクタ
BeamWall::~BeamWall() {

}

//必ず行う更新
void BeamWall::AbsUpdate() {

}

//やられた時の動作
void BeamWall::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //消える
	effect->SetEffect(1, x, y); //爆発
}

//更新
void BeamWall::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	//一定時間ごとに弾を撃つ
	if (time % 12 == 0 && 0 < time) {
		bullet->SetBullet(5, x, y - 32.0f, 12.0f, -0.5f * PI); //弾を発射
		sound->PlaySoundEffect(7); //効果音を鳴らす
	}
}

//描画
void BeamWall::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}