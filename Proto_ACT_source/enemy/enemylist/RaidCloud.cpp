#pragma once
#include "DxLib.h"
#include "RaidCloud.h"

using namespace std;

//コンストラクタ
RaidCloud::RaidCloud(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	shared_ptr<AbstractEnemy> cbit;

	flying_flag = true;
	pattern = 2; //パターンは2から
	parts_num = 12;
	parts_distance = 142.0f;
	parts_angle = 0.0f;
	hit_map = false;

	SetHit(0.0f, 0.0f, 64.0f);

	//パーツを生成
	for (int i = 0; i < parts_num; i++) {
		float pangle = 2.0f * PI * ((float)i / parts_num); //角度
		float px = x + parts_distance * cosf(pangle);//配置する座標
		float py = y + parts_distance * sinf(pangle);
		cbit = manager->SetEnemy(34, px, py);
		parts.emplace_back(cbit);
	}

	AbsUpdate();
}

//デストラクタ
RaidCloud::~RaidCloud() {

}

//攻撃1（ばらまき）
void RaidCloud::Pattern1(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	
	//パーツを高速回転させる
	if (60 < time && time < 240) {
		float direction = (reverse) ? -1.0f : 1.0f; //向きに応じた計算用
		parts_angle += (0.025f * PI);
	}
	//一定時間ごとに弾を撃つ
	if (120 < time && time < 240 && time % 6 == 0) {
		shared_ptr<AbstractBullet> bul;
		for (int i = 0; i < parts_num; i++) {
			float pangle = parts_angle + 2.0f * PI * ((float)i / parts_num); //角度
			float px = parts[i]->GetX();//配置する座標
			float py = parts[i]->GetY();
			bul = bullet->SetBullet(5, px, py, 8.0f, pangle); //弾を発射
			bul->SetEndTime(30); //消えるまでの時間を設定
		}
		sound->PlaySoundEffect(7); //効果音を鳴らす
	}

	//一定時間経ったら
	if (300 <= time) {
		pattern = 3; //パターンを3に
		time = 0; //時間を初期化
	}
}

//攻撃2（突進）
void RaidCloud::Pattern2(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float left = (float)camera->GetScrollX() + 160.0f; //左端
	float right = (float)camera->GetScrollX() + (float)WINDOW_X - 160.0f; //右端
	float top = (float)camera->GetScrollY() + 416.0f; //上
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y - 96.0f; //底

	//速度を設定
	if (time == 60) {
		float center = (float)camera->GetScrollX() + ((float)WINDOW_X / 2.0f); //中心
		sx = (center < x) ? 2.0f : -2.0f; //位置に応じて速度を設定
		sy = 0.0f; //速度を設定
		return;
	}
	if (time < 90) return;
	if (time == 90) {
		sx = 0.0f; //速度を設定
		sy = 8.0f;
		return;
	}

	//パーツを高速回転させる
	parts_angle += (0.025 * PI);

	//底に近くなったら
	if (bottom < y && fabsf(sx) < 0.1f && 0.0f < sy) {
		float center = (float)camera->GetScrollX() + ((float)WINDOW_X / 2.0f); //中心
		y = bottom; //位置を調整
		sy = 0.0f; //速度を設定
		sx = (center < x) ? -10.0f : 10.0f; //位置に応じて速度を設定
	}
	//左に近くなったら
	else if (fabsf(x - left) < 8.0f && sx < 0.0f && fabsf(y - bottom) < 1.0f) {
		x = left; //位置を調整
		sx = 0.0f; //速度を設定
		sy = -8.0f;
	}
	//右に近くなったら
	else if (fabsf(x - right) < 8.0f && 0.0f < sx && fabsf(y - bottom) < 1.0f) {
		x = right; //位置を調整
		sx = 0.0f; //速度を設定
		sy = -8.0f;
	}
	//上に近くなったら
	else if (fabsf(y - top) < 8.0f && fabsf(sx) < 0.1f && sy < 0.0f) {
		y = top; //位置を調整
		sy = 0.0f; //速度を設定
		pattern = 3; //パターンを3に
		time = 0; //時間を初期化
	}
}

