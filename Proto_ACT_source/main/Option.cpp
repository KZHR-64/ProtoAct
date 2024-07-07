#pragma once
#include "DxLib.h"
#include "Option.h"

using namespace std;

Option::Option(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {
	Reset();

	cursor_pos = 0; //cursorの位置を初期化
	count = 0; //カウンターを初期化
}

Option::~Option() {
	
}

//初期化
void Option::Reset() {
	
}

//事前のロード
void Option::Load() {
	if (loaded) return; //ロード済みなら終了

	sound->LoadBgm(1); //曲をロード
	image->LoadBackImage(1); //背景をロード

	data_set.fps_flag = setting->GetFpsFlag(); //FPS表示の設定を取得
	data_set.volume_bgm = setting->GetBgmVolume(); //BGMの音量を取得
	data_set.volume_effect = setting->GetSoundVolume(); //効果音の音量を取得

	//画像を設定
	on_hundle = image->GetEffectImage(3, 1);
	off_hundle = image->GetEffectImage(3, 0);
	graduation_hundle = image->GetEffectImage(5, 0);

	loaded = true; //ロードしたフラグをtrueに
}

//設定の保存
void Option::SaveSetting() {
	setting->SetFpsFlag(data_set.fps_flag); //FPS表示の設定を取得
	setting->SetBgmVolume(data_set.volume_bgm); //BGMの音量を取得
	setting->SetSoundVolume(data_set.volume_effect); //効果音の音量を取得

	setting->SaveSetting();
}

//更新
void Option::Update(){
	//切替フラグがtrueの場合
	if (start_flag) {
		sound->PlayBgm(1); //曲を再生
		start_flag = false; //切替フラグをfalseに
	}

	//上キーが押されていたら
	if (key->KeyCheckOnce(Up)){
		sound->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos = (cursor_pos - 1); //カーソルを上に移動
	}

	//下キーが押されていたら
	if (key->KeyCheckOnce(Down)){
		sound->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos = (cursor_pos + 1); //カーソルを下に移動
	}

	if (cursor_pos < 0) cursor_pos = 0;
	if (2 < cursor_pos) cursor_pos = 2;

	//左右の入力情報を取得
	bool left = key->KeyCheck(Left);
	bool right = key->KeyCheck(Right);

	if (left || right){
		count++; //カウンターを増加
        //カウントが1か4の倍数の場合
		if (count == 1 || (count % 4 == 0 && 30 < count)) {
			//カーソル位置で処理を決定
			switch (cursor_pos)
			{
			case 0:
				//fps表示
				data_set.fps_flag = !data_set.fps_flag;
				fps->SetDrawFlag(data_set.fps_flag);
				break;
			case 1:
				//BGM音量
				if (left) {
					data_set.volume_bgm--;
				}
				else if (right) {
					data_set.volume_bgm++;
				}
				//音量を調整
				if (data_set.volume_bgm < 0) {
					data_set.volume_bgm = 0;
				}
				if (VOLUME_MAX < data_set.volume_bgm) {
					data_set.volume_bgm = VOLUME_MAX;
				}
				sound->SetBgmVolume(data_set.volume_bgm); //音量を設定
				break;
			case 2:
				//効果音音量
				if (left) {
					data_set.volume_effect--;
				}
				else if (right) {
					data_set.volume_effect++;
				}
				//音量を調整
				if (data_set.volume_effect < 0) {
					data_set.volume_effect = 0;
				}
				if (VOLUME_MAX < data_set.volume_effect) {
					data_set.volume_effect = VOLUME_MAX;
				}
				sound->SetSoundVolume(data_set.volume_effect); //音量を設定
				break;
			default:
				break;
			}
			sound->PlaySoundEffect(0); //効果音を鳴らす
		}
	}
	else {
		count = 0; //カウンターを初期化
	}

	//決定キーが押されていたら
	if (key->KeyCheckOnce(Jump)){
		sound->PlaySoundEffect(1); //効果音を鳴らす

		SaveSetting(); //設定を保存する
		start_flag = true; //帰還フラグを立てる

		modemanager->ChangeMode(Next_Back, false); //メニューに戻る
	}
}

//描画
void Option::Draw(){
	int back = image->GetBackImage(1); //背景を取得
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y / 2, false, 0.0f, back); //背景を描画

	int blend_mode; //表示方法
	int blend; //文字の明るさ

	//FPS
	//選択によって文字の明るさを変更
	blend_mode = (data_set.fps_flag ? DX_BLENDMODE_SUB : DX_BLENDMODE_NOBLEND);
	blend = (data_set.fps_flag ? 96 : 1);
	Display::Draw(672.0f, 192.0f, false, 0.0f, off_hundle, 1.0f, blend_mode, blend); //選択肢を描画
	blend_mode = (data_set.fps_flag ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_SUB);
	blend = (data_set.fps_flag ? 1 : 96);
	Display::Draw(960.0f, 192.0f, false, 0.0f, on_hundle, 1.0f, blend_mode, blend);

	//音量
	for (int i = 0; i < data_set.volume_bgm; i++)
	{
		Display::Draw(420.0f + (8.0f * i), 314.0f, false, 0.0f, graduation_hundle);
	}

	for (int i = 0; i < data_set.volume_effect; i++)
	{
		Display::Draw(420.0f + (8.0f * i), 436.0f, false, 0.0f, graduation_hundle);
	}

	//選択した位置以外は少し暗くする
	for (int i = 0; i < 3; i++)
	{
		if (i == cursor_pos) continue;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 131 + (122 * i), WINDOW_X, 253 + (122 * i), GetColor(128, 128, 128), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}