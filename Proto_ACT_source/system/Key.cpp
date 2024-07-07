#pragma once
#include "Key.h"
#include "DxLib.h"

using namespace std;

Key::Key() {
	button[Jump].key = KEY_INPUT_Z; //�W�����v��z�L�[
	button[Jump].pad = 4; //�W�����v��1�{�^��
	button[Attack].key = KEY_INPUT_X; //�U����x�L�[
	button[Attack].pad = 5; //�U����2�{�^��
	button[Up].key = KEY_INPUT_UP; //��ړ��͏�L�[
	button[Up].pad = 3; //��ړ��͏�{�^��
	button[Down].key = KEY_INPUT_DOWN; //���ړ��͉��L�[
	button[Down].pad = 0; //���ړ��͉��{�^��
	button[Left].key = KEY_INPUT_LEFT; //���ړ��͍��L�[
	button[Left].pad = 1; //���ړ��͍��{�^��
	button[Right].key = KEY_INPUT_RIGHT; //�E�ړ��͉E�L�[
	button[Right].pad = 2; //�E�ړ��͉E�{�^��
	button[Plus].key = KEY_INPUT_A; //L�{�^����a�L�[
	button[Plus].pad = 6; //L�{�^����3�{�^��
	//button[Minus].key = KEY_INPUT_S; //R�{�^����s�L�[
	//button[Minus].pad = 7; //R�{�^����4�{�^��

	for (int i = 0; i < 256; i++) {
		old_key_list[i] = 0;
		key_list[i] = 0;
	}

	LoadSetting();

	pad = 0;
	old_pad = 0;
}

//�ݒ�t�@�C���̓ǂݍ���
void Key::LoadSetting() {
	ifstream ifs("key_config.dat");

	//�Ȃ���΃f�t�H���g
	if (ifs.fail()) {
		//�L�[
		button[Jump].key = KEY_INPUT_Z; //�W�����v��z�L�[
		button[Attack].key = KEY_INPUT_X; //�U����x�L�[
		button[Up].key = KEY_INPUT_UP; //��ړ��͏�L�[
		button[Down].key = KEY_INPUT_DOWN; //���ړ��͉��L�[
		button[Left].key = KEY_INPUT_LEFT; //���ړ��͍��L�[
		button[Right].key = KEY_INPUT_RIGHT; //�E�ړ��͉E�L�[
		button[L].key = KEY_INPUT_A; //L�{�^����a�L�[
		button[R].key = KEY_INPUT_S; //R�{�^����s�L�[
		button[Plus].key = KEY_INPUT_D; //+�{�^����D�L�[
		//button[Minus].key = KEY_INPUT_F; //-�{�^����F�L�[

		//�p�b�h
		button[Jump].pad = PAD_INPUT_1; //�W�����v��1�{�^��
		button[Attack].pad = PAD_INPUT_2; //�U����2�{�^��
		button[Up].pad = PAD_INPUT_UP; //��ړ��͏�{�^��
		button[Down].pad = PAD_INPUT_DOWN; //���ړ��͉��{�^��
		button[Left].pad = PAD_INPUT_LEFT; //���ړ��͍��{�^��
		button[Right].pad = PAD_INPUT_RIGHT; //�E�ړ��͉E�{�^��
		button[L].pad = PAD_INPUT_3; //L�{�^����3�{�^��
		button[R].pad = PAD_INPUT_4; //R�{�^����4�{�^��
		button[Plus].pad = PAD_INPUT_5; //+�{�^����5�{�^��
		//button[Minus].pad = PAD_INPUT_6; //-�{�^����6�{�^��
	}
	else {
		string str;
		//�L�[
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Jump].key = atoi(str.c_str()); //�W�����v
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Attack].key = atoi(str.c_str()); //�U��
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Up].key = atoi(str.c_str()); //��ړ�
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Down].key = atoi(str.c_str()); //���ړ�
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Left].key = atoi(str.c_str()); //���ړ�
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Right].key = atoi(str.c_str()); //�E�ړ�
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[L].key = atoi(str.c_str()); //L�{�^��
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[R].key = atoi(str.c_str()); //R�{�^��
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Plus].key = atoi(str.c_str()); //+�{�^��
		//getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		//button[Minus].key = atoi(str.c_str()); //-�{�^��

		//�p�b�h
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Jump].pad = atoi(str.c_str()); //�W�����v
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Attack].pad = atoi(str.c_str()); //�U��
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Up].pad = atoi(str.c_str()); //��ړ�
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Down].pad = atoi(str.c_str()); //���ړ�
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Left].pad = atoi(str.c_str()); //���ړ�
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Right].pad = atoi(str.c_str()); //�E�ړ�
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[L].pad = atoi(str.c_str()); //L�{�^��
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[R].pad = atoi(str.c_str()); //R�{�^��
		getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		button[Plus].pad = atoi(str.c_str()); //+�{�^��
		//getline(ifs, str); //�t�@�C������1�s�ǂݍ���
		//button[Minus].pad = atoi(str.c_str()); //-�{�^��
	}
}

