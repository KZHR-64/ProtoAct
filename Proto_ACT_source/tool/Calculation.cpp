#pragma once
#include "DxLib.h"
#include "Calculation.h"
#include "../Define.h"



//パーツのx座標を返す
float Calculation::GetPartsX(float bangle, float axis, float pdist, float pangle, bool reverse) {
	float x = 0.0f; //x座標
	float direction = (reverse) ? -1.0f : 1.0f; //向きに応じた計算用

	//x = ((right_leg.def_distance * cosf(sum_angle) * direction)) + (right_leg.spin_point * cosf(sum_spin) * direction);
	
	return x;
}

//パーツのy座標を返す
float Calculation::GetPartsY(float bangle, float ax, float ay, float px, float py, bool reverse) {
	float y = 0.0f; //y座標
	float direction = (reverse) ? -1.0f : 1.0f; //向きに応じた計算用
	ax *= direction; //向きに合わせ位置を計算
	px *= direction; //向きに合わせ位置を計算

	//回転軸とパーツのベクトルと角度をそれぞれ計算
	float axis_angle = atan2f(ay, ax);
	float axis_vec = sqrtf((ax * ax) + (ay * ay));
	float spin_angle = atan2f(py, px);
	float spin_vec = sqrtf((px * px) + (py * py));

	//y = (pdist * sinf(sum_angle) * direction) + (right_leg.spin_point * sinf(sum_spin));
	
	return y;
}

//目標に向けて角度を設定
float Calculation::LockOn(float cx, float cy, float dx, float dy) {
	float angle = 0.0f; //角度

	angle = atan2f(dy - cy, dx - cx);

	return angle; //角度を返す
}

//目標に向けて回転
float Calculation::HomingSpin(float angle, float set_spin_speed, float x, float y, float set_x, float set_y) {
	
	//目標への角度を計算
	float target_angle = atan2f(set_y - y, set_x - x);

	//キャラの角度を計算用に編集
	float base_angle = atan2f(sinf(angle), cosf(angle));

	//両方の角度の正負が同じ場合
	if (0.0f <= target_angle * base_angle) {
		//角度の差が回転角度未満の場合
		if (fabsf(target_angle - base_angle) <= set_spin_speed) {
			base_angle = target_angle;
		}
		//角度以上の場合
		else {
			//目標角度が大きい場合は足す
			if (base_angle < target_angle) {
				base_angle += set_spin_speed;
			}
			//小さければ引く
			else {
				base_angle -= set_spin_speed;
			}
		}
	}
	//異なる場合
	else {
		//右側、左の角度の差を計算
		float sub_right = fabsf(target_angle) + fabsf(base_angle);
		float sub_left = fabsf(2.0f * PI - sub_right);
		//回転方向を設定
		float spin = (0.0f < base_angle) ? set_spin_speed : -set_spin_speed;
		//どちらかの角度の差が回転角度以下の場合
		if (sub_right <= set_spin_speed || sub_left <= set_spin_speed) {
			base_angle = target_angle;
		}
		//角度以上の場合
		else {
			//差が小さい方へ回転
			if (sub_right < sub_left) {
				base_angle -= spin;
			}
			else {
				base_angle += spin;
			}
		}
	}
	return base_angle; //角度を返す
}

//目標に向けて回転
float Calculation::HomingSpin(float angle, float set_spin_speed, float target_angle) {
	
	//キャラの角度を計算用に編集
	float set_angle = atan2f(sinf(angle), cosf(angle));
	//目標角度を計算用に編集
	target_angle = atan2f(sinf(target_angle), cosf(target_angle));

	//両方の角度の正負が同じ場合
	if (0.0f <= target_angle * set_angle) {
		//角度の差が回転角度未満の場合
		if (fabsf(target_angle - set_angle) <= set_spin_speed) {
			set_angle = target_angle;
		}
		//角度以上の場合
		else {
			//目標角度が大きい場合は足す
			if (set_angle < target_angle) {
				set_angle += set_spin_speed;
			}
			//小さければ引く
			else {
				set_angle -= set_spin_speed;
			}
		}
	}
	//異なる場合
	else {
		//右側、左の角度の差を計算
		float sub_right = fabsf(target_angle) + fabsf(set_angle);
		float sub_left = fabsf(2.0f * PI - sub_right);
		//回転方向を設定
		float spin = (0.0f < set_angle) ? set_spin_speed : -set_spin_speed;
		//どちらかの角度の差が回転角度以下の場合
		if (sub_right <= set_spin_speed || sub_left <= set_spin_speed) {
			set_angle = target_angle;
		}
		//角度以上の場合
		else {
			//差が小さい方へ回転
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

//回転させる
float Calculation::Spin(float angle, float set_spin_speed, float spin_max, float spin_min) {
	angle += set_spin_speed; //パーツを回転させる

	//上限に達したら
	if (spin_max < angle) {
		angle = spin_max; //角度を調整
	}
	//下限に達したら
	if (angle < spin_min) {
		angle = spin_min; //角度を調整
	}

	return angle; //角度を返す
}