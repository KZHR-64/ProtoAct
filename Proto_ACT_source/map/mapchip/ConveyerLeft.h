#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//�x���g�R���x�A�i���j

class ConveyerLeft : public AbstractMapChip{
protected:

public:
	ConveyerLeft(MapChipManager* man, int num); //�R���X�g���N�^(�ԍ�)
	~ConveyerLeft(); //�f�X�g���N�^
	void AbsUpdate(); //�K���s���X�V
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw() override; //�`��
};
