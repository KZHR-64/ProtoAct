#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "AbstractMapChip.h"
#include "../player/Player.h"
#include "../enemy/EnemyManager.h"
#include "../item/ItemManager.h"
#include "../event/EventManager.h"
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

class AbstractMapChip;
class WarpDoor;
class Player;
class EnemyManager;
class ItemManager;
class EventManager;
class Camera;

struct MapChipDataStruct
{
	//�}�b�v�`�b�v���̍\����
	int type; //���
	int image; //�\������摜
	int size_x; //���̑傫��
	int size_y; //�c�̑傫��
	bool through; //���蔲���邩
	int breakable; //�󂹂邩(0=�󂹂Ȃ��A1=�Ƃ��A2=�d��)
	bool hit_map; //���̃}�b�v�`�b�v�ɓ����邩
	bool flying; //�����Ă��邩
	float friction; //���C
	int link_x1; //�A������}�b�v�`�b�v1�i���j�i��̔ԍ����ǂꂾ���傫�����j
	int link_x2;//�A������}�b�v�`�b�v2�i���j
};

struct EventDataStruct
{
	//�C�x���g�z�u���̍\����
	bool flag; //�������邩
	int num; //�ԍ�
	float x; //x���W
	float y; //y���W
};

struct MapDataStruct
{
	//�}�b�v���̍\����
	std::string back_name; //BGM�Ɣw�i�ݒ�̃t�@�C����
	std::string mapfile_name; //�}�b�v�`�b�v�z�u�̃t�@�C����
	std::string mapfile_name2; //�}�b�v�`�b�v�z�u�̃t�@�C����(�����Ȃ�����)
	std::string scroll_name; //�X�N���[�����̃t�@�C����
	std::string enemy_name; //�G�z�u�̃t�@�C����
	std::string item_name; //�A�C�e���z�u�̃t�@�C����
	std::string warp_name; //���[�v���z�u�̃t�@�C����
	std::string warp_data_name; //���[�v���̃t�@�C����
	std::string event_name; //�C�x���g�z�u�̃t�@�C����
	std::string event_data_name; //�C�x���g���̃t�@�C����
};

struct BackStruct
{
	//�w�i�̍\����
	int image; //�摜
	float x; //���W(��������Ƃ���)
	float y;
	float sx; //�X�N���[�����鑬�x(�{��)
	float sy;
	bool loop; //���[�v���邩
};

struct WarpDataStruct
{
	//���[�v���̍\����
	int next_num; //���̃}�b�v�ԍ�
	int image; //�\������摜
	int size_x; //���̑傫��
	int size_y; //�c�̑傫��
	float next_x; //���̍��W
	float next_y;
	bool check_key; //�L�[�̓��͂��m�F���邩
};

struct WarpStruct
{
	//���[�v���̍\����
	int num; //�Q�Ƃ�����
	float x; //���W
	float y;
};

class MapChipManager{
private:
	std::list<std::shared_ptr<AbstractMapChip>> mapchip; //�}�b�v�`�b�v
	std::vector<EventDataStruct> standby_event; //�C�x���g
	std::vector<std::string> stage_data; //�X�e�[�W���
	std::vector<MapDataStruct> map_data; //�}�b�v���
	std::map<int, MapChipDataStruct> mapchip_data; //�}�b�v�`�b�v���
	std::vector<BackStruct> back_data; //�w�i
	std::vector<WarpDataStruct> warp_data; //���[�v���
	std::vector<WarpStruct> warp_door; //���[�v��

	void SetData(); //�}�b�v�`�b�v���̐ݒ�
	void SetStageData(); //�X�e�[�W���̐ݒ�
	void SetMapData(std::string file_name); //�}�b�v���̐ݒ�
	void SetBackData(std::shared_ptr<Image> image); //BGM�Ɣw�i���̐ݒ�
	void SetWarpData(); //���[�v���̐ݒ�
	void MakeMapChip(); //�}�b�v�`�b�v�̔z�u
	void MakeMapFront(); //�}�b�v�`�b�v�̔z�u(�����Ȃ�����)
	void MakeMapScroll(std::shared_ptr<Camera> camera); //�X�N���[���͈͂̐ݒ�
	void MakeMapEvent(); //�C�x���g�J�n�ʒu�̐ݒ�
	void MakeWarpDoor(); //���[�v���̐ݒ�
	void WindowCheck(std::shared_ptr<AbstractMapChip>, std::shared_ptr<Camera> camera); //��ʓ��Ɏ��܂��Ă��邩�m�F
	void BackUpdate(std::shared_ptr<Image> image); //�w�i�̍X�V
	void BackDraw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //�w�i�̕`��


