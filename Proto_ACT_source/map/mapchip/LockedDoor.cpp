#pragma once
#include "DxLib.h"
#include "LockedDoor.h"

using namespace std;

//コンストラクタ
LockedDoor::LockedDoor(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	locked = true;
}

//デストラクタ
LockedDoor::~LockedDoor() {
	
}

//必ず行う更新
void LockedDoor::AbsUpdate() {

}

//更新
void LockedDoor::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){
	//自機の座標を取得
	float px = player->GetX();
	float py = player->GetY();

	//鍵がかかっているなら
	if (locked) {
		//自機が近いなら
		if (fabsf(px - x) < 24.0f + 4.0f * size_x && fabsf(py - y - 4.0f * size_y) < 4.0f * size_y) {
			int key = player->GetKeyNum(); //鍵の本数を取得
			//鍵を持っているなら
			if (0 < key) {
				locked = false;//開錠
				time = 0; //時間を初期化
				player->SetKeyNum(key - 1); //鍵を消費
				sound->PlaySoundEffect(13); //効果音を鳴らす
			}
		}
	}
	//開錠されているなら
	else {
		//一定時間したら消える
		if (30 <= time) {
			live_flag = false;
		}
	}
}

//描画
void LockedDoor::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetMapchipImage(image_num);
	//画像の大きさを取得
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);
	int pal_mode = locked ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_ADD;
	int pal_add = locked ? 0 : 196;

	camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, pal_mode, pal_add);
}