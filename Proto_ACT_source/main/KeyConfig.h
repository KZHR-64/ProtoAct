#pragma once
#include "ModeBase.h"
#include <iostream>
#include <string>
#include <sstream>

class KeyConfig : public ModeBase {
private:

	int message_font; //�t�H���g���

	std::map<int, std::string> key_map; //�L�[�̔ԍ��ɑΉ����镶��

	int key_cursor; //�J�[�\���̈ʒu(�L�[�R���t�B�O)
	int pad_cursor; //�J�[�\���̈ʒu(�p�b�h�R���t�B�O)

	Key_Func button[BUTTON]; //�Ή�����{�^��

	void Reset(); //������

public:
	KeyConfig(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~KeyConfig(); //�f�X�g���N�^
	void Load(); //���O�̃��[�h
	void Update(); //�X�V
	void Draw(); //�`��
};