//攻撃3（上移動）
void RaidCloud::Pattern3(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float left = (float)camera->GetScrollX() + 160.0f; //左端
	float right = (float)camera->GetScrollX() + (float)WINDOW_X - 160.0f; //右端
	float top = (float)camera->GetScrollY() + 128.0f; //上
	float bottom = (float)camera->GetScrollY() + 416.0f; //下

	//速度を設定
	if (time == 60) {
		sx = 0.0f; //速度を設定
		sy = -8.0f;
		return;
	}
	if (time < 60) return;

	//パーツを高速回転させる
	parts_angle += (0.025f * PI);

	//上に近くなったら
	if (y < top && fabsf(sx) < 0.1f && sy < 0.0f) {
		float center = (float)camera->GetScrollX() + ((float)WINDOW_X / 2.0f); //中心
		y = top; //位置を調整
		sy = 0.0f; //速度を設定
		sx = (center < x) ? -10.0f : 10.0f; //位置に応じて速度を設定
	}
	//左に近くなったら
	else if (fabsf(x - left) < 8.0f && sx < 0.0f && fabsf(y - top) < 1.0f) {
		x = left; //位置を調整
		sx = 0.0f; //速度を設定
		sy = 8.0f;

		//弾を撃つ
		for (int i = 0; i < parts_num; i++) {
			float pangle = parts_angle + 2.0f * PI * ((float)i / parts_num); //角度
			float px = parts[i]->GetX();//配置する座標
			float py = parts[i]->GetY();
			bullet->SetBullet(6, px, py, 8.0f, pangle); //弾を発射
		}
		sound->PlaySoundEffect(7); //効果音を鳴らす
	}
	//右に近くなったら
	else if (fabsf(x - right) < 8.0f && 0.0f < sx && fabsf(y - top) < 1.0f) {
		x = right; //位置を調整
		sx = 0.0f; //速度を設定
		sy = 8.0f;

		//弾を撃つ
		for (int i = 0; i < parts_num; i++) {
			float pangle = parts_angle + 2.0f * PI * ((float)i / parts_num); //角度
			float px = parts[i]->GetX();//配置する座標
			float py = parts[i]->GetY();
			bullet->SetBullet(6, px, py, 8.0f, pangle); //弾を発射
		}
		sound->PlaySoundEffect(7); //効果音を鳴らす
	}
	//底に近くなったら
	else if (fabsf(bottom - y) < 8.0f && fabsf(sx) < 0.1f && 0.0f < sy) {
		y = bottom; //位置を調整
		sy = 0.0f; //速度を設定
		pattern = 3; //パターンを3に
		time = 0; //時間を初期化
	}
}

//必ず行う更新
void RaidCloud::AbsUpdate() {
	float direction = (reverse) ? -1.0f : 1.0f; //向きに応じた計算用

	//パーツの位置を設定
	for (int i = 0; i < parts_num; i++) {
		float pangle = parts_angle + 2.0f * PI * ((float)i / parts_num); //角度
		float px = x + parts_distance * cosf(pangle);//配置する座標
		float py = y + parts_distance * sinf(pangle);
		parts[i]->SetX(px);
		parts[i]->SetY(py);
	}
}

//やられた時の動作
void RaidCloud::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_time = 60; //消えるまでの時間を設定
	sy = 0.5f;
}

//更新
void RaidCloud::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//消えるまでの時間が設定されているなら
	if (end_time != -1) {
		//消える寸前なら
		if (end_time == 1) {
			end_flag = true; //消える
			effect->SetEffect(1, x, y, 2.0f); //爆発
		}
		//消える前なら
		else if (end_time % 12 == 0) {
			effect->SetEffect(2, x, y - 64.0f); //煙
		}
		return; //終了
	}

	//攻撃パターンによって行動を変更
	switch (pattern)
	{
	case 0:
		Pattern1(player, bullet, effect, sound, camera);
		break;
	case 1:
		Pattern2(player, bullet, effect, sound, camera);
		break;
	case 2:
		Pattern3(player, bullet, effect, sound, camera);
		break;
	default:
		//一定時間経ったらパターンを変更
		if (60 <= time) {
			pattern = GetRand(3);
			time = 0; //時間を初期化
		}
		break;
	}

}

//描画
void RaidCloud::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

	int hundle = image->GetCharaImage(image_num, 0);

	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}