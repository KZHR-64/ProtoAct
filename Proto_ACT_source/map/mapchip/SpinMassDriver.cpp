#pragma once
#include "DxLib.h"
#include "SpinMassDriver.h"

using namespace std;

//コンストラクタ
SpinMassDriver::SpinMassDriver(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	loaded = false;
	fire_time = 0;
	hit_flag = false;
}

//デストラクタ
SpinMassDriver::~SpinMassDriver() {

}

//必ず行う更新
void SpinMassDriver::AbsUpdate() {

}

//更新
void SpinMassDriver::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	//自機の座標を取得
	float px = player->GetX();
	float py = player->GetY();

	//自機が入っているなら
	if (loaded) {
		player->SetX(x); //自機の座標を設定
		player->SetY(y + (4.0f * size_y));
		//ジャンプボタンが押されたなら
		if (key->KeyCheckOnce(Attack)) {
			shared_ptr<AbstractEffect> eff;
			float x_speed = 12.0f * cosf(angle); //x方向の速度を設定
			float y_speed = 12.0f * sinf(angle); //y方向の速度を設定
			float eff_x = x + 48.0f * cosf(angle); //エフェクトの位置を設定
			float eff_y = y + (4.0f * size_y) + 48.0f * sinf(angle);
			player->SetXSpeed(x_speed); //自機の速度を設定
			player->SetYSpeed(y_speed);
			player->SetSpinSpeed(0.05f * PI); //回転速度を設定
			player->SetDrawFlag(true); //自機の表示を行う
			loaded = false; //自機を入れた状態をfalseに
			fire_time = 18; //しばらくは自機を入れない
			eff = effect->SetEffect(2, eff_x, eff_y, 0.7f); //エフェクトを発生
			eff->SetAngle(angle + (0.5f * PI)); //角度を設定
			sound->PlaySoundEffect(16); //効果音を鳴らす
		}
	}
	//入っていないなら
	else {
		//自機が近いなら
		if (fabsf(px - x) < 24.0f + (4.0f * size_x) && fabsf(py - y - (4.0f * size_y)) < 4.0f * size_y && fire_time == 0) {
			loaded = true; //自機が入った状態に
			player->SetXSpeed(0.0f); //自機の速度を0に
			player->SetYSpeed(0.0f);
			player->SetFlying(true); //自機を飛行状態に
			player->SetDrawFlag(false); //自機の表示を行わない
			player->SetMoveFlag(false); //自機を操作不可に
		}
		//撃った直後なら
		if (0 < fire_time) {
			fire_time--; //時間を減少
		}
	}

	//一定時間ごとに回転
	if(time % 30 == 0) {
		angle += 0.25f * PI;
	}
}

//描画
void SpinMassDriver::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetMapchipImage(image_num);
	//画像の大きさを取得
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);

	camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);

	//自機が入っているなら発射指示を表示
	if (loaded && time % 60 < 30) {
		int ehundle = image->GetEffectImage(15, 0);
		camera->Draw(x + 32.0f, y - 32.0f, false, 0.0f, ehundle, 1.0f, DX_BLENDMODE_NOBLEND);
	}
}