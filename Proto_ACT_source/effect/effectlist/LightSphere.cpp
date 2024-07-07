#pragma once
#include "DxLib.h"
#include "LightSphere.h"

using namespace std;

//コンストラクタ
LightSphere::LightSphere(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	hundle_num = 0;
}

//デストラクタ
LightSphere::~LightSphere() {

}

//必ず行う更新
void LightSphere::AbsUpdate() {

}

//更新
void LightSphere::Update(shared_ptr<Sound> sound) {
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
void LightSphere::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetEffectImage(image_num, hundle_num);

	camera->Draw(x, y, false, angle, hundle, ex_rate, DX_BLENDMODE_NOBLEND);
}