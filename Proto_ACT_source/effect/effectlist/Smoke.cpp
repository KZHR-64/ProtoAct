#pragma once
#include "DxLib.h"
#include "Smoke.h"

using namespace std;

//�R���X�g���N�^
Smoke::Smoke(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	hundle_num = 0;
}

//�f�X�g���N�^
Smoke::~Smoke() {

}

//�K���s���X�V
void Smoke::AbsUpdate() {

}

//�X�V
void Smoke::Update(shared_ptr<Sound> sound) {
	if (time == 0) {
		sound->PlaySoundEffect(12); //���ʉ���炷
	}

	//��莞�Ԃ��߂��������
	if (30 <= time) {
		end_flag = true;
	}
	else {
		//�\������摜������
		hundle_num = time / 3;
	}

}

//�`��
void Smoke::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetEffectImage(image_num, hundle_num);

	camera->Draw(x, y, false, angle, hundle, ex_rate, DX_BLENDMODE_NOBLEND);
}