#pragma once
#include "DxLib.h"
#include "../Define.h"

//�`��֘A
class Display {
private:

public:
	Display(); //�R���X�g���N�^
	static void Draw(float x, float y, bool reverse, float angle, int image, float ex_rate = 1.0f, int BlendMode = DX_BLENDMODE_NOBLEND, int Pal = 0); //�`��(x,y���W�A���E�̌����A�p�x�A�摜�A�u�����h���[�h�A�p�����[�^)
	static void BackDraw(float x, float y, int image, int BlendMode = DX_BLENDMODE_NOBLEND, int Pal = 0); //�w�i�̕`��(x,y���W�A�摜�A�u�����h���[�h�A�p�����[�^)
	static void HitDraw(float x, float y, float hit_size); //�����蔻��̕`��
};