#pragma once
#include "Display.h"
#include "DxLib.h"

Display::Display() {

}

//描画
void Display::Draw(float x, float y, bool reverse, float angle, int image, float ex_rate, int BlendMode, int Pal) {

	SetDrawBlendMode(BlendMode, Pal); //描画モードを反映

	DrawRotaGraph((int)x, (int)y, ex_rate, angle, image, true, reverse);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
}

//背景の描画
void Display::BackDraw(float x, float y, int image, int BlendMode, int Pal) {
	//背景画像の大きさを取得
	int size_x;
	int size_y;
	GetGraphSize(image, &size_x, &size_y);

	// 実際に使うのは半分の大きさ
	size_x = size_x / 2;
	size_y = size_y / 2;

	SetDrawBlendMode(BlendMode, Pal); //描画モードを反映

	DrawRotaGraph((int)x + size_x, (int)y + size_y, 1.0f, 0.0f,image, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
}

//当たり判定の描画
void Display::HitDraw(float x, float y, float hit_size) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192); //描画モードを反映

	DrawCircle((int)x, (int)y, (int)hit_size, GetColor(255, 96, 96));

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
}