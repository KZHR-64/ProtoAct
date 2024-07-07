#pragma once
#include "Camera.h"
#include "DxLib.h"

using namespace std;

Camera::Camera() {

	scroll_x = 0; //�������̃X�N���[����������
	scroll_y = 0; //�c�����̃X�N���[����������
	scroll_x_max = 0; //�X�N���[�������������
	scroll_y_max = 0; //�X�N���[�������������
	scroll_x_min = 0; //�X�N���[��������������
	scroll_y_min = 0; //�X�N���[��������������
	back_x_max = 0; //�X�N���[�������������
	back_y_max = 0; //�X�N���[�������������
}

//�f�X�g���N�^
Camera::~Camera() {

}

//�X�N���[���𔽉f�������`��
void Camera::Draw(float x, float y, bool reverse, float angle, int img, float ex_rate, int BlendMode, int Pal) {

	Display::Draw(x - (float)scroll_x, y - (float)scroll_y, reverse, angle, img, ex_rate, BlendMode, Pal);

}

//�w�i�̕`��
void Camera::BackDraw(float x, float y, int image, int BlendMode, int Pal) {
	//�w�i�摜�̑傫�����擾
	int size_x;
	int size_y;
	GetGraphSize(image, &size_x, &size_y);

	// ���ۂɎg���͔̂����̑傫��
	size_x = size_x / 2;
	size_y = size_y / 2;

	SetDrawBlendMode(BlendMode, Pal); //�`�惂�[�h�𔽉f

	DrawRotaGraph((int)x + size_x, (int)y + size_y, 1.0f, 0.0f, image, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�`�惂�[�h��߂�
}

//�X�N���[���𔽉f�����Ȃ��`��
void Camera::FixedDraw(float x, float y, bool lr, float angle, int image, float ex_rate, int BlendMode, int Pal) {
	SetDrawBlendMode(BlendMode, Pal); //�`�惂�[�h�𔽉f

	DrawRotaGraph((int)x, (int)y, ex_rate, angle, image, true, !lr);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�`�惂�[�h��߂�
}

//�����蔻��̕`��
void Camera::HitDraw(float x, float y, float hit_size) {
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192); //�`�惂�[�h�𔽉f

	//DrawCircle((int)x - scroll_x, (int)y - scroll_y, (int)hit_size, GetColor(255, 96, 96));

	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�`�惂�[�h��߂�
}

//�������ɂǂꂾ���X�N���[�����Ă��邩�Ԃ�
int Camera::GetScrollX() {
	return scroll_x;
}

//�c�����ɂǂꂾ���X�N���[�����Ă��邩�Ԃ�
int Camera::GetScrollY() {
	return scroll_y;
}

//�������ɂǂꂾ���X�N���[�������邩�ݒ肷��
void Camera::SetScrollX(float x) {
	scroll_x = (int)x - (WINDOW_X / 3);
	//�Œ�l����������ꍇ
	if (scroll_x < scroll_x_min) {
		scroll_x = scroll_x_min; //�X�N���[���͍Œ�l��
	}
	//�͂ݏo�����ꍇ
	if (scroll_x_max < scroll_x) {
		scroll_x = scroll_x_max;
	}
}

//�c�����ɂǂꂾ���X�N���[�������邩�ݒ肷��
void Camera::SetScrollY(float y) {
	scroll_y = (int)y - (WINDOW_Y / 2);
	//�}�C�i�X�ɂȂ����ꍇ
	if (scroll_y < scroll_y_min) {
		scroll_y = scroll_y_min; //�X�N���[���͍Œ�l��
	}

	//�͂ݏo�����ꍇ
	if (scroll_y_max < scroll_y) {
		scroll_y = scroll_y_max;
	}
}

//�������̃X�N���[��������Ԃ�
int Camera::GetScrollXMin() {
	return scroll_x_min;
}

//�c�����̃X�N���[��������Ԃ�
int Camera::GetScrollYMin() {
	return scroll_y_min;
}

//�������̃X�N���[�������Ԃ�
int Camera::GetScrollXMax() {
	return scroll_x_max + WINDOW_X;
}

//�c�����̃X�N���[�������Ԃ�
int Camera::GetScrollYMax() {
	return scroll_y_max + WINDOW_Y;
}

//�������̃X�N���[��������ݒ肷��
void Camera::SetScrollXMin(int x) {
	scroll_x_min = x;
}

//�c�����̃X�N���[��������ݒ肷��
void Camera::SetScrollYMin(int y) {
	scroll_y_min = y;
}

//�������̃X�N���[�������ݒ肷��
void Camera::SetScrollXMax(int x) {
	back_x_max = scroll_x_max;
	scroll_x_max = x - WINDOW_X;
}

//�c�����̃X�N���[�������ݒ肷��
void Camera::SetScrollYMax(int y) {
	back_y_max = scroll_y_max;
	scroll_y_max = y - WINDOW_Y;
}

//�������̃X�N���[�������߂�
void Camera::ReSetScrollXMax() {
	scroll_x_max = back_x_max;
}

//�c�����̃X�N���[�������߂�
void Camera::ReSetScrollYMax() {
	scroll_y_max = back_y_max;
}

//�������ɂǂꂾ���X�N���[���������Ԃ�
int Camera::GetScrollDifX() {
	return scroll_dif_x;
}

//�c�����ɂǂꂾ���X�N���[���������Ԃ�
int Camera::GetScrollDifY() {
	return scroll_dif_y;
}