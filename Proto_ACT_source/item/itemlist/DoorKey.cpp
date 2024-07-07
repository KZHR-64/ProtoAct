#pragma once
#include "DxLib.h"
#include "DoorKey.h"

using namespace std;

//コンストラクタ
DoorKey::DoorKey(ItemManager* man, int num, float ini_x, float ini_y) : AbstractItem(man, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 16.0f);
}

//デストラクタ
DoorKey::~DoorKey() {
	mark.reset();
}

//アイテム取得時の処理
void DoorKey::ItemGet(shared_ptr<Player> player, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	int num = player->GetKeyNum();
	player->SetKeyNum(num + 1); //自機の持ち鍵を増やす
	sound->PlaySoundEffect(14); //効果音を鳴らす
	mark->SetEndFlag(true); //エフェクトを消去
}

//必ず行う更新
void DoorKey::AbsUpdate() {

}

//更新
void DoorKey::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (time == 0) {
		mark = effect->SetEffect(16, x, y + 24.0f, 0.1f);
	}
	if (mark) {
		mark->SetX(x);
		mark->SetY(y + 24.0f);
	}
}

//描画
void DoorKey::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetItemImage(image_num, 0);

	camera->Draw(x, y, false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}