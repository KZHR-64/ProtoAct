#pragma once
#include "DxLib.h"
#include "Smoke.h"

using namespace std;

//コンストラクタ
Smoke::Smoke(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	hundle_num = 0;
}

//デストラクタ
Smoke::~Smoke() {

}

//必ず行う更新
void Smoke::AbsUpdate() {

}

//更新
void Smoke::Update(shared_ptr<Sound> sound) {
	if (time == 0) {
		sound->PlaySoundEffect(12); //効果音を鳴らす
	}

	//一定時間を過ぎたら消す
	if (30 <= time) {
		end_flag = true;
	}
	else {
		//表示する画像を決定
		hundle_num = time / 3;
	}

}

//描画
void Smoke::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetEffectImage(image_num, hundle_num);

	camera->Draw(x, y, false, angle, hundle, ex_rate, DX_BLENDMODE_NOBLEND);
}