#pragma once
#include "DxLib.h"
#include "Option.h"

using namespace std;

Option::Option(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {
	Reset();

	cursor_pos = 0; //cursor�̈ʒu��������
	count = 0; //�J�E���^�[��������
}

Option::~Option() {
	
}

//������
void Option::Reset() {
	
}

//���O�̃��[�h
void Option::Load() {
	if (loaded) return; //���[�h�ς݂Ȃ�I��

	sound->LoadBgm(1); //�Ȃ����[�h
	image->LoadBackImage(1); //�w�i�����[�h

	data_set.fps_flag = setting->GetFpsFlag(); //FPS�\���̐ݒ���擾
	data_set.volume_bgm = setting->GetBgmVolume(); //BGM�̉��ʂ��擾
	data_set.volume_effect = setting->GetSoundVolume(); //���ʉ��̉��ʂ��擾

	//�摜��ݒ�
	on_hundle = image->GetEffectImage(3, 1);
	off_hundle = image->GetEffectImage(3, 0);
	graduation_hundle = image->GetEffectImage(5, 0);

	loaded = true; //���[�h�����t���O��true��
}

//�ݒ�̕ۑ�
void Option::SaveSetting() {
	setting->SetFpsFlag(data_set.fps_flag); //FPS�\���̐ݒ���擾
	setting->SetBgmVolume(data_set.volume_bgm); //BGM�̉��ʂ��擾
	setting->SetSoundVolume(data_set.volume_effect); //���ʉ��̉��ʂ��擾

	setting->SaveSetting();
}

//�X�V
void Option::Update(){
	//�ؑփt���O��true�̏ꍇ
	if (start_flag) {
		sound->PlayBgm(1); //�Ȃ��Đ�
		start_flag = false; //�ؑփt���O��false��
	}

	//��L�[��������Ă�����
	if (key->KeyCheckOnce(Up)){
		sound->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos = (cursor_pos - 1); //�J�[�\������Ɉړ�
	}

	//���L�[��������Ă�����
	if (key->KeyCheckOnce(Down)){
		sound->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos = (cursor_pos + 1); //�J�[�\�������Ɉړ�
	}

	if (cursor_pos < 0) cursor_pos = 0;
	if (2 < cursor_pos) cursor_pos = 2;

	//���E�̓��͏����擾
	bool left = key->KeyCheck(Left);
	bool right = key->KeyCheck(Right);

	if (left || right){
		count++; //�J�E���^�[�𑝉�
        //�J�E���g��1��4�̔{���̏ꍇ
		if (count == 1 || (count % 4 == 0 && 30 < count)) {
			//�J�[�\���ʒu�ŏ���������
			switch (cursor_pos)
			{
			case 0:
				//fps�\��
				data_set.fps_flag = !data_set.fps_flag;
				fps->SetDrawFlag(data_set.fps_flag);
				break;
			case 1:
				//BGM����
				if (left) {
					data_set.volume_bgm--;
				}
				else if (right) {
					data_set.volume_bgm++;
				}
				//���ʂ𒲐�
				if (data_set.volume_bgm < 0) {
					data_set.volume_bgm = 0;
				}
				if (VOLUME_MAX < data_set.volume_bgm) {
					data_set.volume_bgm = VOLUME_MAX;
				}
				sound->SetBgmVolume(data_set.volume_bgm); //���ʂ�ݒ�
				break;
			case 2:
				//���ʉ�����
				if (left) {
					data_set.volume_effect--;
				}
				else if (right) {
					data_set.volume_effect++;
				}
				//���ʂ𒲐�
				if (data_set.volume_effect < 0) {
					data_set.volume_effect = 0;
				}
				if (VOLUME_MAX < data_set.volume_effect) {
					data_set.volume_effect = VOLUME_MAX;
				}
				sound->SetSoundVolume(data_set.volume_effect); //���ʂ�ݒ�
				break;
			default:
				break;
			}
			sound->PlaySoundEffect(0); //���ʉ���炷
		}
	}
	else {
		count = 0; //�J�E���^�[��������
	}

	//����L�[��������Ă�����
	if (key->KeyCheckOnce(Jump)){
		sound->PlaySoundEffect(1); //���ʉ���炷

		SaveSetting(); //�ݒ��ۑ�����
		start_flag = true; //�A�҃t���O�𗧂Ă�

		modemanager->ChangeMode(Next_Back, false); //���j���[�ɖ߂�
	}
}

//�`��
void Option::Draw(){
	int back = image->GetBackImage(1); //�w�i���擾
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y / 2, false, 0.0f, back); //�w�i��`��

	int blend_mode; //�\�����@
	int blend; //�����̖��邳

	//FPS
	//�I���ɂ���ĕ����̖��邳��ύX
	blend_mode = (data_set.fps_flag ? DX_BLENDMODE_SUB : DX_BLENDMODE_NOBLEND);
	blend = (data_set.fps_flag ? 96 : 1);
	Display::Draw(672.0f, 192.0f, false, 0.0f, off_hundle, 1.0f, blend_mode, blend); //�I������`��
	blend_mode = (data_set.fps_flag ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_SUB);
	blend = (data_set.fps_flag ? 1 : 96);
	Display::Draw(960.0f, 192.0f, false, 0.0f, on_hundle, 1.0f, blend_mode, blend);

	//����
	for (int i = 0; i < data_set.volume_bgm; i++)
	{
		Display::Draw(420.0f + (8.0f * i), 314.0f, false, 0.0f, graduation_hundle);
	}

	for (int i = 0; i < data_set.volume_effect; i++)
	{
		Display::Draw(420.0f + (8.0f * i), 436.0f, false, 0.0f, graduation_hundle);
	}

	//�I�������ʒu�ȊO�͏����Â�����
	for (int i = 0; i < 3; i++)
	{
		if (i == cursor_pos) continue;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 131 + (122 * i), WINDOW_X, 253 + (122 * i), GetColor(128, 128, 128), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}