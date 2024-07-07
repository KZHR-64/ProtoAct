#pragma once
#include "DxLib.h"
#include "KeyConfig.h"

using namespace std;

KeyConfig::KeyConfig(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {

	Reset();

	message_font = CreateFontToHandle("Meiryo UI", 24, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1); //フォント情報

	key_map[KEY_INPUT_BACK] = "BackSpace";	// バックスペースキー
	key_map[KEY_INPUT_TAB] = "Tab";	// タブキー
	key_map[KEY_INPUT_RETURN] = "Enter";	// エンターキー
	key_map[KEY_INPUT_LSHIFT] = "LShift";	// 左シフトキー
	key_map[KEY_INPUT_RSHIFT] = "Rshift";	// 右シフトキー
	key_map[KEY_INPUT_LCONTROL] = "LCtrl";	// 左コントロールキー
	key_map[KEY_INPUT_RCONTROL] = "Rctrl";	// 右コントロールキー
	key_map[KEY_INPUT_ESCAPE] = "Esc";	// エスケープキー
	key_map[KEY_INPUT_SPACE] = "Space";	// スペースキー
	key_map[KEY_INPUT_PGUP] = "PgUp";	// ＰａｇｅＵＰキー
	key_map[KEY_INPUT_PGDN] = "PgDn";	// ＰａｇｅＤｏｗｎキー
	key_map[KEY_INPUT_END] = "End";	// エンドキー
	key_map[KEY_INPUT_HOME] = "Home";	// ホームキー
	key_map[KEY_INPUT_LEFT] = "←";	// 左キー
	key_map[KEY_INPUT_UP] = "↑";	// 上キー
	key_map[KEY_INPUT_RIGHT] = "→";	// 右キー
	key_map[KEY_INPUT_DOWN] = "↓";	// 下キー
	key_map[KEY_INPUT_INSERT] = "Insert";	// インサートキー
	key_map[KEY_INPUT_DELETE] = "Delete";	// デリートキー
	key_map[KEY_INPUT_MINUS] = "-";	// －キー
	key_map[KEY_INPUT_YEN] = "\\";	// ￥キー
	key_map[KEY_INPUT_PREVTRACK] = "^";	// ＾キー
	key_map[KEY_INPUT_PERIOD] = ".";	// ．キー
	key_map[KEY_INPUT_SLASH] = "/";	// ／キー
	key_map[KEY_INPUT_LALT] = "LAlt";	// 左ＡＬＴキー
	key_map[KEY_INPUT_RALT] = "RAlt";	// 右ＡＬＴキー
	key_map[KEY_INPUT_SCROLL] = "ScrollLock";	// ScrollLockキー
	key_map[KEY_INPUT_SEMICOLON] = ";";	// ；キー
	key_map[KEY_INPUT_COLON] = ":";	// ：キー
	key_map[KEY_INPUT_LBRACKET] = "[";	// ［キー
	key_map[KEY_INPUT_RBRACKET] = "]";	// ］キー
	key_map[KEY_INPUT_AT] = "@";	// ＠キー
	key_map[KEY_INPUT_BACKSLASH] = "＼";	// ＼キー
	key_map[KEY_INPUT_COMMA] = ",";	// ，キー
	key_map[KEY_INPUT_CAPSLOCK] = "CapsLock";	// CaspLockキー
	key_map[KEY_INPUT_PAUSE] = "Pause";	// PauseBreakキー
	key_map[KEY_INPUT_NUMPAD0] = "0";	// テンキー０
	key_map[KEY_INPUT_NUMPAD1] = "1";	// テンキー１
	key_map[KEY_INPUT_NUMPAD2] = "2";	// テンキー２
	key_map[KEY_INPUT_NUMPAD3] = "3";	// テンキー３
	key_map[KEY_INPUT_NUMPAD4] = "4";	// テンキー４
	key_map[KEY_INPUT_NUMPAD5] = "5";	// テンキー５
	key_map[KEY_INPUT_NUMPAD6] = "6";	// テンキー６
	key_map[KEY_INPUT_NUMPAD7] = "7";	// テンキー７
	key_map[KEY_INPUT_NUMPAD8] = "8";	// テンキー８
	key_map[KEY_INPUT_NUMPAD9] = "9";	// テンキー９
	key_map[KEY_INPUT_MULTIPLY] = "*";	// テンキー＊キー
	key_map[KEY_INPUT_ADD] = "+";	// テンキー＋キー
	key_map[KEY_INPUT_SUBTRACT] = "-";	// テンキー－キー
	key_map[KEY_INPUT_DECIMAL] = ".";	// テンキー．キー
	key_map[KEY_INPUT_DIVIDE] = "/";	// テンキー／キー
	key_map[KEY_INPUT_NUMPADENTER] = "Enter";	// テンキーのエンターキー
	key_map[KEY_INPUT_F1] = "F1";	// Ｆ１キー
	key_map[KEY_INPUT_F2] = "F2";	// Ｆ２キー
	key_map[KEY_INPUT_F3] = "F3";	// Ｆ３キー
	key_map[KEY_INPUT_F4] = "F4";	// Ｆ４キー
	key_map[KEY_INPUT_F5] = "F5";	// Ｆ５キー
	key_map[KEY_INPUT_F6] = "F6";	// Ｆ６キー
	key_map[KEY_INPUT_F7] = "F7";	// Ｆ７キー
	key_map[KEY_INPUT_F8] = "F8";	// Ｆ８キー
	key_map[KEY_INPUT_F9] = "F9";	// Ｆ９キー
	key_map[KEY_INPUT_F10] = "F10";	// Ｆ１０キー
	key_map[KEY_INPUT_F11] = "F11";	// Ｆ１１キー
	key_map[KEY_INPUT_F12] = "F12";	// Ｆ１２キー
	key_map[KEY_INPUT_A] = "A";	// Ａキー
	key_map[KEY_INPUT_B] = "B";	// Ｂキー
	key_map[KEY_INPUT_C] = "C";	// Ｃキー
	key_map[KEY_INPUT_D] = "D";	// Ｄキー
	key_map[KEY_INPUT_E] = "E";	// Ｅキー
	key_map[KEY_INPUT_F] = "F";	// Ｆキー
	key_map[KEY_INPUT_G] = "G";	// Ｇキー
	key_map[KEY_INPUT_H] = "H";	// Ｈキー
	key_map[KEY_INPUT_I] = "I";	// Ｉキー
	key_map[KEY_INPUT_J] = "J";	// Ｊキー
	key_map[KEY_INPUT_K] = "K";	// Ｋキー
	key_map[KEY_INPUT_L] = "L";	// Ｌキー
	key_map[KEY_INPUT_M] = "M";	// Ｍキー
	key_map[KEY_INPUT_N] = "N";	// Ｎキー
	key_map[KEY_INPUT_O] = "O";	// Ｏキー
	key_map[KEY_INPUT_P] = "P";	// Ｐキー
	key_map[KEY_INPUT_Q] = "Q";	// Ｑキー
	key_map[KEY_INPUT_R] = "R";	// Ｒキー
	key_map[KEY_INPUT_S] = "S";	// Ｓキー
	key_map[KEY_INPUT_T] = "T";	// Ｔキー
	key_map[KEY_INPUT_U] = "U";	// Ｕキー
	key_map[KEY_INPUT_V] = "V";	// Ｖキー
	key_map[KEY_INPUT_W] = "W";	// Ｗキー
	key_map[KEY_INPUT_X] = "X";	// Ｘキー
	key_map[KEY_INPUT_Y] = "Y";	// Ｙキー
	key_map[KEY_INPUT_Z] = "Z";	// Ｚキー
	key_map[KEY_INPUT_0] = "0";	// ０キー
	key_map[KEY_INPUT_1] = "1";	// １キー
	key_map[KEY_INPUT_2] = "2";	// ２キー
	key_map[KEY_INPUT_3] = "3";	// ３キー
	key_map[KEY_INPUT_4] = "4";	// ４キー
	key_map[KEY_INPUT_5] = "5";	// ５キー
	key_map[KEY_INPUT_6] = "6";	// ６キー
	key_map[KEY_INPUT_7] = "7";	// ７キー
	key_map[KEY_INPUT_8] = "8";	// ８キー
	key_map[KEY_INPUT_9] = "9";	// ９キー
}

KeyConfig::~KeyConfig() {
	key_map.clear();
	DeleteFontToHandle(message_font);
}

//初期化
void KeyConfig::Reset() {

	key_cursor = 0; //カーソルの位置
	pad_cursor = 0; //カーソルの位置

}

//事前のロード
void KeyConfig::Load() {
	if (loaded) return; //ロード済みなら終了

	sound->LoadBgm(1); //曲をロード
	image->LoadBackImage(2); //背景をロード

	key->GetKey(button); //キー情報を取得

	loaded = true; //ロードしたフラグをtrueに
}

//更新
void KeyConfig::Update(){
	//切替フラグがtrueの場合
	if (start_flag) {
		Reset();
		sound->PlayBgm(1); //曲を再生
		start_flag = false; //切替フラグをfalseに
	}

	int key_num = key->GetKeyOnce(); //押されているキーを取得
	int pad = key->GetPadOnce(); //押されているボタンを取得
	int flag = false; //コンフィグ終了フラグ

	//押されているキーがある場合
	if (key_num != -1) {
		// 最後まで設定していない場合
		if (key_cursor < BUTTON) {
			//他のキーを確認
			for (int i = 0; i < BUTTON; i++)
			{
				if (i == key_cursor) continue; //iがカーソルと一致した場合はスルー
				//すでにキーが設定されている場合
				if (button[i].key == key_num) {
					button[i].key = button[key_cursor].key; //入れ替える
				}
			}
			button[key_cursor].key = key_num; //押されたキーを格納
			key_cursor++; //カーソルを一つ下に移動
		}
		// 最後まで設定している場合
		else {
			flag = true; //コンフィグ終了フラグを立てる
		}
		sound->PlaySoundEffect(1); //効果音を鳴らす
	}

	//押されているボタンがある場合
	if (pad != -1) {
		// 最後まで設定していない場合
		if (pad_cursor < BUTTON) {
			//他のボタンを確認
			for (int i = 0; i < BUTTON; i++)
			{
				if (i == pad_cursor) continue; //iがカーソルと一致した場合はスルー
				//すでにボタンが設定されている場合
				if (button[i].pad == pad) {
					button[i].pad = button[pad_cursor].pad; //入れ替える
				}
			}
			button[pad_cursor].pad = pad; //押されたボタンを格納
			pad_cursor++; //カーソルを一つ下に移動
		}
		// 最後まで設定している場合
		else {
			flag = true; //コンフィグ終了フラグを立てる
		}
		sound->PlaySoundEffect(1); //効果音を鳴らす
	}

	//コンフィグ終了フラグがtrueの場合
	if (flag) {
		key->SetKey(button); //設定を確定する
		key->SaveSetting(); //設定を保存する
		modemanager->ChangeMode(Next_Back); //メニューに戻る
	}
}

//描画
void KeyConfig::Draw(){
	int back = image->GetBackImage(2); //背景を取得
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y / 2, false, 0.0f, back); //背景を描画

	//カーソルの大きさを指定
	int cursor_size_x = 256;
	int cursor_size_y = 60;

	//カーソルの位置を指定
	int key_cursor_x = 616;
	int key_cursor_y = 98 + (cursor_size_y * key_cursor);

	//カーソルの位置を指定
	int pad_cursor_x = 952;
	int pad_cursor_y = 98 + (cursor_size_y * pad_cursor);

	//選択する位置以外は少し暗くする
	for (int i = 0; i <= BUTTON; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		if (i != key_cursor)DrawBox(key_cursor_x, 98 + (cursor_size_y * i), key_cursor_x + cursor_size_x, 98 + (cursor_size_y * i) + cursor_size_y, GetColor(128, 128, 128), true);
		if (i != pad_cursor) DrawBox(pad_cursor_x, 98 + (cursor_size_y * i), pad_cursor_x + cursor_size_x, 98 + (cursor_size_y * i) + cursor_size_y, GetColor(128, 128, 128), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	for (int i = 0; i < BUTTON; i++)
	{
		DrawFormatStringToHandle(key_cursor_x + 24, 98 + (cursor_size_y * i) + 14, GetColor(255, 255, 255), message_font, "%s", key_map[button[i].key].c_str());
		
		int pad_num = (int)log2((float)(button[i].pad));
		DrawFormatStringToHandle(pad_cursor_x + 24, 98 + (cursor_size_y * i) + 14, GetColor(255, 255, 255), message_font, "%d %d", pad_num, button[i].pad);
	}
}