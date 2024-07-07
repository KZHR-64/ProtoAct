#pragma once
#include "DxLib.h"
#include "Menu.h"
#include <math.h>

using namespace std;

Menu::Menu(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {

	Reset(); //������
	
	cursor_pos = 0; //cursor�̈ʒu��������
}

//�f�X�g���N�^
Menu::~Menu() {
	
}

//������
void Menu::Reset() {
	count = 0; //�J�E���^�[��������
}

//���O�̃��[�h
void Menu::Load() {
	if (loaded) return; //���[�h�ς݂Ȃ�I��

	sound->LoadBgm(0); //�Ȃ����[�h
	image->LoadBackImage(0); //�w�i�����[�h
	for (int i = 0; i < 4; i++)
	{
		choice[i].image = image->GetEffectImage(0, i); //�摜��ݒ�
		choice[i].ex_rate = 1.0f; //�{����������
	}
	logo = image->GetEffectImage(1, 0); //�摜��ݒ�

	loaded = true; //���[�h�����t���O��true��
}

//�X�V
void Menu::Update(){
	//�ؑփt���O��true�̏ꍇ
	if (start_flag) {
		Reset(); //������
		sound->PlayBgm(0); //�Ȃ��Đ�
		start_flag = false; //�ؑփt���O��false��
	}
	if (key->KeyCheckOnce(Up)){ //��L�[��������Ă�����
		sound->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos += 3; //�J�[�\������Ɉړ�
		count = 0; //�J�E���^�[��������
	}

	if (key->KeyCheckOnce(Down)){ //���L�[��������Ă�����
		sound->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos++; //�J�[�\�������Ɉړ�
		count = 0; //�J�E���^�[��������
	}

	cursor_pos %= 4; //�J�[�\�������킹��

	//�I�����̏�Ԃ��X�V
	for (int i = 0; i < 4; i++)
	{
		if (i == cursor_pos) {
			choice[i].ex_rate = 1.1f + (0.1f * sinf(PI * 2.0f / 90.0f * count)); //�I������Ă���ꍇ�͊g��A�k�����J��Ԃ�
		}
		else {
			choice[i].ex_rate = 1.0f; //�I������Ă��Ȃ���Γ��{
		}
	}

	if (key->KeyCheckOnce(Jump)){ //����L�[��������Ă�����
		sound->PlaySoundEffect(1); //���ʉ���炷
		start_flag = true; //�ؑփt���O�𗧂Ă�
		//�J�[�\���̈ʒu�ɂ���đJ�ڐ��ύX
		switch (cursor_pos)
		{
		case 0:
			modemanager->ChangeMode(Next_StageSelect); //���[�h���X�e�[�W�Z���N�g�ɕύX
			break;
		case 1:
			modemanager->ChangeMode(Next_Option); //���[�h���I�v�V�����ɕύX
			break;
		case 2:
			modemanager->ChangeMode(Next_Config); //���[�h���L�[�R���t�B�O�ɕύX
			break;
		case 3:
			PostMessageA(GetMainWindowHandle(), WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
	}

	/*if (key->KeyCheckOnce(Attack)){ //�߂�{�^����������Ă�����
		sound->PlaySoundEffect(2); //���ʉ���炷
		modemanager->ChangeMode(Next_Back); //�I�[�v�j���O�ɖ߂�
	}*/

	count = (count + 1) % 90;//�J�E���^�[�𑝉�
}

//�`��
void Menu::Draw(){
	
	int image_num = image->GetEffectImage(7, 0); //�摜���擾

	int back = image->GetBackImage(0); //�w�i���擾
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y / 2, false, 0.0f, back); //�w�i��`��

	////Display::FixedDraw(320.f, 96.f, false, 0.f, logo); //���S��`��

	for (int i = 0; i < 4; i++)
	{
		Display::Draw(960.0f, 352.0f + (96.0f * i), false, 0.0f, choice[i].image, choice[i].ex_rate); //�I������`��
	}

	//DrawFormatString(128, 0, GetColor(255, 255, 255), "%d", sound->GetBgmVolume());
	//DrawFormatString(128, 32, GetColor(255, 255, 255), "%d", sound->GetSoundVolume());
	//DrawFormatString(160, 0, GetColor(255, 255, 255), "%d", setting->GetBgmVolume());
	//DrawFormatString(160, 32, GetColor(255, 255, 255), "%d", setting->GetSoundVolume());
	//int pad = key->GetPadOnce(); //������Ă���{�^�����擾
	//DrawFormatString(128, 128, GetColor(255, 255, 255), "%d", pad);
}