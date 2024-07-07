#pragma once
#include "ModeManager.h"
#include "..\tool\Display.h"
#include "..\tool\Calculation.h"
#include "..\camera\Camera.h"
#include "..\system\EnvSetting.h"
#include "..\system\Image.h"
#include "..\system\Key.h"
#include "..\system\Sound.h"
#include <memory>
#include <thread>
#include <vector>

class ModeManager;
class EffectManager;
class Camera;
class EnvSetting;
class Key;
class Sound;
class Image;

class ModeBase{
protected:
	ModeManager* modemanager; //�V�[���ؑւ�`����|�C���^
	std::shared_ptr<EnvSetting> setting; //�ݒ�֘A�̃|�C���^
	std::shared_ptr<Key> key; //�L�[�֘A�̃|�C���^
	std::shared_ptr<Sound> sound; //���֘A�̃|�C���^
	std::shared_ptr<Image> image; //�摜�֘A�̃|�C���^
	std::shared_ptr<Fps> fps; //FPS�֘A�̃|�C���^
	std::shared_ptr<Camera> camera; //�J�����֘A�̃|�C���^

	bool loaded; //���[�h������������
	bool start_flag; //�ؑ֒��ォ
public:
	ModeBase(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	virtual ~ModeBase();
	bool GetLoaded(); //���[�h�������������Ԃ�
	virtual void Load() = 0; //���O�̃��[�h
	virtual void Update() = 0; //�X�V
	virtual void Draw() = 0; //�`��
};