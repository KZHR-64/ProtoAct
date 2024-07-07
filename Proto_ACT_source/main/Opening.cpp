#pragma once
#include "DxLib.h"
#include "Opening.h"

using namespace std;

Opening::Opening(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {
	logo = image->GetEffectImage(6, 0);

	time = 0;
	pal = 0;
}

Opening::~Opening() {

}

//���O�̃��[�h
void Opening::Load() {
	if (loaded) return; //���[�h�ς݂Ȃ�I��

	loaded = true; //���[�h�����t���O��true��
}

//�X�V
void Opening::Update(){
	//�ؑփt���O��true�̏ꍇ
	if (start_flag) {
		time = 0; //�^�C�}�[��������
		start_flag = false; //�A�҃t���O��false��
	}
	
	if (time == 18) {
		sound->PlaySoundEffect(4); //���ʉ���炷

	}

	if (pal < 255) {
		pal += 5;
	}

	if (180 <= time) {
		start_flag = true; //�A�҃t���O�𗧂�
		modemanager->ChangeMode(Next_Menu, true); //���[�h�����j���[�ɕύX
	}
	
	time++;
}

//�`��
void Opening::Draw(){
	DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(255, 255, 255), true);

	////Display::Draw(520.f, 260.f, false, 0.f, logo, 1.0f, DX_BLENDMODE_ALPHA, pal);
}