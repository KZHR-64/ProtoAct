#pragma once
#include "../Define.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class EnvSetting {
private:
	void LoadSetting(); //�ݒ�t�@�C���̓ǂݍ���

	bool fps_flag;		//FPS��\�����邩
	int volume_bgm;		//BGM�̉���
	int volume_effect;	//���ʉ��̉���
public:
	EnvSetting(); //�R���X�g���N�^
	void SaveSetting(); //�ݒ�̕ۑ�
	bool GetFpsFlag(); //FPS��\�����邩��Ԃ�
	void SetFpsFlag(bool flag); //FPS��\�����邩��ݒ�
	int GetBgmVolume(); //BGM�̉��ʂ�Ԃ�
	void SetBgmVolume(int num); //BGM�̉��ʂ�ݒ�
	int GetSoundVolume(); //���ʉ��̉��ʂ�Ԃ�
	void SetSoundVolume(int num); //���ʉ��̉��ʂ�ݒ�
};