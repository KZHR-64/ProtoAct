#pragma once
#include "DxLib.h"
#include "../Define.h"
#include <math.h>

//計算関連
class Calculation {
private:
	Calculation() {};
public:
	static float GetPartsAngle(float bangle, float pangle); //パーツの角度を返す
	static float GetPartsX(float bangle, float axis, float pdist, float pangle, bool reverse); //パーツのx座標を返す（基の角度、回転軸の座標、回転の半径、パーツの初期角度、向き）
	static float GetPartsY(float bangle, float ax, float ay, float px, float py, bool reverse); //パーツのy座標を返す（基の角度、回転軸の座標、回転の半径、向き）
	static float LockOn(float cx, float cy, float dx, float dy); //目標に向けて角度を設定(自分のx,y座標、目標のx,y座標)
	static float HomingSpin(float angle, float set_spin_speed, float x, float y, float set_x, float set_y); //目標に向けて回転（角度、回転速度、座標、目標の座標）
	static float HomingSpin(float angle, float set_spin_speed, float target_angle); //目標に向けて回転（角度、回転速度、目標の角度）
	static float Spin(float angle, float set_spin_speed, float spin_max, float spin_min); //回転させる（角度、回転速度、上限、下限）
};