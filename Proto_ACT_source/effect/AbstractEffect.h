#pragma once
#include "../character/CharacterBase.h"
#include "EffectManager.h"
#include "../Define.h"
#include <memory>

class EffectManager;

class AbstractEffect : public CharacterBase{
protected:
	EffectManager* manager;

public:
	AbstractEffect(EffectManager* man, int num, float ini_x, float ini_y); //�R���X�g���N�^(�摜�̔ԍ��A���W)
	~AbstractEffect(); //�f�X�g���N�^

	virtual void Update(std::shared_ptr<Sound> sound) = 0;
};