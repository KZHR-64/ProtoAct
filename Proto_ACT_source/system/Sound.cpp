#pragma once
#include "Sound.h"
#include "DxLib.h"
#include <iostream>

using namespace std;

//コンストラクタ
Sound::Sound() {

	int num;

	playing_bgm = -1;
	volume_bgm = 0;
	volume_effect = 0;

	ifstream ifs("data/bgm/bgm_data.csv");

	//なければ終了
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		// 改行コードを削除
		if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
		if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ',');
		bgm_data[num].name = "data/bgm/" + s; //ファイル名を格納
		getline(ss, s, ',');
		bgm_data[num].loop_time = atoi(s.c_str()); //ループ時間を格納
	}
	ifs.close();

	LoadSoundEffectData();
}

//デストラクタ
Sound::~Sound() {
	DeleteBgm();
	DeleteSoundEffect();
	bgm_data.clear();
	effect_data.clear();
}

//効果音情報をロード
void Sound::LoadSoundEffectData() {

	int num;

	ifstream ifs("data/sound/sound_data.csv");

	//なければ終了
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		// 改行コードを削除
		if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
		if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ',');
		effect_data[num].name = "data/sound/" + s; //ファイル名を格納
		getline(ss, s, ',');
		effect_data[num].loop_time = atoi(s.c_str()); //ループ時間を格納
	}
	ifs.close();
}

//効果音をロード
void Sound::LoadSoundEffect() {
	for (auto& var : effect_data)
	{
		loaded_effect[var.first] = LoadSoundMem(var.second.name.c_str()); //効果音を読み込み
	}
}

//BGMをロード
void Sound::LoadBgm(int num) {

	//BGM情報を探す
	auto data_num = bgm_data.find(num);
	//なかった場合
	if (data_num == bgm_data.end()) {
		return; //終了
	}

	//BGMを探す
	auto bgm_num = loaded_bgm.find(num); //BGMを検索
	//なかった場合
	if (bgm_num == loaded_bgm.end()) {
		loaded_bgm[num] = LoadSoundMem(bgm_data[num].name.c_str()); //BGMをロード
	}
}

//効果音を解放
void Sound::DeleteSoundEffect() {
	for (auto& var : loaded_effect)
	{
		DeleteSoundMem(var.second);
	}
	effect_data.clear(); //メモリを解放
}

//BGMのメモリを解放
void Sound::DeleteBgm() {
	StopBgm();
	for (auto& var : loaded_bgm)
	{
		DeleteSoundMem(var.second);
	}
	loaded_bgm.clear(); //メモリを解放
}

//bgmの音量を設定
void Sound::SetBgmVolume(int volume) {
	volume_bgm = volume; //音量を設定
	float play_volume = 255.0f * ((float)volume_bgm / 100.0f); //実際に使用する音量を計算
	if (playing_bgm < 0) return;
	//曲が再生中なら
	if (CheckSoundMem(loaded_bgm[playing_bgm]) == 1) {
		ChangeVolumeSoundMem((int)play_volume, loaded_bgm[playing_bgm]); //音量を調整
	}
}

//効果音の音量を設定
void Sound::SetSoundVolume(int volume) {
	volume_effect = volume; //音量を設定
}

//bgmの音量を取得
int Sound::GetBgmVolume() {
	return volume_bgm;
}

//効果音の音量を取得
int Sound::GetSoundVolume() {
	return volume_effect;
}

//効果音を再生
void Sound::PlaySoundEffect(int num) {
	//効果音を探す
	auto bgm_num = loaded_effect.find(num); //BGMを検索
	//あった場合
	if (bgm_num != loaded_effect.end()) {
		float play_volume = 255.0f * ((float)volume_effect / 100.0f); //実際に使用する音量を計算
		ChangeVolumeSoundMem((int)play_volume, loaded_effect[num]); //音量を調整
		PlaySoundMem(loaded_effect[num], DX_PLAYTYPE_BACK); //効果音を再生
	}
}

//音楽を再生
void Sound::PlayBgm(int num) {

	//BGMを探す
	auto bgm_num = loaded_bgm.find(num); //BGMを検索
	//あった場合
	if (bgm_num != loaded_bgm.end()) {
		if (CheckSoundMem(loaded_bgm[num]) == 1) return; //再生中なら何もしない
		StopBgm();
		float play_volume = 255.0f * ((float)volume_bgm / 100.0f); //実際に使用する音量を計算
		ChangeVolumeSoundMem((int)play_volume, loaded_bgm[num]); //音量を調整
		PlaySoundMem(loaded_bgm[num], DX_PLAYTYPE_LOOP); //BGMを再生
		playing_bgm = num; //再生中の曲を取得
	}
}

//音楽を停止
void Sound::StopBgm() {
	// ロードしたBGMを確認
	for (auto& var : loaded_bgm)
	{
		// 再生中のBGMがあれば停止する
		if (CheckSoundMem(var.second) == 1) {
			StopSoundMem(var.second);
		}
	}
}

//音楽を停止
void Sound::StopBgm(int num) {
	StopSoundMem(loaded_bgm[num]);
}