#pragma once
#include "DxLib.h"
#include "MarkPoint.h"

using namespace std;

//�R���X�g���N�^
MarkPoint::MarkPoint(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	for (int i = 0; i < particle_num; i++) {
		particle_time[i] = i * 12; //�^�C�}�[��������
	}
}

//�f�X�g���N�^
MarkPoint::~MarkPoint() {

}

//�K���s���X�V
void MarkPoint::AbsUpdate() {

}

//�X�V
void MarkPoint::Update(shared_ptr<Sound> sound) {
	for (int i = 0; i < particle_num; i++) {
		particle_time[i]++; //�^�C�}�[�𑝉�
		//��莞�Ԃ��߂����玞�Ԃ�߂�
		if (60 <= particle_time[i]) {
			particle_time[i] = 0;
		}
	}
}

//�`��
void MarkPoint::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	for (int i = 0; i < particle_num; i++) {
		int hundle_num = particle_time[i] / 2; //�\������摜
		int hundle = image->GetEffectImage(image_num, hundle_num);
		float part_x = x + distance * particle_x[i]; //�G�t�F�N�g��x���W��ݒ�
		float part_y = y - (1.0f * particle_time[i]); //�G�t�F�N�g��y���W��ݒ�

		camera->Draw(part_x, part_y, false, angle, hundle, ex_rate, DX_BLENDMODE_NOBLEND);
	}
}