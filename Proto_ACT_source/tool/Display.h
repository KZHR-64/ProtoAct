#pragma once
#include "DxLib.h"
#include "../Define.h"

//描画関連
class Display {
private:

public:
	Display(); //コンストラクタ
	static void Draw(float x, float y, bool reverse, float angle, int image, float ex_rate = 1.0f, int BlendMode = DX_BLENDMODE_NOBLEND, int Pal = 0); //描画(x,y座標、左右の向き、角度、画像、ブレンドモード、パラメータ)
	static void BackDraw(float x, float y, int image, int BlendMode = DX_BLENDMODE_NOBLEND, int Pal = 0); //背景の描画(x,y座標、画像、ブレンドモード、パラメータ)
	static void HitDraw(float x, float y, float hit_size); //当たり判定の描画
};