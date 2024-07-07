#pragma once
#include "DxLib.h"
#include "CatchBeam.h"

using namespace std;

//コンストラクタ
CatchBeam::CatchBeam(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	beam_num = 0;
}

//デストラクタ
CatchBeam::~CatchBeam() {

}

//更新
void CatchBeam::Update() {
	//表示する細いビームの数を設定
	beam_num = (int)(x - base_x) / 64;
	if (beam_num == 0) beam_num = 1;
}

//描画
void CatchBeam::Draw() {
	int hundle = Image::Get_Instance()->GetEffectImage(13, 0);
	int hundle2 = Image::Get_Instance()->GetEffectImage(14, 0);

	for (int i = 0; i < beam_num; i++) {
		Display::Get_Instance()->Draw(base_x + (i * 64.f), y, LEFT, 0.f, hundle2, DX_BLENDMODE_ALPHA, 192);
	}
	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_ALPHA, 192);
}