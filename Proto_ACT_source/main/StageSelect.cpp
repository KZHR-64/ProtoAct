#pragma once
#include "DxLib.h"
#include "StageSelect.h"
#include "Parameter.h"

using namespace std;

StageSelect::StageSelect(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {
	stage_num = 0;
	cursor_pos_x = 0;
	cursor_pos_y = 0;
	
	message_font = -1; //フォント情報
	
	Reset();
}

//デストラクタ
StageSelect::~StageSelect() {
	DeleteFontToHandle(message_font);
}

//初期化
void StageSelect::Reset() {

}

//事前のロード
void StageSelect::Load() {
	if (loaded) return; //ロード済みなら終了

	sound->LoadBgm(2); //曲をロード
	image->LoadBackImage(3); //背景をロード

	message_font = CreateFontToHandle("Meiryo UI", 48, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2); //フォント情報

	//サブタイトルの読み込み
	ifstream ifs("data/subtitle.csv");

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	//設定
	for (int i = 0; i < STAGE_MAX; i++) {
		subtitle[i].select_flag = true;
		subtitle[i].hundle = image->GetEffectImage(10, i); //サムネイルを取得

		//サブタイトルを取得
		string str, s;
		getline(ifs, str);
		//選択可能なら
		if (subtitle[i].select_flag) {
			// 改行コードを削除
			if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
			if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

			stringstream ss{ str };
			getline(ss, s, ','); //カンマまで読み込む
			subtitle[i].str1 = s;
			getline(ss, s, ','); //カンマまで読み込む
			subtitle[i].str2 = s;
		}
		//選択不可なら
		else {
			subtitle[i].hundle = image->GetEffectImage(10, 0);
			subtitle[i].str1 = "？";
			subtitle[i].str2 = "？";
		}
	}

	loaded = true; //ロードしたフラグをtrueに
}

//情報の更新
void StageSelect::SetData() {

}

//更新
void StageSelect::Update() {
	//切替フラグがtrueの場合
	if (start_flag) {
		Reset();
		sound->PlayBgm(2); //曲を再生
		start_flag = false; //切替フラグをfalseに
	}

	//ステージ選択
	if (key->KeyCheckOnce(Left)){ //左ボタンが押されていたら
		sound->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos_x = (cursor_pos_x + 3) % 4; //カーソル番号を減らす
	}
	if (key->KeyCheckOnce(Right)){ //右ボタンが押されていたら
		sound->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos_x = (cursor_pos_x + 1) % 4; //カーソル番号を増やす
	}
	if (key->KeyCheckOnce(Up)){ //下ボタンが押されていたら
		sound->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos_y = (cursor_pos_y + 1) % 2; //カーソル番号を減らす
	}
	if (key->KeyCheckOnce(Down)){ //下ボタンが押されていたら
		sound->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos_y = (cursor_pos_y + 1) % 2; //カーソル番号を増やす
	}

	stage_num = (cursor_pos_y * 4) + cursor_pos_x; //ステージ番号を設定
	if (stage_num < 0) {
		stage_num = 0;//ステージ番号が0未満になった場合は0に
	}
	if (STAGE_MAX <= stage_num) {
		stage_num = STAGE_MAX - 1;//ステージ番号が最大を超えた場合は最大値に
		cursor_pos_x = (STAGE_MAX - 1) % 4;
		cursor_pos_y = STAGE_MAX / 4;
	}

	if (key->KeyCheckOnce(Jump)){ //決定ボタンが押されていたら
		//ステージが選択可能なら
		if (subtitle[stage_num].select_flag) {
			sound->PlaySoundEffect(1); //効果音を鳴らす
			modemanager->SetStageNum(stage_num); //ステージを設定
			start_flag = true; //帰還フラグを立てる
			modemanager->ChangeMode(Next_Game); //モードをゲームに変更
		}
		//そうでなければ
		else {
			sound->PlaySoundEffect(3); //効果音を鳴らす
		}
	}
	if (key->KeyCheckOnce(Attack)){ //戻るボタンが押されていたら
		sound->PlaySoundEffect(2); //効果音を鳴らす
		modemanager->ChangeMode(Next_Back); //メニューに戻る
	}
}

//描画
void StageSelect::Draw() {

	int back = image->GetBackImage(3); //背景を取得
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y / 2, false, 0.0f, back); //背景を描画

	//カーソルを表示
	//int cursor_x = 240 + (cursor_pos_x * 200);
	//int cursor_y = 128 + (cursor_pos_y * 200);
	int cursor_x = 340 + (cursor_pos_x * 200);
	int cursor_y = 256 + (cursor_pos_y * 200);
	DrawBox(cursor_x, cursor_y, cursor_x + 200, cursor_y + 200, GetColor(238, 131, 111), true);

	//サムネイルを表示
	for (int i = 0; i < STAGE_MAX; i++) {
		//float x = 244.0f + 96.0f + ((i % 4) * 200.0f);
		//float y = 132.0f + 96.0f + ((float)(i / 4) * 200.0f);
		float x = 344.0f + 96.0f + ((i % 4) * 200.0f);
		float y = 260.0f + 96.0f + ((float)(i / 4) * 200.0f);
		Display::Draw(x, y, false, 0.0f, subtitle[i].hundle);
	}

	//DrawFormatString(0, 30, GetColor(255, 255, 255), "%d", stage_num);
	
	DrawStringToHandle(96, 562, subtitle[stage_num].str1.c_str(), GetColor(236, 236, 236), message_font, GetColor(21, 169, 175));
	DrawStringToHandle(96, 628, subtitle[stage_num].str2.c_str(), GetColor(236, 236, 236), message_font, GetColor(21, 169, 175));
}