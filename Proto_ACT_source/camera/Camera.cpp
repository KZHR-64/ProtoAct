#pragma once
#include "Camera.h"
#include "DxLib.h"

using namespace std;

Camera::Camera() {

	scroll_x = 0; //横方向のスクロールを初期化
	scroll_y = 0; //縦方向のスクロールを初期化
	scroll_x_max = 0; //スクロール上限を初期化
	scroll_y_max = 0; //スクロール上限を初期化
	scroll_x_min = 0; //スクロール下限を初期化
	scroll_y_min = 0; //スクロール下限を初期化
	back_x_max = 0; //スクロール上限を初期化
	back_y_max = 0; //スクロール上限を初期化
}

//デストラクタ
Camera::~Camera() {

}

//スクロールを反映させた描画
void Camera::Draw(float x, float y, bool reverse, float angle, int img, float ex_rate, int BlendMode, int Pal) {

	Display::Draw(x - (float)scroll_x, y - (float)scroll_y, reverse, angle, img, ex_rate, BlendMode, Pal);

}

//背景の描画
void Camera::BackDraw(float x, float y, int image, int BlendMode, int Pal) {
	//背景画像の大きさを取得
	int size_x;
	int size_y;
	GetGraphSize(image, &size_x, &size_y);

	// 実際に使うのは半分の大きさ
	size_x = size_x / 2;
	size_y = size_y / 2;

	SetDrawBlendMode(BlendMode, Pal); //描画モードを反映

	DrawRotaGraph((int)x + size_x, (int)y + size_y, 1.0f, 0.0f, image, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
}

//スクロールを反映させない描画
void Camera::FixedDraw(float x, float y, bool lr, float angle, int image, float ex_rate, int BlendMode, int Pal) {
	SetDrawBlendMode(BlendMode, Pal); //描画モードを反映

	DrawRotaGraph((int)x, (int)y, ex_rate, angle, image, true, !lr);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
}

//当たり判定の描画
void Camera::HitDraw(float x, float y, float hit_size) {
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192); //描画モードを反映

	//DrawCircle((int)x - scroll_x, (int)y - scroll_y, (int)hit_size, GetColor(255, 96, 96));

	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
}

//横方向にどれだけスクロールしているか返す
int Camera::GetScrollX() {
	return scroll_x;
}

//縦方向にどれだけスクロールしているか返す
int Camera::GetScrollY() {
	return scroll_y;
}

//横方向にどれだけスクロールさせるか設定する
void Camera::SetScrollX(float x) {
	scroll_x = (int)x - (WINDOW_X / 3);
	//最低値を下回った場合
	if (scroll_x < scroll_x_min) {
		scroll_x = scroll_x_min; //スクロールは最低値に
	}
	//はみ出した場合
	if (scroll_x_max < scroll_x) {
		scroll_x = scroll_x_max;
	}
}

//縦方向にどれだけスクロールさせるか設定する
void Camera::SetScrollY(float y) {
	scroll_y = (int)y - (WINDOW_Y / 2);
	//マイナスになった場合
	if (scroll_y < scroll_y_min) {
		scroll_y = scroll_y_min; //スクロールは最低値に
	}

	//はみ出した場合
	if (scroll_y_max < scroll_y) {
		scroll_y = scroll_y_max;
	}
}

//横方向のスクロール下限を返す
int Camera::GetScrollXMin() {
	return scroll_x_min;
}

//縦方向のスクロール下限を返す
int Camera::GetScrollYMin() {
	return scroll_y_min;
}

//横方向のスクロール上限を返す
int Camera::GetScrollXMax() {
	return scroll_x_max + WINDOW_X;
}

//縦方向のスクロール上限を返す
int Camera::GetScrollYMax() {
	return scroll_y_max + WINDOW_Y;
}

//横方向のスクロール下限を設定する
void Camera::SetScrollXMin(int x) {
	scroll_x_min = x;
}

//縦方向のスクロール下限を設定する
void Camera::SetScrollYMin(int y) {
	scroll_y_min = y;
}

//横方向のスクロール上限を設定する
void Camera::SetScrollXMax(int x) {
	back_x_max = scroll_x_max;
	scroll_x_max = x - WINDOW_X;
}

//縦方向のスクロール上限を設定する
void Camera::SetScrollYMax(int y) {
	back_y_max = scroll_y_max;
	scroll_y_max = y - WINDOW_Y;
}

//横方向のスクロール上限を戻す
void Camera::ReSetScrollXMax() {
	scroll_x_max = back_x_max;
}

//縦方向のスクロール上限を戻す
void Camera::ReSetScrollYMax() {
	scroll_y_max = back_y_max;
}

//横方向にどれだけスクロールしたか返す
int Camera::GetScrollDifX() {
	return scroll_dif_x;
}

//縦方向にどれだけスクロールしたか返す
int Camera::GetScrollDifY() {
	return scroll_dif_y;
}