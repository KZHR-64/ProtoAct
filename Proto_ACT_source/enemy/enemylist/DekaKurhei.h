#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"

//�{�X1�i�f�J�N�[�w�C�j

class DekaKurhei : public AbstractEnemy {
protected:
	int hundle_num; //�\������摜
	bool move_flag; //�ړ����邩
	int pattern; //�U���p�^�[��
	float parts1_distance, parts1_angle, parts2_distance, parts2_angle, parts3_distance, parts3_angle, parts4_distance, parts4_angle;
	float parts1_x, parts1_y, parts2_x, parts2_y, parts3_x, parts3_y, parts4_x, parts4_y;
	const int arm_num = 8; //�֐߂̐�

	std::vector<JointStruct> arm; //���֐߂̘r

	void Pattern1(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�U��1�i���ŋ@�֖C�j
	void Pattern2(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�U��2�i����ŋ@�֖C�j
	void Pattern3(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�U��3�i�����j
public:
	DekaKurhei(EnemyManager* ene, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~DekaKurhei(); //�f�X�g���N�^
	void AbsUpdate() override; //�K���s���X�V
	void Defeat(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) override; //���ꂽ���̓���
	void Update(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //�`��
};
