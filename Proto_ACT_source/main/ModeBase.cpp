#pragma once
#include "ModeBase.h"

using namespace std;

ModeBase::ModeBase(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, std::shared_ptr<Camera> cam) {

	modemanager = modeman;//�V�[���ڍs�}�l�[�W��
	setting = set; //�ݒ�֘A
	key = k; //�L�[�֘A
	sound = sou; //���֘A
	image = img; //�摜�֘A
	fps = f; //FPS�֘A
	camera = cam; //�J�����֘A

	loaded = false; //���[�h�����t���O��false��
	start_flag = true; //�ؑ֒���t���O��true��

}

ModeBase::~ModeBase() {
	key.reset(); //���������
	sound.reset(); //���������
	image.reset(); //���������
	fps.reset(); //���������
	camera.reset(); //���������
}

//���[�h�������������Ԃ�
bool ModeBase::GetLoaded() {
	return loaded;
}