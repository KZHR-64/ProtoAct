#pragma once
#include "../character/CharacterBase.h"
#include "ItemManager.h"
#include "../Define.h"
#include "../player/Player.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../tool/Display.h"
#include <vector>
#include <memory>

class ItemManager;
class BulletManager;
class Player;
class EnemyManager;
class MapChipManager;
class EffectManager;
class AbstractMapChip;

class AbstractItem : public CharacterBase{
protected:
	ItemManager* manager;

	bool hit_player; //���@�ɓ����邩
	bool hit_enemy; //�G�ɓ����邩
	bool hit_map; //�}�b�v�`�b�v�ɓ����邩

public:
	AbstractItem(ItemManager* man, int num, float ini_x, float ini_y); //�R���X�g���N�^(�摜�̔ԍ��A���W)
	~AbstractItem(); //�f�X�g���N�^

	bool GetHitPlayer(); //���@�ɓ����邩���擾
	void SetHitPlayer(bool flag); //���@�ɓ����邩��ݒ�
	bool GetHitEnemy(); //�G�ɓ����邩���擾
	void SetHitEnemy(bool flag); //�G�ɓ����邩��ݒ�
	bool GetHitMap(); //�}�b�v�`�b�v�ɓ����邩���擾
	void SetHitMap(bool flag); //�}�b�v�`�b�v�ɓ����邩��ݒ�

	bool HitCheckPlayer(std::shared_ptr<Player> player); //�v���C���[�Ƃ̓����蔻��
	void HitCheckMap(std::shared_ptr<MapChipManager> map); //�}�b�v�`�b�v�Ƃ̓����蔻��
	bool HitCheckChara(float cx, float cy, float hit_size); //�L�����N�^�[�Ƃ̓����蔻��(�L������x,y���W�A�����蔻��̑傫��)

	virtual void ItemGet(std::shared_ptr<Player> player, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) = 0; //�A�C�e���擾���̏���
	virtual void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) = 0;
};