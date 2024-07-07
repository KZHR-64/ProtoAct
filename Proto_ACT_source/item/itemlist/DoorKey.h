#pragma once
#include "../AbstractItem.h"

//�h�A�̌�

class DoorKey : public AbstractItem {
protected:
	std::shared_ptr<AbstractEffect> mark; //�G�t�F�N�g
public:
	DoorKey(ItemManager* man, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ�)
	~DoorKey(); //�f�X�g���N�^
	void ItemGet(std::shared_ptr<Player> player, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //�A�C�e���擾���̏���
	void AbsUpdate(); //�K���s���X�V
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //�`��
};
