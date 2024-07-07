#pragma once
#include "DxLib.h"
#include "NormalBlock.h"

using namespace std;

//�R���X�g���N�^
NormalBlock::NormalBlock(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	
}

//�f�X�g���N�^
NormalBlock::~NormalBlock() {
	
}

//�K���s���X�V
void NormalBlock::AbsUpdate() {

}

//�X�V
void NormalBlock::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect){

}

//�`��
void NormalBlock::Draw() {
	int hundle = Image::Get_Instance()->GetMapchipImage(image);
	//�摜�̑傫�����擾
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);

	Display::Get_Instance()->Draw(x, y + (float)(img_y / 2), LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}