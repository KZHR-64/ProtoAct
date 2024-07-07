#pragma once
#include "DxLib.h"
#include "MarkPoint.h"

using namespace std;

//コンストラクタ
MarkPoint::MarkPoint(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	for (int i = 0; i < particle_num; i++) {
		particle_time[i] = i * 12; //タイマーを初期化
	}
}

//デストラクタ
MarkPoint::~MarkPoint() {

}

//必ず行う更新
void MarkPoint::AbsUpdate() {

}

//更新
void MarkPoint::Update(shared_ptr<Sound> sound) {
	for (int i = 0; i < particle_num; i++) {
		particle_time[i]++; //タイマーを増加
		//一定時間を過ぎたら時間を戻す
		if (60 <= particle_time[i]) {
			particle_time[i] = 0;
		}
	}
}

//描画
void MarkPoint::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	for (int i = 0; i < particle_num; i++) {
		int hundle_num = particle_time[i] / 2; //表示する画像
		int hundle = image->GetEffectImage(image_num, hundle_num);
		float part_x = x + distance * particle_x[i]; //エフェクトのx座標を設定
		float part_y = y - (1.0f * particle_time[i]); //エフェクトのy座標を設定

		camera->Draw(part_x, part_y, false, angle, hundle, ex_rate, DX_BLENDMODE_NOBLEND);
	}
}