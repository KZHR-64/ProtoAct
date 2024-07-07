#pragma once
#include "../character/CharacterBase.h"
#include "BulletManager.h"
#include "../Define.h"
#include "../player/Player.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
#include "../item/ItemManager.h"
#include "../item/AbstractItem.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../system/Sound.h"
#include "../tool/Display.h"
#include <vector>
#include <memory>

class BulletManager;
class Player;
class EnemyManager;
class MapChipManager;
class EffectManager;
class ItemManager;
class AbstractMapChip;
class AbstractItem;

class AbstractBullet : public CharacterBase {
protected:
	BulletManager* manager;

	int damage; //�_���[�W��
	float base_speed; //�n�߂ɐݒ肳�ꂽ���x
	bool breakable; //�󂹂邩
	bool hit_player; //���@�ɓ����邩
	bool hit_enemy; //�G�ɓ����邩
	bool hit_map; //�}�b�v�`�b�v�ɓ����邩
	int break_power; //�}�b�v�`�b�v���󂷗�


public:
	AbstractBullet(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //�R���X�g���N�^(�摜�̔ԍ��A���W�A���x�A�p�x)
	~AbstractBullet(); //�f�X�g���N�^

	int GetDamage(); //�_���[�W�l��Ԃ�
	void SetDamage(int set_damage); //�_���[�W�l��ݒ�(�_���[�W�l)
	bool GetBreakable(); //�󂹂邩���擾
	void SetBreakable(bool flag); //�󂹂邩��ݒ�
	bool GetHitPlayer(); //���@�ɓ����邩���擾
	void SetHitPlayer(bool flag); //���@�ɓ����邩��ݒ�
	bool GetHitEnemy(); //�G�ɓ����邩���擾
	void SetHitEnemy(bool flag); //�G�ɓ����邩��ݒ�
	bool GetHitMap(); //�}�b�v�`�b�v�ɓ����邩���擾
	void SetHitMap(bool flag); //�}�b�v�`�b�v�ɓ����邩��ݒ�
	int GetBreakPower(); //�}�b�v�`�b�v�̔j��͂�Ԃ�
	void SetBreakPower(int set_power); //�}�b�v�`�b�v�̔j��͂�ݒ�

	int HitCheckChara(float cx, float cy, float hit_size); //�L�����N�^�[�Ƃ̓����蔻��(�L������x,y���W�A�����蔻��̑傫��)
	void HitCheckMap(std::shared_ptr<MapChipManager> map); //�}�b�v�`�b�v�Ƃ̓����蔻��

	virtual void Erase(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) = 0; //�����鎞�̓���
	virtual void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<ItemManager> item, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera) = 0; //�X�V
};