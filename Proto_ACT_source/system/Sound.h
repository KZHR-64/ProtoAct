#pragma once
#include "../Define.h"
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct SoundDataStruct{
	//BGM���̍\����
	std::string name; //�t�@�C����
	int loop_time; //���[�v���鎞��
};

class Sound {
private:
	std::map<int, SoundDataStruct> bgm_data; //BGM�̏��
	std::map<int, int> loaded_bgm; //BGM(�ԍ��A�n���h��)
	std::map<int, SoundDataStruct> effect_data; //���ʉ��̏��
	std::map<int, int> loaded_effect; //���ʉ�(�ԍ��A�n���h��)
	int volume_bgm; //BGM�̉���
	int volume_effect; //���ʉ��̉���
	int playing_bgm; //�Đ�����BGM

	void LoadSoundEffectData(); //���ʉ��������[�h
	void DeleteBgm(); //BGM�̃����������
	void DeleteSoundEffect(); //���ʉ������
public:
	Sound(); //�R���X�g���N�^
	~Sound(); //�f�X�g���N�^
	void LoadSoundEffect(); //���ʉ������[�h
	void LoadBgm(int num); //BGM�����[�h
	void SetBgmVolume(int volume); //bgm�̉��ʂ�ݒ�(����)
	void SetSoundVolume(int volume); //���ʉ��̉��ʂ�ݒ�(����)
	int GetBgmVolume(); //bgm�̉��ʂ��擾
	int GetSoundVolume(); //���ʉ��̉��ʂ��擾
	void PlaySoundEffect(int num); //���ʉ����Đ�(���ʉ��̔ԍ�)
	void PlayBgm(int num); //���y���Đ�(�Ȃ̔ԍ�)
	void StopBgm(); //���y���~
	void StopBgm(int num); //���y���~(�Ȃ̔ԍ�)
};