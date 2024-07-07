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
void NormalBlock::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect){

}

//描画
void NormalBlock::Draw() {
	int hundle = Image::Get_Instance()->GetMapchipImage(image);
	//画像の大きさを取得
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);

	Display::Get_Instance()->Draw(x, y + (float)(img_y / 2), LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}