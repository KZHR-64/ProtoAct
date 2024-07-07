#pragma once
#include "DxLib.h"
#include "Menu.h"
#include <math.h>

using namespace std;

Menu::Menu(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {

	Reset(); //初期化
	
	cursor_pos = 0; //cursorの位置を初期化
}

//デストラクタ
Menu::~Menu() {
	
}

//初期化
void Menu::Reset() {
	count = 0; //カウンターを初期化
}

//事前のロード
void Menu::Load() {
	if (loaded) return; //ロード済みなら終了

	sound->LoadBgm(0); //曲をロード
	image->LoadBackImage(0); //背景をロード
	for (int i = 0; i < 4; i++)
	{
		choice[i].image = image->GetEffectImage(0, i); //画像を設定
		choice[i].ex_rate = 1.0f; //倍率を初期化
	}
	logo = image->GetEffectImage(1, 0); //画像を設定

	loaded = true; //ロードしたフラグをtrueに
}

//更新
void Menu::Update(){
	//切替フラグがtrueの場合
	if (start_flag) {
		Reset(); //初期化
		sound->PlayBgm(0); //曲を再生
		start_flag = false; //切替フラグをfalseに
	}
	if (key->KeyCheckOnce(Up)){ //上キーが押されていたら
		sound->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos += 3; //カーソルを上に移動
		count = 0; //カウンターを初期化
	}

	if (key->KeyCheckOnce(Down)){ //下キーが押されていたら
		sound->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos++; //カーソルを下に移動
		count = 0; //カウンターを初期化
	}

	cursor_pos %= 4; //カーソルを合わせる

	//選択肢の状態を更新
	for (int i = 0; i < 4; i++)
	{
		if (i == cursor_pos) {
			choice[i].ex_rate = 1.1f + (0.1f * sinf(PI * 2.0f / 90.0f * count)); //選択されている場合は拡大、縮小を繰り返す
		}
		else {
			choice[i].ex_rate = 1.0f; //選択されていなければ等倍
		}
	}

	if (key->KeyCheckOnce(Jump)){ //決定キーが押されていたら
		sound->PlaySoundEffect(1); //効果音を鳴らす
		start_flag = true; //切替フラグを立てる
		//カーソルの位置によって遷移先を変更
		switch (cursor_pos)
		{
		case 0:
			modemanager->ChangeMode(Next_StageSelect); //モードをステージセレクトに変更
			break;
		case 1:
			modemanager->ChangeMode(Next_Option); //モードをオプションに変更
			break;
		case 2:
			modemanager->ChangeMode(Next_Config); //モードをキーコンフィグに変更
			break;
		case 3:
			PostMessageA(GetMainWindowHandle(), WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
	}

	/*if (key->KeyCheckOnce(Attack)){ //戻るボタンが押されていたら
		sound->PlaySoundEffect(2); //効果音を鳴らす
		modemanager->ChangeMode(Next_Back); //オープニングに戻る
	}*/

	count = (count + 1) % 90;//カウンターを増加
}

//描画
void Menu::Draw(){
	
	int image_num = image->GetEffectImage(7, 0); //画像を取得

	int back = image->GetBackImage(0); //背景を取得
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y / 2, false, 0.0f, back); //背景を描画

	////Display::FixedDraw(320.f, 96.f, false, 0.f, logo); //ロゴを描画

	for (int i = 0; i < 4; i++)
	{
		Display::Draw(960.0f, 352.0f + (96.0f * i), false, 0.0f, choice[i].image, choice[i].ex_rate); //選択肢を描画
	}

	//DrawFormatString(128, 0, GetColor(255, 255, 255), "%d", sound->GetBgmVolume());
	//DrawFormatString(128, 32, GetColor(255, 255, 255), "%d", sound->GetSoundVolume());
	//DrawFormatString(160, 0, GetColor(255, 255, 255), "%d", setting->GetBgmVolume());
	//DrawFormatString(160, 32, GetColor(255, 255, 255), "%d", setting->GetSoundVolume());
	//int pad = key->GetPadOnce(); //押されているボタンを取得
	//DrawFormatString(128, 128, GetColor(255, 255, 255), "%d", pad);
}