#pragma once
#include "DxLib.h"
#include "PushBlock.h"

using namespace std;

//コンストラクタ
PushBlock::PushBlock(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	pushed_flag = false;
	next_x = x;
	base_sx = 0.0f;
}

//デストラクタ
PushBlock::~PushBlock() {
	
}

//必ず行う更新
void PushBlock::AbsUpdate() {

}

//更新
void PushBlock::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){
	//押されているなら
	if (pushed_flag) {
		float sub_x = fabsf(x - next_x); //現在地と目標の差
		//目標値に近いなら
		if (sub_x < 1.0f) {
			x = next_x; //位置を合わせる
			pushed_flag = false; //押されたフラグをfalseに
			sx = 0.0f;
		}
		//遠いなら
		else
		{
			float dec_x = 2.0f * size_x; //減速し始める距離
			if (sub_x <= dec_x) {
				sx = base_sx * (sub_x / dec_x);
			}
		}

		//止まったなら
		if (sx == 0.0f) {
			next_x = x; //あきらめる
			pushed_flag = false; //押されたフラグをfalseに
		}

		if (time % 3 == 0) {
			effect->SetEffect(2, x, y + (8.0f * size_y), 0.2f); //エフェクトを発生
		}
	}
	//押されていないなら
	else
	{
		//左が当たったら
		if (hit_left) {
			pushed_flag = true; //押されたフラグをtrueに
			next_x = x + 4.0f * size_x; //右に一つ分を目標値に
			base_sx = 4.0f;
			sx = base_sx;
		}
		//左が当たったら
		if (hit_right) {
			pushed_flag = true; //押されたフラグをtrueに
			next_x = x - 4.0f * size_x; //左に一つ分を目標値に
			base_sx = -4.0f;
			sx = base_sx;
		}
	}
}

//描画
void PushBlock::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetMapchipImage(image_num);
	//画像の大きさを取得
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);

	camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}