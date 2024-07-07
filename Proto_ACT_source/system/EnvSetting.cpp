#pragma once
#include "EnvSetting.h"
#include "DxLib.h"

using namespace std;

//コンストラクタ
EnvSetting::EnvSetting() {
	LoadSetting();
}

//設定ファイルの読み込み
void EnvSetting::LoadSetting() {
	ifstream ifs("config.dat");

	//なければデフォルト
	if (ifs.fail()) {
		fps_flag = false;
		volume_bgm = 50;
		volume_effect = 50;
		SaveSetting();
	}
	else {
		string str;
		getline(ifs, str); //ファイルから1行読み込む
		fps_flag = (1 && atoi(str.c_str())); //fpsを表示するか
		getline(ifs, str); //ファイルから1行読み込む
		volume_bgm = atoi(str.c_str()); //BGMの音量
		getline(ifs, str); //ファイルから1行読み込む
		volume_effect = atoi(str.c_str()); //効果音の音量
	}

}

//設定の保存
void EnvSetting::SaveSetting() {
	ofstream ofs("config.dat");

	ofs << fps_flag << "\n";
	ofs << volume_bgm << "\n";
	ofs << volume_effect << "\n";

	ofs.close();
}

//FPSを表示するかを返す
bool EnvSetting::GetFpsFlag() {
	return fps_flag;
}

//FPSを表示するかを設定
void EnvSetting::SetFpsFlag(bool flag) {
	fps_flag = flag;
}

//BGMの音量を返す
int EnvSetting::GetBgmVolume() {
	return volume_bgm;
}

//BGMの音量を設定
void EnvSetting::SetBgmVolume(int num) {
	volume_bgm = num;
}

//効果音の音量を返す
int EnvSetting::GetSoundVolume() {
	return volume_effect;
}

//効果音の音量を設定
void EnvSetting::SetSoundVolume(int num) {
	volume_effect = num;
}