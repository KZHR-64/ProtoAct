#pragma once
#include "../character/CharacterBase.h"
#include "EnemyManager.h"
#include "../Define.h"
#include "../player/Player.h"
//#include "../map/MapChipManager.h"
//#include "../map/AbstractMapChip.h"
//#include "../bullet/BulletManager.h"
//#include "../effect/EffectManager.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../tool/Display.h"
#include <memory>

class EnemyManager;
class Player;
class BulletManager;
class MapChipManager;
class EffectManager;
class AbstractMapChip;

class AbstractEnemy : public CharacterBase {
protected:
	EnemyManager* manager;

	std::vector<std::shared_ptr<AbstractEnemy>> parts; //�p�[�c�Ƃ��Ĉ����G
	AbstractEnemy* base_enemy; //�{��

	bool boss_flag; //�{�X�L������


public:
	AbstractEnemy(EnemyManager* man, int num, float ini_x, float ini_y); //�R���X�g���N�^(�摜�̔ԍ��A���W)
	~AbstractEnemy(); //�f�X�g���N�^

	AbstractEnemy* GetBase(); //�{�̂��擾
	void SetBase(AbstractEnemy* base); //�{�̂�ݒ�
	bool GetBossFlag(); //�{�X�����擾
	void SetBossFlag(int rank); //�{�X����ݒ�(�i)

	void AdjustPosition(std::shared_ptr<MapChipManager> map, std::shared_ptr<EffectManager> effect); //�ʒu�̒���
	void HitDamage(int damage_num, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //�_���[�W����(�_���[�W�l)
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //�e�ɓ������Ă��邩
	void HitCheckEnemy(float cx, float cy, float hit_size, std::shared_ptr<EffectManager> effect); //�G�ɓ������Ă��邩
	bool HitCheckChara(float cx, float cy, float hit_size, bool check_hit = true); //�L�����N�^�[�Ƃ̓����蔻��(�L������x,y���W�A�����蔻��̑傫���A�����蔻��̗L�����m�F���邩)
	void Timer(); //�^�C�}�[�֘A�̍X�V

	virtual void Defeat(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) = 0; //���ꂽ���̓���
	virtual void Update(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera) = 0; //�X�V
};