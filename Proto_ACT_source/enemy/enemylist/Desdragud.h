#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"

//�{�X3�i�f�X�h���O�h�j

class Desdragud : public AbstractEnemy {
protected:
	bool move_flag; //�ړ����邩
	int pattern; //�U���p�^�[��
	float head_distance, head_angle, arm1_distance, arm1_angle, arm2_distance, arm2_angle, leg1_distance, leg1_angle, leg2_distance, leg2_angle;
	float arm1_spin_distance, arm1_spin_angle, arm2_spin_distance, arm2_spin_angle, leg1_spin_distance, leg1_spin_angle, leg2_spin_distance, leg2_spin_angle;
	float head_x, head_y, arm1_x, arm1_y, arm2_x, arm2_y, leg1_x, leg1_y, leg2_x, leg2_y;

	void Pattern1(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�U��1�i�o���A�ƃ~�T�C���j
	void Pattern2(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�U��2�i�~�T�C���Ǝ��@�_���j
	void Pattern3(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�U��3�i�ːi�j
public:
	Desdragud(EnemyManager* ene, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~Desdragud(); //�f�X�g���N�^
	void AbsUpdate() override; //�K���s���X�V
	void Defeat(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) override; //���ꂽ���̓���
	void Update(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //�`��
};
