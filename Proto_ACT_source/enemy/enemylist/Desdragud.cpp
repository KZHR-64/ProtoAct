#pragma once
#include "DxLib.h"
#include "Desdragud.h"

using namespace std;

//コンストラクタ
Desdragud::Desdragud(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	shared_ptr<AbstractEnemy> arm;

	flying_flag = true;
	pattern = 0; //パターンは0から
	move_flag = true; //まずは移動
	hit_map = false;
	reverse = true;

	SetHit(0.0f, 0.0f, 64.0f);
	SetHit(112.0f, -32.0f, 32.0f);

	head_angle = atan2f(-34.0f, 118.0f);
	head_distance = sqrtf((34.0f * 34.0f) + (118.0f * 118.0f));
	arm1_angle = atan2f(-48.0f, 24.0f);
	arm1_distance = sqrtf((48.0f * 48.0f) + (24.0f * 24.0f));
	arm1_spin_angle = atan2f(0.0f, 72.0f);
	arm1_spin_distance = sqrtf(72.0f * 72.0f);
	arm2_angle = atan2f(-48.0f, 24.0f);
	arm2_distance = sqrtf((48.0f * 48.0f) + (24.0f * 24.0f));
	arm2_spin_angle = atan2f(0.0f, 72.0f);
	arm2_spin_distance = sqrtf(72.0f * 72.0f);
	leg1_angle = atan2f(48.0f, 16.0f);
	leg1_distance = sqrtf((48.0f * 48.0f) + (16.0f * 16.0f));
	leg2_angle = atan2f(48.0f, 16.0f);
	leg2_distance = sqrtf((48.0f * 48.0f) + (16.0f * 16.0f));
	
	//腕
	arm = ene->SetEnemy(36, x, y, this);
	parts.emplace_back(arm);
	arm = ene->SetEnemy(36, x, y, this);
	parts.emplace_back(arm);

	AbsUpdate();
}

//デストラクタ
Desdragud::~Desdragud() {

}

//攻撃1（バリアとミサイル）
void Desdragud::Pattern1(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	
	parts[0]->SetAngle(0.25 * PI);
	parts[1]->SetAngle(0.25 * PI);

	//一定時間ごとに弾を撃つ
	if (90 <= time % 120 && time % 6 == 0) {
		manager->SetEnemy(11, x, y - 64.0f);
		sound->PlaySoundEffect(9); //効果音を鳴らす
	}

	//一定時間経ったら
	if (240 < time) {
		pattern = 3; //パターンを3に
		time = 0; //時間を初期化
	}
}

//攻撃2（ミサイルと自機狙い）
void Desdragud::Pattern2(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	float dy = (float)camera->GetScrollY() + 224.0f; //目的地
	float px = player->GetX(); //自機の座標
	float py = player->GetY(); //自機の座標
	float direction = (reverse) ? -1.0f : 1.0f; //向きに応じた計算用

	float aangle; //腕の角度
	float parts_dx; //パーツの回転の目標となるx座標

	//定位置に移動するなら
	if (move_flag) {
		//定位置に移動
		float sangle = atan2f(dy - y, 0); //定位置への角度を取得
		sx = 8.0f * cosf(sangle);
		sy = 8.0f * sinf(sangle);
		//近いなら
		if (fabsf(dy - y) < 16.0f) {
			sx = 0.0f;
			sy = 0.0f;
			move_flag = false; //移動を終了
		}
		return;
	}

	parts[0]->SetAngle(0.25 * PI);

	//自機に向け腕を回転
	if (60 < time % 240 && time % 240 < 120) {
		aangle = parts[1]->GetAngle();
		parts_dx = (reverse) ? px + ((parts[1]->GetX() - px) * 2.0f) : px;
		aangle = Calculation::HomingSpin(aangle, (3.0f / 180.0f) * PI, parts[1]->GetX(), parts[1]->GetY(), parts_dx, py);
		parts[1]->SetAngle(aangle);
	}
	if (150 < time % 240 && time % 240 < 210 && time % 3 == 0) {
		aangle = parts[1]->GetAngle();
		float sangle = (reverse) ? (PI) - aangle : aangle; //向きに応じて弾の角度を設定
		//弾の位置を計算
		float shoot_x = parts[1]->GetX() + ((80.0f * cosf(aangle)) * direction);
		float shoot_y = parts[1]->GetY() + (80.0f * sinf(aangle));

		bullet->SetBullet(5, shoot_x, shoot_y, 16.0f, sangle); //弾を発射
		sound->PlaySoundEffect(7); //効果音を鳴らす
	}

	//一定時間ごとに弾を撃つ
	if (time % 240 == 0) {
		shared_ptr<AbstractEnemy> mis;
		mis = manager->SetEnemy(9, x, y - 64.0f);
		mis->SetAngle(1.5f * PI);
		sound->PlaySoundEffect(9); //効果音を鳴らす
	}

	//一定時間経ったら
	if (720 <= time) {
		pattern = 3; //パターンを3に
		time = 0; //時間を初期化
	}
}