	int stage_num; //�X�e�[�W�ԍ�
	int next_map; //���̃}�b�v
	int warp_num; //�g�p���郏�[�v��
	bool warp_flag; //���[�v���邩
	int bgm; //�Đ�����BGM
	float gravity; //�d��

public:
	MapChipManager(int set_num); //�R���X�g���N�^
	~MapChipManager(); //�f�X�g���N�^
	void Reset(); //������
	void MakeMap(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<ItemManager> item, std::shared_ptr<EventManager> event, std::shared_ptr<Image> image, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�}�b�v�̐���(���@�A�G�A�A�C�e���A�C�x���g�̃N���X)
	std::shared_ptr<AbstractMapChip> SetMapChip(int num, float ini_x, float ini_y, bool hit_map = true); //�}�b�v�`�b�v�̔z�u(�f�[�^�̔ԍ��A���W�A���}�b�v�`�b�v�Ƃ̓����蔻��)
	bool HitCheck(float cx, float cy, float hit_size, int break_power, bool abs_check = false); //�L�������}�b�v�`�b�v�ɓ������Ă��邩(�L������x,y���W�A�����蔻��̑傫���A�󂷑��̋����A�����蔻��ɂ�����炸�m�F���邩)
	std::shared_ptr<AbstractMapChip> HitCheckLeft(float cx, float cy, float hit_size); //�L�������}�b�v�`�b�v�ɓ������Ă��邩(���̔���)(�L������x,y���W�A�����蔻��̑傫��)
	std::shared_ptr<AbstractMapChip> HitCheckRight(float cx, float cy, float hit_size); //�L�������}�b�v�`�b�v�ɓ������Ă��邩(�E�̔���)(�L������x,y���W�A�����蔻��̑傫��)
	std::shared_ptr<AbstractMapChip> HitCheckTop(float cx, float cy, float hit_size); //�L�������}�b�v�`�b�v�ɓ������Ă��邩(��̔���)(�L������x,y���W�A�����蔻��̑傫��)
	std::shared_ptr<AbstractMapChip> HitCheckBottom(float cx, float cy, float hit_size); //�L�������}�b�v�`�b�v�ɓ������Ă��邩(���̔���)(�L������x,y���W�A�����蔻��̑傫��)
	void CheckStep(float cx, float cy, float hit_size); //�L�������}�b�v�`�b�v�ɏ���Ă��邩(�L������x,y���W�A�����蔻��̑傫��)
	float GetPlusSpeedX(float cx, float cy, float hit_size); //�}�b�v�`�b�v�ɏ���Ă���L�����ɑ������x���擾(�L������x,y���W�A�����蔻��̑傫��)
	float GetPlusSpeedY(float cx, float cy, float hit_size); //�}�b�v�`�b�v�ɏ���Ă���L�����ɑ������x���擾(�L������x,y���W�A�����蔻��̑傫��)
	void EventHitCheck(std::shared_ptr<EventManager> event, float cx, float cy); //�L�������C�x���g�����ʒu�ɓ������Ă��邩(�L������x,y���W)
	void WarpHitCheck(std::shared_ptr<EventManager> event, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound, float cx, float cy); //�L���������[�v���ɓ������Ă��邩(�L������x,y���W)
	bool GetWarpFlag(); //���[�v���邩�擾
	std::shared_ptr<AbstractMapChip> HitCheckLeftMap(std::shared_ptr<AbstractMapChip> check_map); //�}�b�v�`�b�v�����̃}�b�v�`�b�v�ɓ������Ă��邩(���̔���)
	std::shared_ptr<AbstractMapChip> HitCheckRightMap(std::shared_ptr<AbstractMapChip> check_map); //�}�b�v�`�b�v�����̃}�b�v�`�b�v�ɓ������Ă��邩(�E�̔���)
	std::shared_ptr<AbstractMapChip> HitCheckTopMap(std::shared_ptr<AbstractMapChip> check_map); //�}�b�v�`�b�v�����̃}�b�v�`�b�v�ɓ������Ă��邩(��̔���)
	std::shared_ptr<AbstractMapChip> HitCheckBottomMap(std::shared_ptr<AbstractMapChip> check_map, bool plus_one = false); //�}�b�v�`�b�v�����̃}�b�v�`�b�v�ɓ������Ă��邩(���̔���A1�h�b�g�����݂邩)
	void AdjustPosition(); //�ʒu�̒���

	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Image> image, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //�`��
};