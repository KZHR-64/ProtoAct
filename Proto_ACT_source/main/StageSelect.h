#pragma once
#include "ModeBase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct SubTitleStruct
{
	//�T�u�^�C�g���̍\����
	int hundle; //�T���l�C���̃n���h��
	bool select_flag; //�I�ׂ邩
	std::string str1; //�T�u�^�C�g��1�s��
	std::string str2; //�T�u�^�C�g��2�s��
};

class StageSelect : public ModeBase {
private:
	void Reset(); //������
	void SetData(); //���̍X�V
	int stage_num; //�I���X�e�[�W
	int cursor_pos_x; //�J�[�\���̈ʒu
	int cursor_pos_y; //�J�[�\���̈ʒu

	int message_font; //�t�H���g���

	SubTitleStruct subtitle[STAGE_MAX];
public:
	StageSelect(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~StageSelect(); //�f�X�g���N�^
	void Load(); //���O�̃��[�h
	void Update(); //�X�V
	void Draw(); //�`��
};