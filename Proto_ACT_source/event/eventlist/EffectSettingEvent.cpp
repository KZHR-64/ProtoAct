#pragma once
#include "DxLib.h"
#include "EffectSettingEvent.h"

using namespace std;

//コンストラクタ
EffectSettingEvent::EffectSettingEvent(EventManager* man, int num, float x, float y, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	effect_num = num;
	ex = x + man->GetX();
	ey = y + man->GetX();

}

//デストラクタ
EffectSettingEvent::~EffectSettingEvent() {

}

//更新
void EffectSettingEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	effect->SetEffect(effect_num, ex, ey);

	end_flag = true;
}

//描画
void EffectSettingEvent::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

}