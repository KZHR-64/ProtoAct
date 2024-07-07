#pragma once
#include "DxLib.h"
#include "BlackOut.h"

using namespace std;

//�R���X�g���N�^
BlackOut::BlackOut(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	pal = 0;
}

//�f�X�g���N�^
BlackOut::~BlackOut() {

}

//�K���s���X�V
void BlackOut::AbsUpdate() {

}

//�X�V
void BlackOut::Update(shared_ptr<Sound> sound) {

}

//�`��
void BlackOut::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal); //�`�惂�[�h�𔽉f

	DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�`�惂�[�h��߂�
}