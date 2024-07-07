#pragma once
#include "DxLib.h"
#include "Gameover.h"

using namespace std;

Gameover::Gameover(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {


	//�摜��ݒ�
	for (int i = 0; i < 2; i++)
	{
		select_hundle[i] = image->GetEffectImage(11, i);
	}

	cursor_pos = 0; //cursor�̈ʒu��������
}

//�f�X�g���N�^
Gameover::~Gameover() {
	
}

//������
void Gameover::Reset() {

}

//���O�̃��[�h
void Gameover::Load() {
	sound->LoadBgm(3); //�Ȃ����[�h
	image->LoadBackImage(4); //�w�i�����[�h

	loaded = true; //���[�h�����t���O��true��
}

//�X�V
void Gameover::Update(){
	//�ؑփt���O��true�̏ꍇ
	if (start_flag) {
		sound->PlayBgm(3); //�Ȃ��Đ�
		start_flag = false; //�ؑփt���O��false��
	}

	if (key->KeyCheckOnce(Down) || key->KeyCheckOnce(Up)){ //���L�[����L�[��������Ă�����
		sound->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos = (cursor_pos + 1) % 2; //�J�[�\�������Ɉړ�
	}
	if (key->KeyCheckOnce(Jump)){ //����L�[��������Ă�����
		sound->PlaySoundEffect(1); //���ʉ���炷
		//�J�[�\���̈ʒu�ɂ���đJ�ڐ��ύX
		switch (cursor_pos)
		{
		case 0:
			modemanager->ChangeMode(Next_Game, true); //���[�h���Q�[����ʂɕύX
			break;
		case 1:
			modemanager->ChangeMode(Next_Back); //���[�h���X�e�[�W�Z���N�g�ɕύX
			break;
		default:
			break;
		}
	}
}

//�`��
void Gameover::Draw(){
	int back = image->GetBackImage(4); //�w�i���擾
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y / 2, false, 0.0f, back); //�w�i��`��

	int blend_mode; //�\�����@
	int blend; //�����̖��邳

	//�I���ɂ���ĕ����̖��邳��ύX
	for (int i = 0; i < 2; i++)
	{
		blend_mode = ((cursor_pos == i) ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_SUB);
		blend = ((cursor_pos == i) ? 1 : 64);
		Display::Draw(960.0f, 352.0f + (96.0f * i), false, 0.0f, select_hundle[i], 1.0f, blend_mode, blend); //�I������`��
	}
}