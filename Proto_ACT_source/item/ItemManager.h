#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "AbstractItem.h"
#include "../main/Parameter.h"
#include "../player/Player.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
#include "../camera/Camera.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../system/Sound.h"
#include "../tool/Display.h"
#include <map>
#include <list>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class AbstractItem;
class Player;
class EnemyManager;
class MapChipManager;
class EffectManager;
class Camera;

struct ItemDataStruct
{
	//�A�C�e�����̍\����
	int type; //���
	int image; //�\������摜
	bool hit_player; //���@�ɓ����邩
	bool hit_enemy; //�G�ɓ����邩
	bool hit_map; //�}�b�v�`�b�v�ɓ����邩
};

class ItemManager {
private:
	std::map<int, ItemDataStruct> item_data; //�A�C�e�����
	std::list<std::shared_ptr<AbstractItem>> item; //�A�C�e��

	void SetData(); //�A�C�e�����̐ݒ�
	void EraseCheck(); //�����邩�m�F

public:
	ItemManager(); //�R���X�g���N�^
	~ItemManager(); //�f�X�g���N�^
	void Reset(); //������
	void SetStandby(std::string file_name); //�A�C�e�����}�b�v�ɔz�u
	std::shared_ptr<AbstractItem> SetItem(int num, float ini_x, float ini_y); //�A�C�e���̔z�u(�f�[�^�̔ԍ��A���W)
	void HitCheckMap(std::shared_ptr<MapChipManager> map); //�}�b�v�`�b�v�Ƃ̓����蔻��
	void HitCheckPlayer(std::shared_ptr<Player> player, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //�v���C���[�Ƃ̓����蔻��(�L������x,y���W�A�����蔻��̑傫���A���@�ɓ����邩�G�ɓ����邩)
	std::shared_ptr<AbstractItem> HitCheckChara(float cx, float cy, float hit_size); //�L�����N�^�[�Ƃ̓����蔻��(�L������x,y���W�A�����蔻��̑傫��)

	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //�`��
};