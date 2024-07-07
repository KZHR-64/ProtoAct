#pragma once
#include "DxLib.h"
#include "NormalBlock.h"

using namespace std;

//コンストラクタ
NormalBlock::NormalBlock(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	
}

//デストラクタ
NormalBlock::~NormalBlock() {
	
}

//必ず行う更新
void NormalBlock::AbsUpdate() {

}

//更新
void NormalBlock::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){

	//消える際に小爆発
	if (end_flag) {
		shared_ptr<AbstractEffect> exp = effect->SetEffect(2, x, y + 4.0f * size_y, 0.3f); //爆発
	}
}

//描画
void NormalBlock::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	//連結するなら
	if (2 <= link_x) {
		for (int i = 0; i < link_x; i++) {
			int num = image_num;
			//終端
			if (i == link_x - 1 && i != 0) {
				num += link_img_x2;
			}
			//途中
			else if (0 < i) {
				num += link_img_x1;
			}
			int hundle = image->GetMapchipImage(num);
			//画像の大きさを取得
			int img_x;
			int img_y;
			GetGraphSize(hundle, &img_x, &img_y);
			float pos_x = x - 4.0f * size_x + 16.0f;
			camera->Draw(pos_x + 32.0f * i, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
			//DrawFormatString((int)pos_x + 32 * i, (int)y, GetColor(255, 0, 0), "%d", image_num);
		}
	}
	//しないなら
	else {
		int hundle = image->GetMapchipImage(image_num);
		//画像の大きさを取得
		int img_x;
		int img_y;
		GetGraphSize(hundle, &img_x, &img_y);
		camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	}
}