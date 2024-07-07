#pragma once
#include "DxLib.h"
#include "LightSphere.h"

using namespace std;

//�R���X�g���N�^
LightSphere::LightSphere(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	hundle_num = 0;
}

//�f�X�g���N�^
LightSphere::~LightSphere() {

}

//�K���s���X�V
void LightSphere::AbsUpdate() {

}

//�X�V
void LightSphere::Update(shared_ptr<Sound> sound) {
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
void LightSphere::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetEffectImage(image_num, hundle_num);

	camera->Draw(x, y, false, angle, hundle, ex_rate, DX_BLENDMODE_NOBLEND);
}