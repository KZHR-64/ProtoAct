#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"

//��s�G���i�N�[�w�C�j�����Ȃ�

class Kurhei1 : public AbstractEnemy {
protected:
	int hundle_num; //�\������摜
public:
	Kurhei1(EnemyManager* ene, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~Kurhei1(); //�f�X�g���N�^
	void AbsUpdate() override; //�K���s���X�V
	void Defeat(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) override; //���ꂽ���̓���
	void Update(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //�`��
};
