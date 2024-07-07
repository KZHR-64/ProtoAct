#pragma once
#include "DxLib.h"
#include "StageSelect.h"
#include "Parameter.h"

using namespace std;

StageSelect::StageSelect(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {
	stage_num = 0;
	cursor_pos_x = 0;
	cursor_pos_y = 0;
	
	message_font = -1; //�t�H���g���
	
	Reset();
}

//�f�X�g���N�^
StageSelect::~StageSelect() {
	DeleteFontToHandle(message_font);
}

//������
void StageSelect::Reset() {

}

//���O�̃��[�h
void StageSelect::Load() {
	if (loaded) return; //���[�h�ς݂Ȃ�I��

	sound->LoadBgm(2); //�Ȃ����[�h
	image->LoadBackImage(3); //�w�i�����[�h

	message_font = CreateFontToHandle("Meiryo UI", 48, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2); //�t�H���g���

	//�T�u�^�C�g���̓ǂݍ���
	ifstream ifs("data/subtitle.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	//�ݒ�
	for (int i = 0; i < STAGE_MAX; i++) {
		subtitle[i].select_flag = true;
		subtitle[i].hundle = image->GetEffectImage(10, i); //�T���l�C�����擾

		//�T�u�^�C�g�����擾
		string str, s;
		getline(ifs, str);
		//�I���\�Ȃ�
		if (subtitle[i].select_flag) {
			// ���s�R�[�h���폜
			if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
			if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

			stringstream ss{ str };
			getline(ss, s, ','); //�J���}�܂œǂݍ���
			subtitle[i].str1 = s;
			getline(ss, s, ','); //�J���}�܂œǂݍ���
			subtitle[i].str2 = s;
		}
		//�I��s�Ȃ�
		else {
			subtitle[i].hundle = image->GetEffectImage(10, 0);
			subtitle[i].str1 = "�H";
			subtitle[i].str2 = "�H";
		}
	}

	loaded = true; //���[�h�����t���O��true��
}

//���̍X�V
void StageSelect::SetData() {

}

//�X�V
void StageSelect::Update() {
	//�ؑփt���O��true�̏ꍇ
	if (start_flag) {
		Reset();
		sound->PlayBgm(2); //�Ȃ��Đ�
		start_flag = false; //�ؑփt���O��false��
	}

	//�X�e�[�W�I��
	if (key->KeyCheckOnce(Left)){ //���{�^����������Ă�����
		sound->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos_x = (cursor_pos_x + 3) % 4; //�J�[�\���ԍ������炷
	}
	if (key->KeyCheckOnce(Right)){ //�E�{�^����������Ă�����
		sound->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos_x = (cursor_pos_x + 1) % 4; //�J�[�\���ԍ��𑝂₷
	}
	if (key->KeyCheckOnce(Up)){ //���{�^����������Ă�����
		sound->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos_y = (cursor_pos_y + 1) % 2; //�J�[�\���ԍ������炷
	}
	if (key->KeyCheckOnce(Down)){ //���{�^����������Ă�����
		sound->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos_y = (cursor_pos_y + 1) % 2; //�J�[�\���ԍ��𑝂₷
	}

	stage_num = (cursor_pos_y * 4) + cursor_pos_x; //�X�e�[�W�ԍ���ݒ�
	if (stage_num < 0) {
		stage_num = 0;//�X�e�[�W�ԍ���0�����ɂȂ����ꍇ��0��
	}
	if (STAGE_MAX <= stage_num) {
		stage_num = STAGE_MAX - 1;//�X�e�[�W�ԍ����ő�𒴂����ꍇ�͍ő�l��
		cursor_pos_x = (STAGE_MAX - 1) % 4;
		cursor_pos_y = STAGE_MAX / 4;
	}

	if (key->KeyCheckOnce(Jump)){ //����{�^����������Ă�����
		//�X�e�[�W���I���\�Ȃ�
		if (subtitle[stage_num].select_flag) {
			sound->PlaySoundEffect(1); //���ʉ���炷
			modemanager->SetStageNum(stage_num); //�X�e�[�W��ݒ�
			start_flag = true; //�A�҃t���O�𗧂Ă�
			modemanager->ChangeMode(Next_Game); //���[�h���Q�[���ɕύX
		}
		//�����łȂ����
		else {
			sound->PlaySoundEffect(3); //���ʉ���炷
		}
	}
	if (key->KeyCheckOnce(Attack)){ //�߂�{�^����������Ă�����
		sound->PlaySoundEffect(2); //���ʉ���炷
		modemanager->ChangeMode(Next_Back); //���j���[�ɖ߂�
	}
}

//�`��
void StageSelect::Draw() {

	int back = image->GetBackImage(3); //�w�i���擾
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y / 2, false, 0.0f, back); //�w�i��`��

	//�J�[�\����\��
	//int cursor_x = 240 + (cursor_pos_x * 200);
	//int cursor_y = 128 + (cursor_pos_y * 200);
	int cursor_x = 340 + (cursor_pos_x * 200);
	int cursor_y = 256 + (cursor_pos_y * 200);
	DrawBox(cursor_x, cursor_y, cursor_x + 200, cursor_y + 200, GetColor(238, 131, 111), true);

	//�T���l�C����\��
	for (int i = 0; i < STAGE_MAX; i++) {
		//float x = 244.0f + 96.0f + ((i % 4) * 200.0f);
		//float y = 132.0f + 96.0f + ((float)(i / 4) * 200.0f);
		float x = 344.0f + 96.0f + ((i % 4) * 200.0f);
		float y = 260.0f + 96.0f + ((float)(i / 4) * 200.0f);
		Display::Draw(x, y, false, 0.0f, subtitle[i].hundle);
	}

	//DrawFormatString(0, 30, GetColor(255, 255, 255), "%d", stage_num);
	
	DrawStringToHandle(96, 562, subtitle[stage_num].str1.c_str(), GetColor(236, 236, 236), message_font, GetColor(21, 169, 175));
	DrawStringToHandle(96, 628, subtitle[stage_num].str2.c_str(), GetColor(236, 236, 236), message_font, GetColor(21, 169, 175));
}