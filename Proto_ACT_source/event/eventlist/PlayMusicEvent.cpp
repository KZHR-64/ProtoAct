#pragma once
#include "DxLib.h"
#include "PlayMusicEvent.h"

using namespace std;

//コンストラクタ
PlayMusicEvent::PlayMusicEvent(EventManager* man, int num, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {

	bgm_num = num;
}

//デストラクタ
PlayMusicEvent::~PlayMusicEvent() {

}

//更新
void PlayMusicEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {

	sound->LoadBgm(bgm_num);
	sound->PlayBgm(bgm_num);
	end_flag = true;
}

//描画
void PlayMusicEvent::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

}