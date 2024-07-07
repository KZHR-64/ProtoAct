#pragma once
#include "../AbstractBullet.h"
#include "../Define.h"

//���P�b�g�n���h

class RocketHand : public AbstractBullet {
protected:
	std::shared_ptr<AbstractItem> catch_item; //���񂾃A�C�e��
public:
	RocketHand(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //�R���X�g���N�^(�摜�̔ԍ��A���W�A���x�A�p�x)
	~RocketHand(); //�f�X�g���N�^
	void AbsUpdate(); //�K���s���X�V
	void Erase(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //�����鎞�̓���
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<ItemManager> item, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //�`��
};
