#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"

//������u���b�N

class PushBlock : public AbstractMapChip {
protected:
	bool pushed_flag; //�����ꂽ��
	float next_x; //�ړI��x���W
	float base_sx; //��ƂȂ鑬�x
public:
	PushBlock(MapChipManager* man, int num); //�R���X�g���N�^(�ԍ�)
	~PushBlock(); //�f�X�g���N�^
	void AbsUpdate(); //�K���s���X�V
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //�`��
};
