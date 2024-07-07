#pragma once
#include "DxLib.h"
#include "Calculation.h"
#include "../Define.h"



//�p�[�c��x���W��Ԃ�
float Calculation::GetPartsX(float bangle, float axis, float pdist, float pangle, bool reverse) {
	float x = 0.0f; //x���W
	float direction = (reverse) ? -1.0f : 1.0f; //�����ɉ������v�Z�p

	//x = ((right_leg.def_distance * cosf(sum_angle) * direction)) + (right_leg.spin_point * cosf(sum_spin) * direction);
	
	return x;
}

//�p�[�c��y���W��Ԃ�
float Calculation::GetPartsY(float bangle, float ax, float ay, float px, float py, bool reverse) {
	float y = 0.0f; //y���W
	float direction = (reverse) ? -1.0f : 1.0f; //�����ɉ������v�Z�p
	ax *= direction; //�����ɍ��킹�ʒu���v�Z
	px *= direction; //�����ɍ��킹�ʒu���v�Z

	//��]���ƃp�[�c�̃x�N�g���Ɗp�x�����ꂼ��v�Z
	float axis_angle = atan2f(ay, ax);
	float axis_vec = sqrtf((ax * ax) + (ay * ay));
	float spin_angle = atan2f(py, px);
	float spin_vec = sqrtf((px * px) + (py * py));

	//y = (pdist * sinf(sum_angle) * direction) + (right_leg.spin_point * sinf(sum_spin));
	
	return y;
}

//�ڕW�Ɍ����Ċp�x��ݒ�
float Calculation::LockOn(float cx, float cy, float dx, float dy) {
	float angle = 0.0f; //�p�x

	angle = atan2f(dy - cy, dx - cx);

	return angle; //�p�x��Ԃ�
}

//�ڕW�Ɍ����ĉ�]
float Calculation::HomingSpin(float angle, float set_spin_speed, float x, float y, float set_x, float set_y) {
	
	//�ڕW�ւ̊p�x���v�Z
	float target_angle = atan2f(set_y - y, set_x - x);

	//�L�����̊p�x���v�Z�p�ɕҏW
	float base_angle = atan2f(sinf(angle), cosf(angle));

	//�����̊p�x�̐����������ꍇ
	if (0.0f <= target_angle * base_angle) {
		//�p�x�̍�����]�p�x�����̏ꍇ
		if (fabsf(target_angle - base_angle) <= set_spin_speed) {
			base_angle = target_angle;
		}
		//�p�x�ȏ�̏ꍇ
		else {
			//�ڕW�p�x���傫���ꍇ�͑���
			if (base_angle < target_angle) {
				base_angle += set_spin_speed;
			}
			//��������Έ���
			else {
				base_angle -= set_spin_speed;
			}
		}
	}
	//�قȂ�ꍇ
	else {
		//�E���A���̊p�x�̍����v�Z
		float sub_right = fabsf(target_angle) + fabsf(base_angle);
		float sub_left = fabsf(2.0f * PI - sub_right);
		//��]������ݒ�
		float spin = (0.0f < base_angle) ? set_spin_speed : -set_spin_speed;
		//�ǂ��炩�̊p�x�̍�����]�p�x�ȉ��̏ꍇ
		if (sub_right <= set_spin_speed || sub_left <= set_spin_speed) {
			base_angle = target_angle;
		}
		//�p�x�ȏ�̏ꍇ
		else {
			//�������������։�]
			if (sub_right < sub_left) {
				base_angle -= spin;
			}
			else {
				base_angle += spin;
			}
		}
	}
	return base_angle; //�p�x��Ԃ�
}

//�ڕW�Ɍ����ĉ�]
float Calculation::HomingSpin(float angle, float set_spin_speed, float target_angle) {
	
	//�L�����̊p�x���v�Z�p�ɕҏW
	float set_angle = atan2f(sinf(angle), cosf(angle));
	//�ڕW�p�x���v�Z�p�ɕҏW
	target_angle = atan2f(sinf(target_angle), cosf(target_angle));

	//�����̊p�x�̐����������ꍇ
	if (0.0f <= target_angle * set_angle) {
		//�p�x�̍�����]�p�x�����̏ꍇ
		if (fabsf(target_angle - set_angle) <= set_spin_speed) {
			set_angle = target_angle;
		}
		//�p�x�ȏ�̏ꍇ
		else {
			//�ڕW�p�x���傫���ꍇ�͑���
			if (set_angle < target_angle) {
				set_angle += set_spin_speed;
			}
			//��������Έ���
			else {
				set_angle -= set_spin_speed;
			}
		}
	}
	//�قȂ�ꍇ
	else {
		//�E���A���̊p�x�̍����v�Z
		float sub_right = fabsf(target_angle) + fabsf(set_angle);
		float sub_left = fabsf(2.0f * PI - sub_right);
		//��]������ݒ�
		float spin = (0.0f < set_angle) ? set_spin_speed : -set_spin_speed;
		//�ǂ��炩�̊p�x�̍�����]�p�x�ȉ��̏ꍇ
		if (sub_right <= set_spin_speed || sub_left <= set_spin_speed) {
			set_angle = target_angle;
		}
		//�p�x�ȏ�̏ꍇ
		else {
			//�������������։�]
			if (sub_right < sub_left) {
				set_angle -= spin;
			}
			else {
				set_angle += spin;
			}
		}
	}

	return set_angle;
}

//��]������
float Calculation::Spin(float angle, float set_spin_speed, float spin_max, float spin_min) {
	angle += set_spin_speed; //�p�[�c����]������

	//����ɒB������
	if (spin_max < angle) {
		angle = spin_max; //�p�x�𒲐�
	}
	//�����ɒB������
	if (angle < spin_min) {
		angle = spin_min; //�p�x�𒲐�
	}

	return angle; //�p�x��Ԃ�
}