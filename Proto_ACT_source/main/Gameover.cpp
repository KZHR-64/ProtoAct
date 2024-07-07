#pragma once
#include "DxLib.h"
#include "Gameover.h"

using namespace std;

Gameover::Gameover(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {


	//画像を設定
	for (int i = 0; i < 2; i++)
	{
		select_hundle[i] = image->GetEffectImage(11, i);
	}

	cursor_pos = 0; //cursorの位置を初期化
}

//デストラクタ
Gameover::~Gameover() {
	
}

//初期化
void Gameover::Reset() {

}

//事前のロード
void Gameover::Load() {
	sound->LoadBgm(3); //曲をロード
	image->LoadBackImage(4); //背景をロード

	loaded = true; //ロードしたフラグをtrueに
}

//更新
void Gameover::Update(){
	//切替フラグがtrueの場合
	if (start_flag) {
		sound->PlayBgm(3); //曲を再生
		start_flag = false; //切替フラグをfalseに
	}

	if (key->KeyCheckOnce(Down) || key->KeyCheckOnce(Up)){ //下キーか上キーが押されていたら
		sound->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos = (cursor_pos + 1) % 2; //カーソルを下に移動
	}
	if (key->KeyCheckOnce(Jump)){ //決定キーが押されていたら
		sound->PlaySoundEffect(1); //効果音を鳴らす
		//カーソルの位置によって遷移先を変更
		switch (cursor_pos)
		{
		case 0:
			modemanager->ChangeMode(Next_Game, true); //モードをゲーム画面に変更
			break;
		case 1:
			modemanager->ChangeMode(Next_Back); //モードをステージセレクトに変更
			break;
		default:
			break;
		}
	}
}

//描画
void Gameover::Draw(){
	int back = image->GetBackImage(4); //背景を取得
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y / 2, false, 0.0f, back); //背景を描画

	int blend_mode; //表示方法
	int blend; //文字の明るさ

	//選択によって文字の明るさを変更
	for (int i = 0; i < 2; i++)
	{
		blend_mode = ((cursor_pos == i) ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_SUB);
		blend = ((cursor_pos == i) ? 1 : 64);
		Display::Draw(960.0f, 352.0f + (96.0f * i), false, 0.0f, select_hundle[i], 1.0f, blend_mode, blend); //選択肢を描画
	}
}