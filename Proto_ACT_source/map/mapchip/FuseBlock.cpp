#pragma once
#include "DxLib.h"
#include "FuseBlock.h"

using namespace std;

//コンストラクタ
FuseBlock::FuseBlock(MapChipManager* man, int num) : AbstractMapChip(man, num) {

}

//デストラクタ
FuseBlock::~FuseBlock() {

}

//必ず行う更新
void FuseBlock::AbsUpdate() {

}

//更新
void FuseBlock::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {

	//消える際に上下左右に誘爆する
	if (end_flag) {
		shared_ptr<AbstractBullet> blast = bullet->SetBullet(4, x - (8.0f * size_x), y + 4.0f * size_y, 0.0f, 0.0f);
		blast->SetEndTime(12); //12フレーム後に消えるよう設定
		blast = bullet->SetBullet(4, x + (8.0f * size_x), y + 4.0f * size_y, 0.0f, 0.0f);
		blast->SetEndTime(12); //12フレーム後に消えるよう設定
		blast = bullet->SetBullet(4, x, y - (4.0f * size_y), 0.0f, 0.0f);
		blast->SetEndTime(12); //12フレーム後に消えるよう設定
		blast = bullet->SetBullet(4, x, y + (12.0f * size_y), 0.0f, 0.0f);
		blast->SetEndTime(12); //12フレーム後に消えるよう設定

		shared_ptr<AbstractEffect> exp = effect->SetEffect(1, x, y + 4.0f * size_y, 0.5f); //爆発
	}
}

//描画
void FuseBlock::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetMapchipImage(image_num);
	//画像の大きさを取得
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);

	camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}