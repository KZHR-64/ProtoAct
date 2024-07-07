#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"

//�l�ԑ�C�i��]�j

class SpinMassDriver : public AbstractMapChip {
protected:
	bool loaded; //���@�������Ă��邩
	int fire_time; //�����Ă���̎���
public:
	SpinMassDriver(MapChipManager* man, int num); //�R���X�g���N�^(�ԍ�)
	~SpinMassDriver(); //�f�X�g���N�^
	void AbsUpdate(); //�K���s���X�V
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //�`��
};
