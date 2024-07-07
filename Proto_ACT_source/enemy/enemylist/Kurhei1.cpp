#pragma once
#include "DxLib.h"
#include "Kurhei1.h"

using namespace std;

//コンストラクタ
Kurhei1::Kurhei1(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	flying_flag = true;
	hundle_num = 0;
	SetHit(0.0f, 0.0f, 32.0f);
}

//デストラクタ
Kurhei1::~Kurhei1() {

}

//必ず行う更新
void Kurhei1::AbsUpdate() {
	//一定時間ごとに画像を変更
	if (time % 3 == 0) {
		hundle_num = (hundle_num + 1) % 2;
	}
}

//やられた時の動作
void Kurhei1::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_time = 30; //消えるまでの時間を設定
	sy = 0.5f;
}

//更新
void Kurhei1::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//消えるまでの時間が設定されているなら
	if (end_time != -1) {
		//消える寸前なら
		if (end_time == 1) {
			end_flag = true; //消える
			effect->SetEffect(1, x, y); //爆発
		}
		//消える前なら
		else if (end_time % 12 == 0) {
			effect->SetEffect(2, x, y - 24.0f, 0.5f); //煙
		}
		sy *= 1.1f; //落下速度を加速
		return; //終了
	}

	float px = player->GetX(); //自機の座標
	//自機のいる方向を向く
	reverse = px < x;
}

//描画
void Kurhei1::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, hundle_num);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}