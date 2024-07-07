#pragma once
#include "DxLib.h"
#include "FallBlock.h"

using namespace std;

//コンストラクタ
FallBlock::FallBlock(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	fall_flag = false;
}

//デストラクタ
FallBlock::~FallBlock() {
	
}

//必ず行う更新
void FallBlock::AbsUpdate() {

}

//更新
void FallBlock::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){
	//落ちるなら
	if (fall_flag) {
		//時間が経ったなら
		if (time == 30) {
			sy = 4.0f; //落ちる速度を設定
		}
	}
	//落ちないなら
	else {
		//自機が乗っていたら
		if (step) {
			fall_flag = true; //落ちるように
			time = 0; //時間を初期化
		}
	}
}

//描画
void FallBlock::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetMapchipImage(image_num);
	//画像の大きさを取得
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);

	camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}