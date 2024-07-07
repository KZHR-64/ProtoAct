#pragma once
#include "DxLib.h"
#include "ModeManager.h"
#include "Game.h"
#include "StageSelect.h"
#include "Option.h"
#include "KeyConfig.h"
#include "Opening.h"
#include "Menu.h"
#include "Gameover.h"

using namespace std;

ModeManager::ModeManager(){
	//image->LoadEffectImage();
	next = Next_None;
	erase = false;
	blackout_time = 0;
	blackout_flag = false; //�Ó]��Ԃ�������
	stage_num = 0; //�X�e�[�W��������

	setting = make_shared<EnvSetting>(); //�ݒ�֘A�̃|�C���^
	key = make_shared<Key>(); //�L�[�֘A�̃|�C���^
	sound = make_shared<Sound>(); //���֘A�̃|�C���^
	image = make_shared<Image>(); //�摜�֘A�̃|�C���^
	fps = make_shared<Fps>(); //FPS�֘A�̃|�C���^
	camera = make_shared<Camera>(); //�J�����֘A�̃|�C���^

	sound->SetBgmVolume(setting->GetBgmVolume()); //���ʂ�ݒ�
	sound->SetSoundVolume(setting->GetSoundVolume()); //���ʂ�ݒ�
	fps->SetDrawFlag(setting->GetFpsFlag()); //FPS�̕\����ݒ�

}

ModeManager::~ModeManager()
{
	//�X�^�b�N��S�J��
	while (!scene_stack.empty())
	{
		scene_stack.pop();
	}
}

//�X�e�[�W�ԍ����擾
int ModeManager::GetStageNum() {
	return stage_num;
}

//�X�e�[�W�ԍ���ݒ�
void ModeManager::SetStageNum(int set_num) {
	stage_num = set_num;
}

//�����ݒ�
void ModeManager::Setting() {
	sound->LoadSoundEffect(); //���ʉ������[�h
	image->LoadEffectImage();
	scene_stack.push(make_shared<Opening>(this, setting, key, sound, image, fps, camera)); //�n�߂̓I�[�v�j���O���
}

//�Ó]
void ModeManager::Blackout() {
	bool loaded = false; //���[�h������������

	blackout_time++; //�Ó]���Ԃ𑝉�

	//���̃��[�h������Ȃ�
	if (scene_next && !load.empty()) {
		loaded = scene_next->GetLoaded(); //���[�h�����t���O���擾
	}
	//�Ȃ��Ȃ�
	else {
		loaded = true;
	}

	//�Ó]���Ԃ����ɒB���A���[�h�����������ꍇ
	if (60 < blackout_time && loaded) {
		//���[�h������e������Ȃ�
		if (!load.empty()) {
			//�I��������Ƃ��m�F����
			for (auto& l : load) {
				l.join();
			}
		}
		load.clear(); //���[�h�̃X���b�h�����

		//���݂̃��[�h�������ꍇ
		if (erase) {
			scene_stack.pop();
		}
		//�O�̉�ʂɖ߂�ꍇ
		if (next == Next_Back) {
			scene_stack.pop(); //�X�^�b�N���|�b�v
		}
		else {
			scene_stack.push(scene_next); //���̃V�[�����X�^�b�N��
			scene_next.reset(); //���������
		}
		blackout_flag = false; //�Ó]�t���O��false��
	}
}

//���̃��[�h�ɂ���
void ModeManager::ChangeMode(NextMode nmode, bool erase_now){
	next = nmode; //���̏�ʂ�ݒ�
	blackout_flag = true; //�Ó]
	blackout_time = 0; //�Ó]���Ԃ�������
	erase = erase_now; //���̃��[�h��������
	
	//���Ɉڂ�
	switch (next) {
	case Next_Opening: //�I�[�v�j���O�̏ꍇ
		scene_next = make_shared<Opening>(this, setting, key, sound, image, fps, camera); //���̃��[�h��ݒ�
		load.emplace_back(&ModeBase::Load, scene_next.get()); //�X���b�h�Ƀ��[�h��ǉ�
		break;
	case Next_Menu: //���j���[��ʂ̏ꍇ
		scene_next = make_shared<Menu>(this, setting, key, sound, image, fps, camera); //���̃��[�h��ݒ�
		load.emplace_back(&ModeBase::Load, scene_next.get()); //�X���b�h�Ƀ��[�h��ǉ�
		break;
	case Next_StageSelect: //�X�e�[�W�Z���N�g��ʂ̏ꍇ
		scene_next = make_shared<StageSelect>(this, setting, key, sound, image, fps, camera); //���̃��[�h��ݒ�
		load.emplace_back(&ModeBase::Load, scene_next.get()); //�X���b�h�Ƀ��[�h��ǉ�
		break;
	case Next_Game: //�Q�[����ʂ̏ꍇ
		scene_next = make_shared<Game>(this, setting, key, sound, image, fps, camera); //���̃��[�h��ݒ�
		load.emplace_back(&ModeBase::Load, scene_next.get()); //�X���b�h�Ƀ��[�h��ǉ�
		break;
	case Next_Gameover: //�Q�[���I�[�o�[��ʂ̏ꍇ
		scene_next = make_shared<Gameover>(this, setting, key, sound, image, fps, camera); //���̃��[�h��ݒ�
		load.emplace_back(&ModeBase::Load, scene_next.get()); //�X���b�h�Ƀ��[�h��ǉ�
		break;
	case Next_Option: //�I�v�V������ʂ̏ꍇ
		scene_next = make_shared<Option>(this, setting, key, sound, image, fps, camera); //���̃��[�h��ݒ�
		load.emplace_back(&ModeBase::Load, scene_next.get()); //�X���b�h�Ƀ��[�h��ǉ�
		break;
	case Next_Config: //�L�[�R���t�B�O��ʂ̏ꍇ
		scene_next = make_shared<KeyConfig>(this, setting, key, sound, image, fps, camera); //���̃��[�h��ݒ�
		load.emplace_back(&ModeBase::Load, scene_next.get()); //�X���b�h�Ƀ��[�h��ǉ�
		break;
	case Next_Back: //�߂�ꍇ
		break;
	default:
		break;
	}
}

//�X�V
void ModeManager::Update(){
	key->Update(); //�L�[���X�V
	
	//�Ó]���̏ꍇ
	if (blackout_flag) {
		Blackout(); //�Ó]����
	}
	else {
		scene_stack.top()->Update();
	}
}

//�`��
void ModeManager::Draw(){
	scene_stack.top()->Draw();

	//�Ó]���̏ꍇ
	if (blackout_flag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (256 / 60) * blackout_time); //�`�惂�[�h�𔽉f

		DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true); //��ʂ��Â�����

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�`�惂�[�h��߂�
	}

	//DrawFormatString(0, 640, GetColor(0, 0, 255), "%d %d", load.size(), scene_stack.size());

	fps->Draw(); //���݂�FPS��`��
	fps->Wait();
}