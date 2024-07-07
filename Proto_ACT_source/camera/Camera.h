#pragma once
#include "DxLib.h"
#include "../Define.h"
#include "..\tool\Display.h"
#include "..\tool\Calculation.h"
#include "..\system\Image.h"
#include <memory>
#include <thread>
#include <vector>

class ModeManager;
class EnvSetting;
class Key;
class Sound;
class Image;
class Fps;

class Camera {
private:

	int scroll_x; //�������̃X�N���[��
	int scroll_y; //�c�����̃X�N���[��
	int scroll_x_min; //�������̃X�N���[������
	int scroll_x_max; //�������̃X�N���[�����
	int scroll_y_min; //�c�����̃X�N���[������
	int scroll_y_max; //�c�����̃X�N���[�����
	int scroll_dif_x; //���ɂǂꂾ���X�N���[��������
	int scroll_dif_y; //�c�ɂǂꂾ���X�N���[��������
	int back_x_max; //�ύX�O�̃X�N���[�����
	int back_y_max; //�ύX�O�̃X�N���[�����

public:
	Camera(); //�R���X�g���N�^
	~Camera(); //�f�X�g���N�^
	void Draw(float x, float y, bool reverse, float angle, int img, float ex_rate = 1.0f, int BlendMode = DX_BLENDMODE_NOBLEND, int Pal = 0); //�X�N���[���𔽉f�������`��(x,y���W�A���E�̌����A�p�x�A�摜�A�u�����h���[�h�A�p�����[�^)
	void BackDraw(float x, float y, int img, int BlendMode = DX_BLENDMODE_NOBLEND, int Pal = 0); //�w�i�̕`��(x,y���W�A�摜�A�u�����h���[�h�A�p�����[�^)
	void FixedDraw(float x, float y, bool lr, float angle, int img, float ex_rate = 1.0f, int BlendMode = DX_BLENDMODE_NOBLEND, int Pal = 0); //�X�N���[���𔽉f�����Ȃ��`��(x,y���W�A���E�̌����A�p�x�A�摜�A�{���A�u�����h���[�h�A�p�����[�^)
	void HitDraw(float x, float y, float hit_size); //�����蔻��̕`��
	int GetScrollX(); //�������ɂǂꂾ���X�N���[�����Ă��邩�Ԃ�
	int GetScrollY(); //�c�����ɂǂꂾ���X�N���[�����Ă��邩�Ԃ�
	void SetScrollX(float x); //�������ɂǂꂾ���X�N���[�������邩�ݒ肷��(��ƂȂ�x���W)
	void SetScrollY(float y); //�c�����ɂǂꂾ���X�N���[�������邩�ݒ肷��(��ƂȂ�y���W)
	int GetScrollXMin(); //�������̃X�N���[��������Ԃ�
	int GetScrollYMin(); //�c�����̃X�N���[��������Ԃ�
	int GetScrollXMax(); //�������̃X�N���[�������Ԃ�
	int GetScrollYMax(); //�c�����̃X�N���[�������Ԃ�
	void SetScrollXMin(int x); //�������̃X�N���[��������ݒ肷��(�}�b�v�̍���)
	void SetScrollYMin(int y); //�c�����̃X�N���[��������ݒ肷��(�}�b�v�̏�)
	void SetScrollXMax(int x); //�������̃X�N���[�������ݒ肷��(�}�b�v�̉E��)
	void SetScrollYMax(int y); //�c�����̃X�N���[�������ݒ肷��(�}�b�v�̉�)
	void ReSetScrollXMax(); //�������̃X�N���[�������߂�
	void ReSetScrollYMax(); //�c�����̃X�N���[�������߂�
	int GetScrollDifX(); //�������ɂǂꂾ���X�N���[���������Ԃ�
	int GetScrollDifY(); //�c�����ɂǂꂾ���X�N���[���������Ԃ�
};