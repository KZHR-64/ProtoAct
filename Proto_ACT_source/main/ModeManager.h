#pragma once
#include "ModeBase.h"
#include "..\camera\Camera.h"
#include "..\system\EnvSetting.h"
#include "..\system\Fps.h"
#include "..\system\Image.h"
#include "..\system\Key.h"
#include "..\system\Sound.h"
#include <memory>
#include <stack>
#include <thread>

class ModeBase;
class Camera;
class EffectManager;
class DataSetting;
class Key;
class Sound;
class Image;
class Fps;

class ModeManager {
private:
	std::shared_ptr<EnvSetting> setting; //�ݒ�֘A
	std::shared_ptr<Key> key; //�L�[�֘A
	std::shared_ptr<Sound> sound; //���֘A
	std::shared_ptr<Image> image; //�摜�֘A
	std::shared_ptr<Fps> fps; //FPS�֘A
	std::shared_ptr<Camera> camera; //�J�����֘A

	std::vector<std::thread> load; //���[�h�̃X���b�h

	NextMode next; //���̉��
	bool blackout_flag; //�Ó]����
	int blackout_time; //�Ó]����
	bool erase; //���̃��[�h���I�����邩
	int stage_num; //�I�������X�e�[�W�ԍ�

	std::stack<std::shared_ptr<ModeBase>> scene_stack; //�V�[���̃X�^�b�N
	std::shared_ptr<ModeBase> scene_next; //���̃V�[��

	void Blackout(); //�Ó]
	
public:
	ModeManager(); //�R���X�g���N�^
	~ModeManager(); //�f�X�g���N�^
	void Setting(); //�����ݒ�
	int GetStageNum(); //�X�e�[�W�ԍ����擾
	void SetStageNum(int set_num); //�X�e�[�W�ԍ���ݒ�
	void ChangeMode(NextMode nmode, bool erase_now = false); //���̃��[�h�ɂ���(���݃��[�h���������邩)
	void Update(); //�X�V
	void Draw(); //�`��
};