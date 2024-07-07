#pragma once
#include "DxLib.h"
#include "BlackOut.h"

using namespace std;

//コンストラクタ
BlackOut::BlackOut(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	pal = 0;
}

//デストラクタ
BlackOut::~BlackOut() {

}

//必ず行う更新
void BlackOut::AbsUpdate() {

}

//更新
void BlackOut::Update(shared_ptr<Sound> sound) {

}

//描画
void BlackOut::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal); //描画モードを反映

	DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
}