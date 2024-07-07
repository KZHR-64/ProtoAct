#pragma once
#include "ModeBase.h"
#include "..\effect\EffectManager.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

class Opening : public ModeBase {
private:

	int logo; //���S�̃n���h��
	int pal; //���S�̓����x
	int time; //�^�C�}�[

public:
	Opening(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~Opening(); //�f�X�g���N�^
	void Load(); //���O�̃��[�h
	void Update(); //�X�V
	void Draw(); //�`��
};