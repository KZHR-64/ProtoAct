#pragma once
#include "DxLib.h"
#include "CallSign.h"

using namespace std;

//コンストラクタ
CallSign::CallSign(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	hundle_num = 0;
}

//デストラクタ
CallSign::~CallSign() {

}

//更新
void CallSign::Update() {
	if (time == 0) {
		Sound::Get_Instance()->PlaySoundEffect(10); //効果音を鳴らす
	}

	y -= 2.0f;

	//一定時間を過ぎたら消す
	if (66 <= time) {
		end_flag = true;
	}
	else {
		//表示する画像を決定
		hundle_num = time / 6;
	}

}

//描画
void CallSign::Draw() {
	int hundle = Image::Get_Instance()->GetEffectImage(16, hundle_num);

	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}