//攻撃3（突進）
void Desdragud::Pattern3(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	float left = (float)camera->GetScrollX() + 160.0f; //左端
	float left2 = (float)camera->GetScrollX() - 64.0f;
	float right = (float)camera->GetScrollX() + (float)WINDOW_X - 160.0f; //右端
	float right2 = (float)camera->GetScrollX() + (float)WINDOW_X + 64.0f;
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y - 192.0f; //下
	float direction = (reverse) ? -1.0f : 1.0f; //向きに応じた計算用

	//開始位置へ移動
	if (60 < time && time < 180) {
		//定位置に移動
		float dx = (reverse) ? right : left; //目的地
		float sangle = atan2f(bottom - y, dx - x); //定位置への角度を取得
		sx = 8.0f * cosf(sangle); //速度を設定
		sy = 8.0f * sinf(sangle);
		//parts[0]->Spin((3.0f / 180.0f) * PI, PI, -PI); //腕の角度を調整
		float aangle = Calculation::Spin(parts[0]->GetAngle(), (3.0f / 180.0f) * PI, PI, -PI); //腕の角度を調整
		parts[0]->SetAngle(aangle);
		aangle = Calculation::Spin(parts[1]->GetAngle(), (3.0f / 180.0f) * PI, PI, -PI); //腕の角度を調整
		parts[1]->SetAngle(aangle);
		//近いなら
		if (fabsf(dx - x) < 16.0f && fabsf(bottom - y) < 16.0f) {
			sx = 0.0f;
			sy = 0.0f;
		}
	}
	//速度を設定
	else if (time == 300) {
		sx = -8.0f * direction;
	}
	//加速
	else if(300 < time && time < 600) {
		float max_speed = (reverse ? -28.0f : 28.0f); //向きによって速度上限を設定

		float accel = (reverse ? -0.05f : 0.05f); //向きによって加速度を設定

		if(fabsf(sx) < 2.0f) sx = 2.0f * direction;

		sx += (fabsf(sx) * accel); //加（減）速
	}
	//向きを反転
	else if (time == 600) {
		reverse = !reverse;
	}
	//画面外から戻る
	else if (600 < time) {
		//定位置に移動
		float dx = (reverse) ? right : left; //目的地
		float sangle = atan2f(bottom - y, dx - x); //定位置への角度を取得
		sx = 8.0f * cosf(sangle);
		sy = 8.0f * sinf(sangle);
		//近いなら
		if (fabsf(dx - x) < 16.0f && fabsf(bottom - y) < 16.0f) {
			sx = 0.0f;
			sy = 0.0f;
			pattern = 3; //パターンを3に
			time = 0; //時間を初期化
		}
	}

	//画面外に出たら
	if ((x < left2 && sx < 0.0f && reverse) || (right2 < x && 0.0f < sx && !reverse)) {
		sx = 0.0f; //停止
		parts[0]->SetAngle(0.25 * PI); //腕の角度を調整
		parts[1]->SetAngle(0.25 * PI);
	}
}

//必ず行う更新
void Desdragud::AbsUpdate() {
	parts[0]->SetReverse(reverse);
	parts[1]->SetReverse(reverse);

	float direction = (reverse) ? -1.0f : 1.0f; //向きに応じた計算用
	head_x = x + ((head_distance * cosf(angle + head_angle) * direction));
	head_y = y + (head_distance * sinf(angle + head_angle));
	arm1_x = x + (((arm1_distance * cosf(angle + arm1_angle)) + (arm1_spin_distance * cosf(arm1_spin_angle + parts[0]->GetAngle()))) * direction);
	arm1_y = y + (arm1_distance * sinf(angle + arm1_angle)) + (arm1_spin_distance * sinf(arm1_spin_angle + parts[0]->GetAngle()));
	arm2_x = x + (((arm2_distance * cosf(angle + arm2_angle)) + (arm2_spin_distance * cosf(arm2_spin_angle + parts[1]->GetAngle()))) * direction);
	arm2_y = y + (arm2_distance * sinf(angle + arm2_angle)) + (arm2_spin_distance * sinf(arm2_spin_angle + parts[1]->GetAngle()));
	leg1_x = x + ((leg1_distance * cosf(angle + leg1_angle) * direction));
	leg1_y = y + (leg1_distance * sinf(angle + leg1_angle));
	leg2_x = x + ((leg2_distance * cosf(angle + leg2_angle) * direction));
	leg2_y = y + (leg2_distance * sinf(angle + leg2_angle));

	parts[0]->SetX(arm1_x);
	parts[0]->SetY(arm1_y);
	parts[1]->SetX(arm2_x);
	parts[1]->SetY(arm2_y);
}

//やられた時の動作
void Desdragud::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_time = 60; //消えるまでの時間を設定
	sy = 0.5f;
}

//更新
void Desdragud::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
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
			move_flag = true;
			time = 0; //時間を初期化
		}
		break;
	}
}

//描画
void Desdragud::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

	int hundle = image->GetCharaImage(image_num, 0);
	int head_hundle = image->GetCharaImage(37, 0);
	int leg_hundle = image->GetCharaImage(39, 0);

	camera->Draw(leg1_x, leg1_y, reverse, angle, leg_hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	parts[0]->Draw(image, camera);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(head_x, head_y, reverse, angle, head_hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	camera->Draw(leg2_x, leg2_y, reverse, angle, leg_hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	parts[1]->Draw(image, camera);
}