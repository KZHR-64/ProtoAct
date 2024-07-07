#pragma once
#include "ModeBase.h"

struct SettingStruct{
	//�ݒ�̍\����
	bool fps_flag;		//FPS��\�����邩
	int volume_bgm;		//BGM�̉���
	int volume_effect;	//���ʉ��̉���
};

class Option : public ModeBase {
private:

	int cursor_pos; //�J�[�\���̈ʒu
	int count; //�L�[�������Ă���t���[����
	int on_hundle; //ON�̃n���h��
	int off_hundle; //OFF�̃n���h��
	int graduation_hundle; //���ʖڐ��̃n���h��

	SettingStruct data_set;
	
	void Reset(); //������
	void SaveSetting(); //�ݒ�̕ۑ�

public:
	Option(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~Option(); //�f�X�g���N�^
	void Load(); //���O�̃��[�h
	void Update(); //�X�V
	void Draw(); //�`��
};