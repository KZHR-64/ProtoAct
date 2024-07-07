#pragma once
#include "../Define.h"
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct SoundDataStruct{
	//BGM情報の構造体
	std::string name; //ファイル名
	int loop_time; //ループする時間
};

class Sound {
private:
	std::map<int, SoundDataStruct> bgm_data; //BGMの情報
	std::map<int, int> loaded_bgm; //BGM(番号、ハンドル)
	std::map<int, SoundDataStruct> effect_data; //効果音の情報
	std::map<int, int> loaded_effect; //効果音(番号、ハンドル)
	int volume_bgm; //BGMの音量
	int volume_effect; //効果音の音量
	int playing_bgm; //再生中のBGM

	void LoadSoundEffectData(); //効果音情報をロード
	void DeleteBgm(); //BGMのメモリを解放
	void DeleteSoundEffect(); //効果音を解放
public:
	Sound(); //コンストラクタ
	~Sound(); //デストラクタ
	void LoadSoundEffect(); //効果音をロード
	void LoadBgm(int num); //BGMをロード
	void SetBgmVolume(int volume); //bgmの音量を設定(音量)
	void SetSoundVolume(int volume); //効果音の音量を設定(音量)
	int GetBgmVolume(); //bgmの音量を取得
	int GetSoundVolume(); //効果音の音量を取得
	void PlaySoundEffect(int num); //効果音を再生(効果音の番号)
	void PlayBgm(int num); //音楽を再生(曲の番号)
	void StopBgm(); //音楽を停止
	void StopBgm(int num); //音楽を停止(曲の番号)
};