#pragma once
#include "EnvSetting.h"
#include "DxLib.h"

using namespace std;

//�R���X�g���N�^
EnvSetting::EnvSetting() {
	LoadSetting();
}

//�ݒ�t�@�C���̓ǂݍ���
void EnvSetting::LoadSetting() {
	ifstream ifs("config.dat");

	//�Ȃ���΃f�t�H���g
	if (ifs.fail()) {
		fps_flag = false;
		volume_bgm = 50;
		volume_effect = 50;
		SaveSetting();
	}
	else {
		string str;
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		fps_flag = (1 && atoi(str.c_str())); //fps��\�����邩
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		volume_bgm = atoi(str.c_str()); //BGM�̉���
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		volume_effect = atoi(str.c_str()); //���ʉ��̉���
	}

}

//�ݒ�̕ۑ�
void EnvSetting::SaveSetting() {
	ofstream ofs("config.dat");

	ofs << fps_flag << "\n";
	ofs << volume_bgm << "\n";
	ofs << volume_effect << "\n";

	ofs.close();
}

//FPS��\�����邩��Ԃ�
bool EnvSetting::GetFpsFlag() {
	return fps_flag;
}

//FPS��\�����邩��ݒ�
void EnvSetting::SetFpsFlag(bool flag) {
	fps_flag = flag;
}

//BGM�̉��ʂ�Ԃ�
int EnvSetting::GetBgmVolume() {
	return volume_bgm;
}

//BGM�̉��ʂ�ݒ�
void EnvSetting::SetBgmVolume(int num) {
	volume_bgm = num;
}

//���ʉ��̉��ʂ�Ԃ�
int EnvSetting::GetSoundVolume() {
	return volume_effect;
}

//���ʉ��̉��ʂ�ݒ�
void EnvSetting::SetSoundVolume(int num) {
	volume_effect = num;
}