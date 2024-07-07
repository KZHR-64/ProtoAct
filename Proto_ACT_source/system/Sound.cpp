#pragma once
#include "Sound.h"
#include "DxLib.h"
#include <iostream>

using namespace std;

//�R���X�g���N�^
Sound::Sound() {

	int num;

	playing_bgm = -1;
	volume_bgm = 0;
	volume_effect = 0;

	ifstream ifs("data/bgm/bgm_data.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		// ���s�R�[�h���폜
		if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
		if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ',');
		bgm_data[num].name = "data/bgm/" + s; //�t�@�C�������i�[
		getline(ss, s, ',');
		bgm_data[num].loop_time = atoi(s.c_str()); //���[�v���Ԃ��i�[
	}
	ifs.close();

	LoadSoundEffectData();
}

//�f�X�g���N�^
Sound::~Sound() {
	DeleteBgm();
	DeleteSoundEffect();
	bgm_data.clear();
	effect_data.clear();
}

//���ʉ��������[�h
void Sound::LoadSoundEffectData() {

	int num;

	ifstream ifs("data/sound/sound_data.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		// ���s�R�[�h���폜
		if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
		if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ',');
		effect_data[num].name = "data/sound/" + s; //�t�@�C�������i�[
		getline(ss, s, ',');
		effect_data[num].loop_time = atoi(s.c_str()); //���[�v���Ԃ��i�[
	}
	ifs.close();
}

//���ʉ������[�h
void Sound::LoadSoundEffect() {
	for (auto& var : effect_data)
	{
		loaded_effect[var.first] = LoadSoundMem(var.second.name.c_str()); //���ʉ���ǂݍ���
	}
}

//BGM�����[�h
void Sound::LoadBgm(int num) {

	//BGM����T��
	auto data_num = bgm_data.find(num);
	//�Ȃ������ꍇ
	if (data_num == bgm_data.end()) {
		return; //�I��
	}

	//BGM��T��
	auto bgm_num = loaded_bgm.find(num); //BGM������
	//�Ȃ������ꍇ
	if (bgm_num == loaded_bgm.end()) {
		loaded_bgm[num] = LoadSoundMem(bgm_data[num].name.c_str()); //BGM�����[�h
	}
}

//���ʉ������
void Sound::DeleteSoundEffect() {
	for (auto& var : loaded_effect)
	{
		DeleteSoundMem(var.second);
	}
	effect_data.clear(); //�����������
}

//BGM�̃����������
void Sound::DeleteBgm() {
	StopBgm();
	for (auto& var : loaded_bgm)
	{
		DeleteSoundMem(var.second);
	}
	loaded_bgm.clear(); //�����������
}

//bgm�̉��ʂ�ݒ�
void Sound::SetBgmVolume(int volume) {
	volume_bgm = volume; //���ʂ�ݒ�
	float play_volume = 255.0f * ((float)volume_bgm / 100.0f); //���ۂɎg�p���鉹�ʂ��v�Z
	if (playing_bgm < 0) return;
	//�Ȃ��Đ����Ȃ�
	if (CheckSoundMem(loaded_bgm[playing_bgm]) == 1) {
		ChangeVolumeSoundMem((int)play_volume, loaded_bgm[playing_bgm]); //���ʂ𒲐�
	}
}

//���ʉ��̉��ʂ�ݒ�
void Sound::SetSoundVolume(int volume) {
	volume_effect = volume; //���ʂ�ݒ�
}

//bgm�̉��ʂ��擾
int Sound::GetBgmVolume() {
	return volume_bgm;
}

//���ʉ��̉��ʂ��擾
int Sound::GetSoundVolume() {
	return volume_effect;
}

//���ʉ����Đ�
void Sound::PlaySoundEffect(int num) {
	//���ʉ���T��
	auto bgm_num = loaded_effect.find(num); //BGM������
	//�������ꍇ
	if (bgm_num != loaded_effect.end()) {
		float play_volume = 255.0f * ((float)volume_effect / 100.0f); //���ۂɎg�p���鉹�ʂ��v�Z
		ChangeVolumeSoundMem((int)play_volume, loaded_effect[num]); //���ʂ𒲐�
		PlaySoundMem(loaded_effect[num], DX_PLAYTYPE_BACK); //���ʉ����Đ�
	}
}

//���y���Đ�
void Sound::PlayBgm(int num) {

	//BGM��T��
	auto bgm_num = loaded_bgm.find(num); //BGM������
	//�������ꍇ
	if (bgm_num != loaded_bgm.end()) {
		if (CheckSoundMem(loaded_bgm[num]) == 1) return; //�Đ����Ȃ牽�����Ȃ�
		StopBgm();
		float play_volume = 255.0f * ((float)volume_bgm / 100.0f); //���ۂɎg�p���鉹�ʂ��v�Z
		ChangeVolumeSoundMem((int)play_volume, loaded_bgm[num]); //���ʂ𒲐�
		PlaySoundMem(loaded_bgm[num], DX_PLAYTYPE_LOOP); //BGM���Đ�
		playing_bgm = num; //�Đ����̋Ȃ��擾
	}
}

//���y���~
void Sound::StopBgm() {
	// ���[�h����BGM���m�F
	for (auto& var : loaded_bgm)
	{
		// �Đ�����BGM������Β�~����
		if (CheckSoundMem(var.second) == 1) {
			StopSoundMem(var.second);
		}
	}
}

//���y���~
void Sound::StopBgm(int num) {
	StopSoundMem(loaded_bgm[num]);
}