//�ݒ�̕ۑ�
void Key::SaveSetting() {
	ofstream ofs("key_config.dat");

	//�L�[
	ofs << button[Jump].key << "\n";
	ofs << button[Attack].key << "\n";
	ofs << button[Up].key << "\n";
	ofs << button[Down].key << "\n";
	ofs << button[Left].key << "\n";
	ofs << button[Right].key << "\n";
	ofs << button[L].key << "\n";
	ofs << button[R].key << "\n";
	ofs << button[Plus].key << "\n";
	//ofs << button[Minus].key << "\n";
	
	//�p�b�h
	ofs << button[Jump].pad << "\n";
	ofs << button[Attack].pad << "\n";
	ofs << button[Up].pad << "\n";
	ofs << button[Down].pad << "\n";
	ofs << button[Left].pad << "\n";
	ofs << button[Right].pad << "\n";
	ofs << button[L].pad << "\n";
	ofs << button[R].pad << "\n";
	ofs << button[Plus].pad << "\n";
	//ofs << button[Minus].pad << "\n";

	ofs.close();
}

//�X�V
void Key::Update() {
	for (int i = 0; i < 256; i++) old_key_list[i] = key_list[i]; //��O�̓��͏�Ԃ𓾂�
	old_pad = pad; //��O�̓��͏�Ԃ𓾂�
	GetHitKeyStateAll(key_list); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	pad = GetJoypadInputState(DX_INPUT_PAD1); // �S�Ẵ{�^���̓��͏�Ԃ𓾂�
}

//����ɑΉ�����L�[���擾
void Key::GetKey(Key_Func* set_key) {
	for (int i = 0; i < BUTTON; i++)
	{
		set_key[i].key = button[i].key; //�L�[�̐ݒ�
		set_key[i].pad = button[i].pad; //�p�b�h�̐ݒ�
	}
}

//����ɑΉ�����L�[��ύX
void Key::SetKey(Key_Func* set_key) {
	for (int i = 0; i < BUTTON; i++)
	{
		button[i].key = set_key[i].key; //�L�[�̐ݒ�
		button[i].pad = set_key[i].pad; //�p�b�h�̐ݒ�
	}
}

//�L�[��������Ă��邩
bool Key::KeyCheck(int check) {
	if (key_list[button[check].key] != 0 || (pad & button[check].pad)) return true; //�Ή�����L�[���p�b�h�̃{�^����������Ă�����true��
	else return false; //�����łȂ����false��Ԃ�
}

//�L�[����x�����ꂽ��
bool Key::KeyCheckOnce(int check) {
	//�Ή�����L�[���p�b�h�̃{�^����������Ă�����
	if (key_list[button[check].key] != 0 || (pad & button[check].pad)) {
		if (old_key_list[button[check].key] == 0 && !(old_pad & button[check].pad)) return true; //��O�ɉ�����Ă��Ȃ����true��
		else return false; //�����łȂ����false��Ԃ�
	}
	else return false; //�����łȂ����false��Ԃ�
}

//�L�[����x�����ꂽ��
bool Key::KeyCheckLetGo(int check) {
	//�Ή�����L�[���p�b�h�̃{�^����������Ă�����
	if (key_list[button[check].key] == 0 && !(pad & button[check].pad)) {
		if (old_key_list[button[check].key] != 0 || (old_pad & button[check].pad)) return true; //��O�ɉ�����Ă����true��
		else return false; //�����łȂ����false��Ԃ�
	}
	else return false; //�����łȂ����false��Ԃ�
}

//�����ꂽ�L�[����Ԃ�
int Key::GetKeyOnce() {
	for (int i = 0; i < 256; i++)
	{
		// ������Ă���L�[���������ꍇ
		if (key_list[i] != 0) {
			if (old_key_list[i] == 0) return i; //��O�ɉ�����Ă��Ȃ����i��Ԃ�
		}
	}
	return -1; //�Ȃ����-1��Ԃ�
}

//�����ꂽ�{�^������Ԃ�
int Key::GetPadOnce() {
	for (int i = 0; i < 28; i++){
		// ������Ă���{�^�����������ꍇ
		if (pad & (1 << i)){
			if (!(old_pad & (1 << i))) return (int)pow(2, i); //��O�ɉ�����Ă��Ȃ����i��Ԃ�
		}
	}
	return -1; //�Ȃ����-1��Ԃ�
}