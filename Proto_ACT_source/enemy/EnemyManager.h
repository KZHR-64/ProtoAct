#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "AbstractEnemy.h"
#include "../player/Player.h"
#include "../map/MapChipManager.h"
#include "../effect/EffectManager.h"
#include "../camera/Camera.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../system/Sound.h"
#include "../tool/Display.h"
#include <map>
#include <list>
#include <vector>
#include <memory>

class Player;
class AbstractEnemy;
class MapChipManager;
class EffectManager;
class Camera;

struct EnemyDataStruct
{
	//�G���̍\����
	int type; //���
	int image; //�\������摜
	int hp; //HP
	int size_x; //���̑傫��
	int size_y; //�c�̑傫��
	int rank; //�i(0=�G���A1=���{�X�A2�ȏ�=�{�X)
};

struct StandbyEnemyDataStruct
{
	//�}�b�v�ɔz�u����G�̍\����
	bool flag; //�o��������
	int num; //���
	float x; //���W
	float y;
};

class EnemyManager {
private:
	std::map<int, EnemyDataStruct> enemy_data; //�G���
	std::list<std::shared_ptr<AbstractEnemy>> enemy; //�G
	std::vector<StandbyEnemyDataStruct> standby_enemy; //�}�b�v�ɔz�u����G

	bool boss_battle; //�{�X����s���Ă��邩
	bool boss_flag; //�{�X���o�Ă��邩
	bool midboss_flag; //���{�X���o�Ă��邩

	void SetData(); //�G���̐ݒ�

public:
	EnemyManager(); //�R���X�g���N�^
	~EnemyManager(); //�f�X�g���N�^
	void Reset(); //������
	void EraseCheck(std::shared_ptr<Camera> camera); //�����邩�m�F
	void SetStandby(std::string file_name); //�G���}�b�v�ɔz�u
	std::shared_ptr<AbstractEnemy> SetEnemy(int num, float ini_x, float ini_y, AbstractEnemy* base = NULL); //�G�̔z�u(�f�[�^�̔ԍ��A���W�A�{��)
	void SpawnCheck(std::shared_ptr<Camera> camera); //�G���o���ł��邩�m�F
	bool HitCheckChara(float cx, float cy, float hit_size, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, int damage = 0); //�L�����N�^�[�Ƃ̓����蔻��(�L������x,y���W�Ax,y�����̑傫���A�_���[�W)
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //�e�ɓ������Ă��邩
	void HitCheckEnemy(std::shared_ptr<EffectManager> effect); //�G�ɓ������Ă��邩
	bool GetBossFlag(); //�{�X�풆���擾
	bool GetBeatBoss(); //�{�X��|�������擾
	
	void Update(std::shared_ptr<MapChipManager> map, std::shared_ptr<BulletManager> bullet, std::shared_ptr<Player> player, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //�`��
};