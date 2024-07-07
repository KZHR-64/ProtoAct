#pragma once
#include "../Define.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class EnvSetting {
private:
	void LoadSetting(); //設定ファイルの読み込み

	bool fps_flag;		//FPSを表示するか
	int volume_bgm;		//BGMの音量
	int volume_effect;	//効果音の音量
public:
	EnvSetting(); //コンストラクタ
	void SaveSetting(); //設定の保存
	bool GetFpsFlag(); //FPSを表示するかを返す
	void SetFpsFlag(bool flag); //FPSを表示するかを設定
	int GetBgmVolume(); //BGMの音量を返す
	void SetBgmVolume(int num); //BGMの音量を設定
	int GetSoundVolume(); //効果音の音量を返す
	void SetSoundVolume(int num); //効果音の音量を設定
};