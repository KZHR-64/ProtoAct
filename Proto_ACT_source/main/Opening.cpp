#pragma once
#include "DxLib.h"
#include "Opening.h"

using namespace std;

Opening::Opening(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {
	logo = image->GetEffectImage(6, 0);

	time = 0;
	pal = 0;
}

Opening::~Opening() {

}

//事前のロード
void Opening::Load() {
	if (loaded) return; //ロード済みなら終了

	loaded = true; //ロードしたフラグをtrueに
}

//更新
void Opening::Update(){
	//切替フラグがtrueの場合
	if (start_flag) {
		time = 0; //タイマーを初期化
		start_flag = false; //帰還フラグをfalseに
	}
	
	if (time == 18) {
		sound->PlaySoundEffect(4); //効果音を鳴らす

	}

	if (pal < 255) {
		pal += 5;
	}

	if (180 <= time) {
		start_flag = true; //帰還フラグを立て
		modemanager->ChangeMode(Next_Menu, true); //モードをメニューに変更
	}
	
	time++;
}

//描画
void Opening::Draw(){
	DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(255, 255, 255), true);

	////Display::Draw(520.f, 260.f, false, 0.f, logo, 1.0f, DX_BLENDMODE_ALPHA, pal);
}