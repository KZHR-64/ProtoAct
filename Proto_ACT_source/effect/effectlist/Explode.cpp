#pragma once
#include "DxLib.h"
#include "Explode.h"

using namespace std;

//コンストラクタ
Explode::Explode(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	hundle_num = 0;
}

//デストラクタ
Explode::~Explode() {

}

//必ず行う更新
void Explode::AbsUpdate() {

}

//更新
void Explode::Update(shared_ptr<Sound> sound) {
	if (time == 0) {
		sound->PlaySoundEffect(16); //効果音を鳴らす
	}

	//一定時間を過ぎたら消す
	if (64 <= time) {
		end_flag = true;
	}
	else {
		//表示する画像を決定
		hundle_num = time / 8;
	}

}

//描画
void Explode::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetEffectImage(image_num, hundle_num);

	camera->Draw(x, y, false, angle, hundle, ex_rate, DX_BLENDMODE_NOBLEND);
}