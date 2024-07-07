#pragma once
#include "../Define.h"
#include "Singleton.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct Key_Func{
	int key; //�Ή�����L�[�̎��ʎq
	int pad; //�Ή�����{�^���̎��ʎq
};

typedef enum {
	//�{�^��
	Up, //��
	Down, //��
	Left, //��
	Right, //�E
	Jump, //�W�����v(����)
	Attack, //�U��(�߂�)
	L, //Switch�ł���L
	R, //Switch�ł���R
	Plus, //Switch�ł���+
	//Minus, //Switch�ł���-
} Button;

class Key {
private:
	char key_list[256]; //���ݓ��͂���Ă���L�[
	char old_key_list[256]; //��O�ɓ��͂��ꂽ�L�[
	int pad; //�p�b�h�ŉ����ꂽ�{�^��
	int old_pad; //��O�Ƀp�b�h�ŉ����ꂽ�{�^��
	Key_Func button[BUTTON]; //�Ή�����{�^��

	void LoadSetting(); //�ݒ�t�@�C���̓ǂݍ���
public:
	Key(); //�R���X�g���N�^
	void Update(); //�X�V
	void SaveSetting(); //�ݒ�̕ۑ�
	void GetKey(Key_Func* set_key); //����ɑΉ�����L�[���擾
	void SetKey(Key_Func* set_key); //����ɑΉ�����L�[��ύX
	bool KeyCheck(int check); //�L�[��������Ă��邩(���������ɑΉ�)
	bool KeyCheckOnce(int check); //�L�[����x�����ꂽ��(����͉�����Ă����̂�)
	bool KeyCheckLetGo(int check); //�L�[����x�����ꂽ��(����͕����ꂽ�����̂�)
	int GetKeyOnce(); //�����ꂽ�L�[����Ԃ�(����͉�����Ă����̂�)
	int GetPadOnce(); //�����ꂽ�{�^������Ԃ�(����͉�����Ă����̂�)
};