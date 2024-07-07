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
void NormalBlock::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){

	//������ۂɏ�����
	if (end_flag) {
		shared_ptr<AbstractEffect> exp = effect->SetEffect(2, x, y + 4.0f * size_y, 0.3f); //����
	}
}

//�`��
void NormalBlock::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	//�A������Ȃ�
	if (2 <= link_x) {
		for (int i = 0; i < link_x; i++) {
			int num = image_num;
			//�I�[
			if (i == link_x - 1 && i != 0) {
				num += link_img_x2;
			}
			//�r��
			else if (0 < i) {
				num += link_img_x1;
			}
			int hundle = image->GetMapchipImage(num);
			//�摜�̑傫�����擾
			int img_x;
			int img_y;
			GetGraphSize(hundle, &img_x, &img_y);
			float pos_x = x - 4.0f * size_x + 16.0f;
			camera->Draw(pos_x + 32.0f * i, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
			//DrawFormatString((int)pos_x + 32 * i, (int)y, GetColor(255, 0, 0), "%d", image_num);
		}
	}
	//���Ȃ��Ȃ�
	else {
		int hundle = image->GetMapchipImage(image_num);
		//�摜�̑傫�����擾
		int img_x;
		int img_y;
		GetGraphSize(hundle, &img_x, &img_y);
		camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	}
}