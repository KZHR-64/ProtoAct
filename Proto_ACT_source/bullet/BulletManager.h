#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "AbstractBullet.h"
#include "../main/Parameter.h"
#include "../player/Player.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
#include "../item/ItemManager.h"
#include "../camera/Camera.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../system/Sound.h"
#include "../tool/Display.h"
#include <map>
#include <list>
#include <vector>
#include <memory>

class AbstractBullet;
class Player;
class EnemyManager;
class MapChipManager;
class EffectManager;
class ItemManager;
class Camera;

struct BulletDataStruct
{
	//�e���̍\����
	int type; //���
	int image; //�\������摜
	bool breakable; //�󂹂邩
	bool hit_player; //���@�ɓ����邩
	bool hit_enemy; //�G�ɓ����邩
	bool hit_map; //�}�b�v�`�b�v�ɓ����邩
	int damage; //�_���[�W�l
	int break_power; //�}�b�v�`�b�v���󂷗�
};

class BulletManager {
private:
	std::map<int, BulletDataStruct> bullet_data; //�e���
	std::list<std::shared_ptr<AbstractBullet>> bullet; //�e

	void SetData(); //�e���̐ݒ�
	void EraseCheck(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�����邩�m�F

public:
	BulletManager(); //�R���X�g���N�^
	~BulletManager(); //�f�X�g���N�^
	void Reset(); //������
	std::shared_ptr<AbstractBullet> SetBullet(int num, float ini_x, float ini_y, float speed, float angle); //�e�̔z�u(�f�[�^�̔ԍ��A���W�A���x�A�p�x)
	void HitCheckMap(std::shared_ptr<MapChipManager> map); //�}�b�v�`�b�v�Ƃ̓����蔻��
	int HitCheckChara(float cx, float cy, float hit_size, bool check_player, bool check_enemy); //�L�����N�^�[�Ƃ̓����蔻��(�L������x,y���W�A�����蔻��̑傫���A���@�ɓ����邩�G�ɓ����邩)
	
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<ItemManager> item, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //�`��
};