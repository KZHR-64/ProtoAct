#pragma once
#include "DxLib.h"
#include "RocketHand.h"

using namespace std;

//コンストラクタ
RocketHand::RocketHand(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	catch_item = 0;
	SetHit(0.0f, 0.0f, 24.0f);
}

//デストラクタ
RocketHand::~RocketHand() {
	catch_item.reset();
}

//必ず行う更新
void RocketHand::AbsUpdate() {

}

//消える時の動作
void RocketHand::Erase(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {

}

//更新
void RocketHand::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float px = player->GetX();
	float py = player->GetY();

	//アイテムをつかんでいるなら
	if (catch_item != 0) {
		catch_item->SetX(x); //アイテムの位置を設定
		catch_item->SetY(y);
	}
	//つかんでいないなら
	else {
		//近くにアイテムがあるなら
		for (auto& h : hit) {
			shared_ptr<AbstractItem> it = item->HitCheckChara(h.x, h.y, h.size);
			if (it != NULL) {
				catch_item = it; //アイテムをつかむ
				catch_item->SetXSpeed(0.0f); //速度を0に
				catch_item->SetYSpeed(0.0f);
				catch_item->SetHitMap(false); //マップとの当たり判定をfalseに
				break;
			}
		}
	}


	//一定時間を過ぎたら自機へ戻ってくる
	if (18 < time) {
		float back = Calculation::LockOn(x, y, px, py);
		sx = base_speed * cosf(back);
		sy = base_speed * sinf(back);

		//自機に近づいたら消える
		if (fabsf(px - x) < 16.0f && fabsf(py - y) < 16.0f) {
			end_flag = true;
		}
	}

}

//描画
void RocketHand::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetBulletImage(image_num, 0);
	float draw_angle = angle;
	if (0.5f * PI < angle || angle < -0.5f * PI) {
		reverse = true;
		draw_angle += PI;
	}
	else {
		reverse = false;
	}
	camera->Draw(x, y, reverse, draw_angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}