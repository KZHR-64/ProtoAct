#pragma once
#include "DxLib.h"
#include "../Define.h"
#include <math.h>

//�v�Z�֘A
class Calculation {
private:
	Calculation() {};
public:
	static float GetPartsAngle(float bangle, float pangle); //�p�[�c�̊p�x��Ԃ�
	static float GetPartsX(float bangle, float axis, float pdist, float pangle, bool reverse); //�p�[�c��x���W��Ԃ��i��̊p�x�A��]���̍��W�A��]�̔��a�A�p�[�c�̏����p�x�A�����j
	static float GetPartsY(float bangle, float ax, float ay, float px, float py, bool reverse); //�p�[�c��y���W��Ԃ��i��̊p�x�A��]���̍��W�A��]�̔��a�A�����j
	static float LockOn(float cx, float cy, float dx, float dy); //�ڕW�Ɍ����Ċp�x��ݒ�(������x,y���W�A�ڕW��x,y���W)
	static float HomingSpin(float angle, float set_spin_speed, float x, float y, float set_x, float set_y); //�ڕW�Ɍ����ĉ�]�i�p�x�A��]���x�A���W�A�ڕW�̍��W�j
	static float HomingSpin(float angle, float set_spin_speed, float target_angle); //�ڕW�Ɍ����ĉ�]�i�p�x�A��]���x�A�ڕW�̊p�x�j
	static float Spin(float angle, float set_spin_speed, float spin_max, float spin_min); //��]������i�p�x�A��]���x�A����A�����j
};