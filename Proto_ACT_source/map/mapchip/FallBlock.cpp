#pragma once
#include "DxLib.h"
#include "FallBlock.h"

using namespace std;

//�R���X�g���N�^
FallBlock::FallBlock(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	fall_flag = false;
}

//�f�X�g���N�^
FallBlock::~FallBlock() {
	
}

//�K���s���X�V
void FallBlock::AbsUpdate() {

}

//�X�V
void FallBlock::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){
	//������Ȃ�
	if (fall_flag) {
		//���Ԃ��o�����Ȃ�
		if (time == 30) {
			sy = 4.0f; //�����鑬�x��ݒ�
		}
	}
	//�����Ȃ��Ȃ�
	else {
		//���@������Ă�����
		if (step) {
			fall_flag = true; //������悤��
			time = 0; //���Ԃ�������
		}
	}
}

//�`��
void FallBlock::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetMapchipImage(image_num);
	//�摜�̑傫�����擾
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);

	camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}