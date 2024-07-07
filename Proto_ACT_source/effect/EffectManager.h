#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "AbstractEffect.h"
#include "../camera/Camera.h"
#include <map>
#include <list>
#include <queue>
#include <memory>

class AbstractEffect;
class Camera;

struct EffectDataStruct
{
	//�G�t�F�N�g���̍\����
	int type; //���
	int image; //�\������摜
};

class EffectManager {
private:
	std::map<int, EffectDataStruct> effect_data; //�G�t�F�N�g���
	std::list<std::shared_ptr<AbstractEffect>> effect; //�G�t�F�N�g
	
	void SetData(); //�G�t�F�N�g���̐ݒ�

public:
	EffectManager(); //�R���X�g���N�^
	~EffectManager(); //�f�X�g���N�^
	void Reset(); //������
	std::shared_ptr<AbstractEffect> SetEffect(int num, float ini_x, float ini_y, float ini_rate = 1.0f); //�G�t�F�N�g�̔z�u(�f�[�^�̔ԍ��A�摜�̔ԍ��A���W�A�\���{��)

	void Update(std::shared_ptr<Sound> sound); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //�`��
};