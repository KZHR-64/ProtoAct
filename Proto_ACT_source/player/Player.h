#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../bullet/BulletManager.h"
#include "../enemy/EnemyManager.h"
#include "../effect/EffectManager.h"
#include "../camera/Camera.h"
#include <memory>

class MapChipManager;
class BulletManager;
class EnemyManager;
class EffectManager;
class AbstractMapChip;
class AbstractBullet;
class AbstractEnemy;
class AbstractEffect;
class AbstractItem;
class Camera;

typedef enum {
	//�L�����̓���
	Move_Stand, //�Î~
	Move_Walk, //���s
	Move_Jump, //�W�����v
	Move_Attack, //�U��
	Move_Dash //�_�b�V��
} MoveSet;

struct AttackStruct
{
	//�U���̍\����
	bool flag; //�U�����Ă��邩
	int time; //�U�����Ă��鎞��
	bool stop; //�U�����ɑ����~�߂邩
	int energy; //�U���G�l���M�[
	int res_time; //�G�l���M�[���񕜂���܂ł̎���
};

struct PlayerPartsStruct
{
	//�p�[�c�̍\����
	float x; //���W
	float y;
	float angle; //�p�x
	float total_angle; //�p�x�̍��v
	float def_angle; //�v�Z�p�̊p�x
	float def_distance; //�v�Z�p�̋���
	float spin_angle; //��]���̈ʒu�����߂�p�x
	float spin_point; //��]���̈ʒu
};

class Player : public CharacterBase{
private:
	void Control(std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //���@�̑���
	void DamageAction(); //�_���[�W����
	void Move(std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�ړ�
	void SetKeyRecord(std::shared_ptr<Key> key); //�L�[�̗������X�V
	bool RecordCheck(bool record[], int point = 0); //���͗����̊m�F(�n����A�T���n�߂�_)
	void HitUpdate(); //�����蔻��̍X�V
	void SetGraphic(); //�\������摜������
	void SetParts(); //�p�[�c�����낦��
	void Attack1(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�U��1
	void Attack2(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�U��2
	void Attack3(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�U��3
	void Attack4(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�U��4

	bool jumped; //�Ō�ɃW�����v�����Ƃ�����A�W�����v�{�^�����������ςȂ���
	bool through_flag; //���蔲���Ă��邩
	int move_type; //�s���Ă��铮��
	int move_time; //����̎���
	int weapon; //�g�p���镐��
	int handle; //�\������摜�̔ԍ�
	int inv_time; //���G����
	bool draw_flag; //�`�悷�邩
	bool move_flag; //����ł��邩
	int key_num; //�����Ă��錮�̐�
	int weapon_max; //�g�p�ł��镐��̐�
	const float move_speed = 8.0f; //��ƂȂ�ړ����x
	const int max_energy = 4; //�ő�G�l���M�[
	const int res_time = 30; //�G�l���M�[���񕜂���܂ł̎���

	AttackStruct attack;
	using func = void (Player::*)(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound);
	std::vector<func> attack_move;
	std::shared_ptr<AbstractBullet> player_bullet; //�������������e
	std::shared_ptr<AbstractEffect> catch_effect; //�r�[���p�̃G�t�F�N�g
	std::shared_ptr<AbstractMapChip> step_mapchip; //����Ă���}�b�v�`�b�v

	PlayerPartsStruct body, head, left_leg, right_leg, left_arm, right_arm; //�e�p�[�c
	
	bool commando[BUTTON][RECORD]; //���͂����L�[�̗���
	bool jump_book[RECORD]; //�W�����v�̎��O����

	int message_font; //�t�H���g���

public:
	Player(); //�R���X�g���N�^
	~Player(); //�f�X�g���N�^
	void Reset(); //������
	void AdjustPosition(std::shared_ptr<MapChipManager> map, bool event_flag); //�ʒu�̒���
	void AttackCheck(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�U��
	void HitCheckEnemy(std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //�G�ɓ������Ă��邩
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet, std::shared_ptr<Sound> sound); //�e�ɓ������Ă��邩
	bool HitCheckItem(float cx, float cy, float hit_size); //�A�C�e���ɓ������Ă��邩(�L������x,y���W�A�����蔻��̑傫��)
	void SetDrawFlag(bool flag); //�`�悷�邩�ݒ�
	void SetMoveFlag(bool flag); //����ł��邩�ݒ�
	int GetKeyNum(); //���̐����擾
	void SetKeyNum(int num); //���̐���ݒ�
	void SetWeaponMax(int num); //����̐���ݒ�
	void AbsUpdate(); //�K���s���X�V
	void Update(std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //�`��
};