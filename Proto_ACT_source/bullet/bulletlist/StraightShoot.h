#pragma once
#include "../AbstractBullet.h"
#include "../Define.h"

//���i�e

class StraightShoot : public AbstractBullet{
protected:

public:
	StraightShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //�R���X�g���N�^(�摜�̔ԍ��A���W�A���x�A�p�x)
	~StraightShoot(); //�f�X�g���N�^
	void AbsUpdate(); //�K���s���X�V
	void Erase(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //�����鎞�̓���
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<ItemManager> item, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //�`��
};
