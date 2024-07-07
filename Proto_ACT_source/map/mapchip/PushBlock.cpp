#pragma once
#include "DxLib.h"
#include "PushBlock.h"

using namespace std;

//�R���X�g���N�^
PushBlock::PushBlock(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	pushed_flag = false;
	next_x = x;
	base_sx = 0.0f;
}

//�f�X�g���N�^
PushBlock::~PushBlock() {
	
}

//�K���s���X�V
void PushBlock::AbsUpdate() {

}

//�X�V
void PushBlock::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){
	//������Ă���Ȃ�
	if (pushed_flag) {
		float sub_x = fabsf(x - next_x); //���ݒn�ƖڕW�̍�
		//�ڕW�l�ɋ߂��Ȃ�
		if (sub_x < 1.0f) {
			x = next_x; //�ʒu�����킹��
			pushed_flag = false; //�����ꂽ�t���O��false��
			sx = 0.0f;
		}
		//�����Ȃ�
		else
		{
			float dec_x = 2.0f * size_x; //�������n�߂鋗��
			if (sub_x <= dec_x) {
				sx = base_sx * (sub_x / dec_x);
			}
		}

		//�~�܂����Ȃ�
		if (sx == 0.0f) {
			next_x = x; //������߂�
			pushed_flag = false; //�����ꂽ�t���O��false��
		}

		if (time % 3 == 0) {
			effect->SetEffect(2, x, y + (8.0f * size_y), 0.2f); //�G�t�F�N�g�𔭐�
		}
	}
	//������Ă��Ȃ��Ȃ�
	else
	{
		//��������������
		if (hit_left) {
			pushed_flag = true; //�����ꂽ�t���O��true��
			next_x = x + 4.0f * size_x; //�E�Ɉ����ڕW�l��
			base_sx = 4.0f;
			sx = base_sx;
		}
		//��������������
		if (hit_right) {
			pushed_flag = true; //�����ꂽ�t���O��true��
			next_x = x - 4.0f * size_x; //���Ɉ����ڕW�l��
			base_sx = -4.0f;
			sx = base_sx;
		}
	}
}

//�`��
void PushBlock::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetMapchipImage(image_num);
	//�摜�̑傫�����擾
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);

	camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}