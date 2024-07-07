#pragma once
#include "DxLib.h"
#include "DekaKurhei.h"

using namespace std;

//コンストラクタ
DekaKurhei::DekaKurhei(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	flying_flag = true;
	hundle_num = 0;
	pattern = 0; //パターンは0から
	move_flag = true; //まずは移動
	hit_map = false;
	reverse = true;

	SetHit(-48.0f, 0.0f, 64.0f);
	SetHit(48.0f, 0.0f, 64.0f);

	parts1_angle = atan2f(-40.0f, 112.0f);
	parts1_distance = sqrtf((40.0f * 40.0f) + (112.0f * 112.0f));
	parts2_angle = atan2f(-40.0f, 24.0f);
	parts2_distance = sqrtf((40.0f * 40.0f) + (24.0f * 24.0f));
	parts3_angle = atan2f(-40.0f, -24.0f);
	parts3_distance = sqrtf((40.0f * 40.0f) + (24.0f * 24.0f));
	parts4_angle = atan2f(-40.0f, -112.0f);
	parts4_distance = sqrtf((40.0f * 40.0f) + (112.0f * 112.0f));

	AbsUpdate();
}

//デストラクタ
DekaKurhei::~DekaKurhei() {

}

//攻撃1（低空で機関砲）
void DekaKurhei::Pattern1(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float dx = (float)camera->GetScrollX() + 1080.0f; //目的地
	float dy = (float)camera->GetScrollY() + 480.0f; //目的地

	//定位置に移動するなら
	if (move_flag) {
		//定位置に移動
		float sangle = atan2f(dy - y, dx - x); //定位置への角度を取得
		sx = 8.0f * cosf(sangle);
		sy = 8.0f * sinf(sangle);
		//近いなら
		if (fabsf(dx - x) < 16.0f && fabsf(dy - y) < 16.0f) {
			sx = 0.0f;
			sy = 0.0f;
			move_flag = false; //移動を終了
		}
		return;
	}

	//一定時間ごとに弾を撃つ
	if (90 <= time % 120 && time % 6 == 0) {
		float shoot_x = (reverse ? -8.0f : 8.0f); //銃口
		float shoot_y = 40.0f;
		float shoot_angle = (reverse ? PI : 0.0f); //向きによって撃つ角度を決定
		bullet->SetBullet(5, x + shoot_x, y + shoot_y, 8.0f, shoot_angle); //弾を発射
		sound->PlaySoundEffect(7); //効果音を鳴らす
	}
	
	//HPが2/3以下になったら
	if (hp <= max_hp * 2 / 3) {
		effect->SetEffect(1, x, y, 1.5f); //爆発
		pattern = 1; //パターンを1に
		move_flag = true; //移動を開始
	}
}

//攻撃2（高空で機関砲）
void DekaKurhei::Pattern2(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float dx = (float)camera->GetScrollX() + 1080.0f; //目的地
	float dy = (float)camera->GetScrollY() + 128.0f; //目的地

	//定位置に移動するなら
	if (move_flag) {
		//定位置に移動
		float sangle = atan2f(dy - y, dx - x); //定位置への角度を取得
		sx = 8.0f * cosf(sangle);
		sy = 8.0f * sinf(sangle);
		//近いなら
		if (fabsf(dx - x) < 16.0f && fabsf(dy - y) < 16.0f) {
			sx = 0.0f;
			sy = 0.0f;
			move_flag = false; //移動を終了
		}
		return;
	}

	//一定時間ごとに弾を撃つ
	if (180 <= time % 240 && time % 15 == 0) {
		float shoot_x = (reverse ? -8.0f : 8.0f); //銃口
		float shoot_y = 40.0f;
		float shoot_angle = (reverse ? PI : 0.0f); //向きによって撃つ角度を決定
		bullet->SetBullet(6, x + shoot_x, y + shoot_y, 10.0f, shoot_angle); //弾を発射
		sound->PlaySoundEffect(7); //効果音を鳴らす
	}

	//HPが1/3以下になったら
	if (hp <= max_hp / 3) {
		effect->SetEffect(1, x, y, 1.5f); //爆発
		pattern = 2; //パターンを2に
		move_flag = true; //移動を開始
	}
}

//攻撃3（爆撃）
void DekaKurhei::Pattern3(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	//定位置に移動するなら
	if (move_flag) {
		//定位置に移動
		float dx = (reverse ? (float)camera->GetScrollX() + 128.0f : (float)camera->GetScrollX() + 1152.0f); //目的地
		float dy = (float)camera->GetScrollY() + 128.0f; //目的地

		float sangle = atan2f(dy - y, dx - x); //定位置への角度を取得
		sx = 4.0f * cosf(sangle);
		sy = 4.0f * sinf(sangle);
		//近いなら
		if (fabsf(dx - x) < 16.0f && fabsf(dy - y) < 16.0f) {
			sx = 0.0f;
			sy = 0.0f;
			reverse = !reverse;
			move_flag = false; //移動を終了
		}
	}

	//一定時間毎に往復
	if (time % 420 == 0) {
		move_flag = true;
	}

	//一定時間ごとに爆撃
	if (time % 42 == 0 && move_flag) {
		manager->SetEnemy(10, x, y + 64.0f);
		sound->PlaySoundEffect(9); //効果音を鳴らす
	}
}

//必ず行う更新
void DekaKurhei::AbsUpdate() {
	float direction = (reverse) ? -1.0f : 1.0f; //向きに応じた計算用
	parts1_x = x + ((parts1_distance * cosf(angle + parts1_angle) * direction));
	parts1_y = y + (parts1_distance * sinf(angle + parts1_angle));
	parts2_x = x + ((parts2_distance * cosf(angle + parts2_angle) * direction));
	parts2_y = y + (parts2_distance * sinf(angle + parts2_angle));
	parts3_x = x + ((parts3_distance * cosf(angle + parts3_angle) * direction));
	parts3_y = y + (parts3_distance * sinf(angle + parts3_angle));
	parts4_x = x + ((parts4_distance * cosf(angle + parts4_angle) * direction));
	parts4_y = y + (parts4_distance * sinf(angle + parts4_angle));

	JointUpdate(arm, x, y, angle); //関節を更新

	//一定時間ごとに画像を変更
	if (time % 3 == 0) {
		hundle_num = (hundle_num + 1) % 2;
	}
}

//やられた時の動作
void DekaKurhei::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_time = 60; //消えるまでの時間を設定
	sy = 0.5f;
}

//更新
void DekaKurhei::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
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
		break;
	}
}

//描画
void DekaKurhei::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle_num2 = (hundle_num + 1) % 2;

	int hundle = image->GetCharaImage(image_num, 0);
	int parts_hundle = image->GetCharaImage(33, hundle_num);
	int parts_hundle2 = image->GetCharaImage(33, hundle_num2);

	camera->Draw(parts1_x, parts1_y, reverse, angle, parts_hundle, ex_rate, DX_BLENDMODE_NOBLEND);
	camera->Draw(parts2_x, parts2_y, reverse, angle, parts_hundle2, ex_rate, DX_BLENDMODE_NOBLEND);
	camera->Draw(x, y, reverse, angle, hundle, ex_rate, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(parts3_x, parts3_y, reverse, angle, parts_hundle, ex_rate, DX_BLENDMODE_NOBLEND);
	camera->Draw(parts4_x, parts4_y, reverse, angle, parts_hundle2, ex_rate, DX_BLENDMODE_NOBLEND);
}