#pragma once
#include "DxLib.h"
#include "MapChipManager.h"
#include "./mapchip/NormalBlock.h"
#include "./mapchip/BombBlock.h"
#include "./mapchip/FuseBlock.h"
#include "./mapchip/PushBlock.h"
#include "./mapchip/LockedDoor.h"
#include "./mapchip/FallBlock.h"
#include "./mapchip/MassDriver.h"
#include "./mapchip/SpinMassDriver.h"
#include <math.h>

using namespace std;

MapChipManager::MapChipManager(int set_num){
	stage_num = set_num;
	next_map = 0;
	warp_num = 0;
	warp_flag = false;

	SetStageData();
	SetData();
	SetWarpData(); //���[�v����ݒ�
}

MapChipManager::~MapChipManager(){
	stage_data.clear();
	mapchip.clear();
	mapchip_data.clear();
	standby_event.clear();
	back_data.clear();
	warp_data.clear();
	warp_door.clear();
}

//�}�b�v�`�b�v���̐ݒ�
void MapChipManager::SetData() {

	int num;

	ifstream ifs("data/map/mapchip_data.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ',');
		mapchip_data[num].type = atoi(s.c_str()); //��ނ��擾
		getline(ss, s, ',');
		mapchip_data[num].image = atoi(s.c_str()); ////�摜�̔ԍ����擾
		getline(ss, s, ',');
		mapchip_data[num].size_x = atoi(s.c_str()); //���̑傫�����擾
		getline(ss, s, ',');
		mapchip_data[num].size_y = atoi(s.c_str()); //�c�̑傫�����擾
		getline(ss, s, ',');
		mapchip_data[num].through = (1 == atoi(s.c_str())); //���蔲���邩���擾
		getline(ss, s, ',');
		mapchip_data[num].breakable = atoi(s.c_str()); //�󂹂邩���擾
		getline(ss, s, ',');
		mapchip_data[num].hit_map = (1 == atoi(s.c_str())); //���̃}�b�v�`�b�v�ɓ����邩���擾
		getline(ss, s, ',');
		mapchip_data[num].flying = (1 == atoi(s.c_str())); //�����Ă��邩���擾
		getline(ss, s, ',');
		mapchip_data[num].friction = (float)atof(s.c_str()); //���C���擾
		getline(ss, s, ',');
		mapchip_data[num].link_x1 = atoi(s.c_str()); //�Ȃ���}�b�v�`�b�v���擾
		getline(ss, s, ',');
		mapchip_data[num].link_x2 = atoi(s.c_str()); //�Ȃ���}�b�v�`�b�v���擾
	}
	ifs.close();
}

//�X�e�[�W���̐ݒ�
void MapChipManager::SetStageData() {
	
	ifstream ifs("data/map/stage_data.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}
	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stage_data.emplace_back(str);
	}

	ifs.close();

	SetMapData(stage_data[stage_num]);
}

//�}�b�v���̐ݒ�
void MapChipManager::SetMapData(string file_name) {

	MapDataStruct new_map{};
	
	ifstream ifs(file_name);

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		new_map.mapfile_name = s; //�}�b�v���t�@�C�������擾
		getline(ss, s, ',');
		new_map.mapfile_name2 = s; //�}�b�v���t�@�C�������擾
		getline(ss, s, ',');
		new_map.scroll_name = s; //�X�N���[���͈̓t�@�C�������擾
		getline(ss, s, ',');
		new_map.back_name = s; //BGM&�w�i�t�@�C�������擾
		getline(ss, s, ',');
		new_map.enemy_name = s; //�G�z�u�t�@�C�������擾
		getline(ss, s, ',');
		new_map.item_name = s; //�A�C�e���z�u�t�@�C�������擾
		getline(ss, s, ',');
		new_map.warp_name = s; //���[�v�z�u�t�@�C�������擾
		getline(ss, s, ',');
		new_map.warp_data_name = s; //���[�v���t�@�C�������擾
		getline(ss, s, ',');
		new_map.event_name = s; //�C�x���g�z�u�t�@�C�������擾
		getline(ss, s, ',');
		new_map.event_data_name = s; //�C�x���g���t�@�C�������擾
		map_data.emplace_back(new_map);
	}

	ifs.close();
}

//BGM�Ɣw�i���̐ݒ�
void MapChipManager::SetBackData(shared_ptr<Image> image) {

	ifstream ifs(map_data[next_map].back_name);

	//�w�i������Ώ�����
	if (!back_data.empty()) {
		back_data.clear();
	}

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//BGM
	//�t�@�C�������s�ǂ�
	getline(ifs, str);
	bgm = atoi(str.c_str());

	//�w�i
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		BackStruct back{};
		stringstream ss{ str };
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		back.image = atoi(s.c_str()); //�摜�ԍ���ݒ�
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		back_data.push_back(back);

		image->LoadBackImage(back.image); //�w�i�����[�h
	}

	ifs.close();
}

//���[�v���̐ݒ�
void MapChipManager::SetWarpData() {

	//���[�v��񂪂���Ώ�����
	if (!warp_data.empty()) {
		warp_data.clear();
	}

	ifstream ifs(map_data[next_map].warp_data_name);

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	int num;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		WarpDataStruct warp{};
		stringstream ss{ str };
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		num = atoi(s.c_str()); //�ԍ���ݒ�
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		warp.image = atoi(s.c_str()); //�\������摜��ݒ�
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		warp.size_x = atoi(s.c_str()); //���̑傫����ݒ�
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		warp.size_y = atoi(s.c_str()); //�c�̑傫����ݒ�
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		warp.next_num = atoi(s.c_str()); //���̃}�b�v�ԍ���ݒ�
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		warp.next_x = (float)atof(s.c_str()); //x���W��ݒ�
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		warp.next_y = (float)atof(s.c_str()); //y���W��ݒ�
		warp_data.emplace_back(warp);
	}

	ifs.close();
}

//�}�b�v�̐���
void MapChipManager::MakeMap(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EventManager> event, shared_ptr<Image> image, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	int row = 0; //�s
	int col = 0; //��

	//���@�̈ʒu��ݒ�
	player->SetX(warp_data[warp_num].next_x);
	player->SetY(warp_data[warp_num].next_y);

	camera->SetScrollX(warp_data[warp_num].next_x); //�������̃X�N���[����������
	camera->SetScrollY(warp_data[warp_num].next_y); //�c�����̃X�N���[����������

	if(warp_flag) SetWarpData(); //���[�v�����Đݒ�

	//�}�b�v�`�b�v������Ώ�����
	if (!mapchip.empty()) {
		mapchip.clear();
	}

	MakeMapChip(); //�}�b�v�`�b�v�̔z�u
	MakeMapFront(); //�����Ȃ����̃}�b�v�`�b�v��z�u
	MakeMapScroll(camera); //�X�N���[���͈͂�ݒ�
	MakeMapEvent(); //�C�x���g��z�u
	SetBackData(image); //�w�i����ݒ�
	MakeWarpDoor(); //���[�v����z�u
	enemy->SetStandby(map_data[next_map].enemy_name); //�G��z�u
	item->SetStandby(map_data[next_map].item_name); //�A�C�e����z�u
	event->SetStandby(map_data[next_map].event_data_name); //�C�x���g����ݒ�

	warp_flag = false;
	warp_num = 0;

	sound->LoadBgm(bgm); //�Ȃ����[�h
	sound->PlayBgm(bgm); //�Ȃ��Đ�
}

//�}�b�v�`�b�v�̔z�u
void MapChipManager::MakeMapChip() {

	struct MapChipStruct
	{
		//�}�b�v�`�b�v�̍\����
		int type; //���
		bool flag; //�z�u������
	};

	vector<vector<MapChipStruct>> map_layout; //�}�b�v�`�b�v�̔z��

	ifstream ifs(map_data[next_map].mapfile_name);

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		vector<MapChipStruct> v;
		stringstream ss{ str };
		//�J���}��؂�ōs��ǂݍ���
		while (getline(ss, s, ',')) {
			MapChipStruct m = {-1, false};
			m.type = atoi(s.c_str()); //�ǂݍ��񂾐��l���i�[
			v.emplace_back(m);
		}
		map_layout.emplace_back(v);
	}

	ifs.close();

	//�}�b�v�`�b�v�̔z�u
	for (unsigned int i = 0; i < map_layout.size(); i++) {
		for (unsigned int j = 0; j < map_layout[i].size(); j++) {
			int num = map_layout[i][j].type;
			int size_x = mapchip_data[num].size_x; //�N�_�̑傫��
			unsigned int plus_j = 1;
			//�z�u���Ă��Ȃ��Ȃ�
			if (!map_layout[i][j].flag && num != -1) {
				//�Ȃ���}�b�v�`�b�v������Ȃ�
				//���̘A��
				if (mapchip_data[num].link_x1 != -1 || mapchip_data[num].link_x2 != -1) {
					//�͂ݏo���܂ŌJ��Ԃ�
					while (j + plus_j < map_layout[i].size()) {
						int num_j = map_layout[i][j + plus_j].type;
						//�Ȃ���}�b�v�`�b�v�łȂ���ΏI��
						if (num_j != mapchip_data[num].link_x1 + map_layout[i][j].type && num_j != mapchip_data[num].link_x2 + map_layout[i][j].type) {
							break;
						}
						size_x += mapchip_data[num_j].size_x; //�傫���𑝉�
						map_layout[i][j + plus_j].flag = true; //�z�u�������Ƃ�
						plus_j++;
					}
				}
				shared_ptr<AbstractMapChip> new_mapchip = SetMapChip(num, 32.0f * j + (4.0f * size_x), 32.0f * i); //�}�b�v�`�b�v��z�u
				new_mapchip->SetSizeX(size_x); //�傫����ݒ�
				new_mapchip->SetLinkX(plus_j); //�A������ݒ�
				new_mapchip->SetLinkImgX(mapchip_data[num].link_x1, mapchip_data[num].link_x2); //�A������摜��ݒ�
				map_layout[i][j].flag = true; //�z�u�������Ƃ�
				
			}
		}
	}
}

//�}�b�v�`�b�v�̔z�u(�����Ȃ�����)
void MapChipManager::MakeMapFront() {

	int row = 0; //�s
	int col = 0; //��

	ifstream ifs(map_data[next_map].mapfile_name2);

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		//�J���}��؂�ōs��ǂݍ���
		while (getline(ss, s, ',')) {

			//�ǂݍ��񂾐��l��-1�łȂ����
			int num = atoi(s.c_str());
			if (num != -1) {
				//�}�b�v�`�b�v��z�u
				SetMapChip(num, 32.0f * col + (4.0f * mapchip_data[num].size_x), 32.0f * row, false);
			}
			col++; //�񐔂𑝂₷
		}

		//�񐔂����Z�b�g���čs���𑝂₷
		col = 0;
		row++;
	}

	ifs.close();
}

//�X�N���[���͈͂̐ݒ�
void MapChipManager::MakeMapScroll(shared_ptr<Camera> camera) {

	int row = 0; //�s
	int col = 0; //��

	ifstream ifs(map_data[next_map].scroll_name);

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		//�J���}��؂�ōs��ǂݍ���
		while (getline(ss, s, ',')) {

			//�ǂݍ��񂾐��l�ɂ���ăX�N���[���͈͂�����
			switch (atoi(s.c_str()))
			{
			case 0:
				camera->SetScrollXMin(col * 32);
				camera->SetScrollYMin(row * 32);
				break;
			case 1:
				camera->SetScrollXMax((col + 1) * 32);
				camera->SetScrollYMax((row + 1) * 32);
				break;
			default:
				break;
			}
			col++; //�񐔂𑝂₷
		}

		//�񐔂����Z�b�g���čs���𑝂₷
		col = 0;
		row++;
	}

	ifs.close();
}

//�C�x���g�J�n�ʒu�̐ݒ�
void MapChipManager::MakeMapEvent() {

	int row = 0; //�s
	int col = 0; //��
	EventDataStruct new_event{};

	ifstream ifs(map_data[next_map].event_name);

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		//�J���}��؂�ōs��ǂݍ���
		while (getline(ss, s, ',')) {

			//�ǂݍ��񂾐��l��-1�łȂ����
			int num = atoi(s.c_str());
			if (num != -1) {
				//�C�x���g��z�u
				new_event.flag = true;
				new_event.num = num;
				new_event.x = 32.0f * col;
				new_event.y = 32.0f * row + 16.0f;
				standby_event.emplace_back(new_event);
			}
			col++; //�񐔂𑝂₷
		}

		//�񐔂����Z�b�g���čs���𑝂₷
		col = 0;
		row++;
	}

	ifs.close();
}

//���[�v���̐ݒ�
void MapChipManager::MakeWarpDoor() {
	int row = 0; //�s
	int col = 0; //��

	//���[�v��������Ώ�����
	if (!warp_door.empty()) {
		warp_door.clear();
	}

	ifstream ifs(map_data[next_map].warp_name);

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		//�J���}��؂�ōs��ǂݍ���
		while (getline(ss, s, ',')) {

			//�ǂݍ��񂾐��l��-1�łȂ����
			int num = atoi(s.c_str());
			if (num != -1) {
				//���[�v����z�u
				WarpStruct warp{};
				warp.num = num;
				warp.x = 32.0f * col + (4.0f * warp_data[warp.num].size_x);
				warp.y = 32.0f * row + 32.0f - (4.0f * warp_data[warp.num].size_y);
				warp_door.emplace_back(warp);
			}
			col++; //�񐔂𑝂₷
		}

		//�񐔂����Z�b�g���čs���𑝂₷
		col = 0;
		row++;
	}

	ifs.close();
}

//������
void MapChipManager::Reset(){
	
}

//�}�b�v�`�b�v�̔z�u
shared_ptr<AbstractMapChip> MapChipManager::SetMapChip(int num, float ini_x, float ini_y, bool hit_map) {
	shared_ptr<AbstractMapChip> new_mapchip;

	switch (mapchip_data[num].type)
	{
	case 0:
		new_mapchip = make_shared<NormalBlock>(this, mapchip_data[num].image);
		break;
	case 1:
		new_mapchip = make_shared<BombBlock>(this, mapchip_data[num].image);
		break;
		case 2:
		new_mapchip = make_shared<FuseBlock>(this, mapchip_data[num].image);
		break;
	case 3:
		new_mapchip = make_shared<PushBlock>(this, mapchip_data[num].image);
		break;
	case 4:
		new_mapchip = make_shared<LockedDoor>(this, mapchip_data[num].image);
		break;
	case 5:
		new_mapchip = make_shared<FallBlock>(this, mapchip_data[num].image);
		break;
	case 6:
		new_mapchip = make_shared<MassDriver>(this, mapchip_data[num].image);
		new_mapchip->SetAngle(0.0f);
		break;
	case 7:
		new_mapchip = make_shared<MassDriver>(this, mapchip_data[num].image);
		new_mapchip->SetAngle(PI);
		break;
	case 8:
		new_mapchip = make_shared<MassDriver>(this, mapchip_data[num].image);
		new_mapchip->SetAngle(1.5f * PI);
		break;
	case 9:
		new_mapchip = make_shared<MassDriver>(this, mapchip_data[num].image);
		new_mapchip->SetAngle(0.5f * PI);
		break;
	case 10:
		new_mapchip = make_shared<SpinMassDriver>(this, mapchip_data[num].image);
		break;
	default:
		new_mapchip = make_shared<NormalBlock>(this, mapchip_data[num].image);
		break;
	}

	new_mapchip->SetX(ini_x); //���W��ݒ�
	new_mapchip->SetY(ini_y);
	new_mapchip->SetBaseX(ini_x); //��̍��W��ݒ�
	new_mapchip->SetBaseY(ini_y);
	new_mapchip->SetSizeX(mapchip_data[num].size_x); //�傫����ݒ�
	new_mapchip->SetSizeY(mapchip_data[num].size_y);
	new_mapchip->SetThrough(mapchip_data[num].through); //���蔲���邩�ݒ�
	new_mapchip->SetBreakable(mapchip_data[num].breakable); //�󂹂邩�ݒ�
	new_mapchip->SetHitMap(mapchip_data[num].hit_map); //���̃}�b�v�`�b�v�ɓ����邩�ݒ�
	new_mapchip->SetFlying(mapchip_data[num].flying); //�����Ă��邩�ݒ�
	new_mapchip->SetFriction(mapchip_data[num].friction); //���C��ݒ�
	new_mapchip->SetHitMap(hit_map); //���}�b�v�`�b�v�Ƃ̓����蔻���ݒ�

	mapchip.emplace_back(new_mapchip);

	return new_mapchip;
}

//�L�������}�b�v�`�b�v�ɓ������Ă��邩
bool MapChipManager::HitCheck(float cx, float cy, float hit_size, int break_power, bool abs_check) {
	bool flag = false; //����������
	for (auto &map : mapchip) {
		if ((!map->GetHitFlag() && !abs_check) || !map->GetLiveFlag() || !map->GetDrawFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.0f * map->GetSizeX() + hit_size; //����p
		float sub_x = cx - map->GetX(); //x���W�̍�

		//x���W���������Ă��Ȃ��Ȃ��΂�
		if (!(fabsf(sub_x) < x)) {
			continue;
		}

		float y = 4.0f * map->GetSizeY() + hit_size; //����p
		float center_y = map->GetY() + 4.0f * map->GetSizeY(); //�}�b�v�`�b�v�̒��S
		float sub_y = cy - center_y; //y���W�̍�

		//y���W���������Ă���Ȃ�
		if (fabsf(sub_y) < y) {
			//x���W��y���W���r
			//y���W�̕��������Ȃ�
			if (fabsf(sub_x) < fabsf(sub_y)) {
				//��ɓ��������Ȃ�
				if (sub_y < 0.0f) {
					map->SetHitTop(true); //��ɓ����������Ƃ�
				}
				//���ɓ��������Ȃ�
				else {
					map->SetHitBottom(true); //���ɓ����������Ƃ�
				}
			}
			//y���W�̕��������Ȃ�
			else {
				//���ɓ��������Ȃ�
				if (sub_x < 0.0f) {
					map->SetHitLeft(true); //���ɓ����������Ƃ�
				}
				//�E�ɓ��������Ȃ�
				else {
					map->SetHitRight(true); //�E�ɓ����������Ƃ�
				}
			}
			
			//�󂷂��m�F���Ă�����
			if (map->GetBreakable() <= break_power && map->GetBreakable() != 0) {
				map->SetEndFlag(true); //���Ńt���O��true��
			}
			flag = true; //���������t���O��true��
		}
	}
	return flag;
}

//�L�������}�b�v�`�b�v�ɓ������Ă��邩(���̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckLeft(float cx, float cy, float hit_size) {
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag() || map->GetThrough()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.0f * map->GetSizeX(); //����p
		float y = 4.0f * map->GetSizeY() + hit_size - 0.01f; //����p
		float center_y = map->GetY() + 4.0f * map->GetSizeY(); //�}�b�v�`�b�v�̒��S
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf((cx - hit_size) - map->GetX()) < x && fabsf(cy - center_y) < y) {
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�L�������}�b�v�`�b�v�ɓ������Ă��邩(�E�̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckRight(float cx, float cy, float hit_size) {
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag() || map->GetThrough()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.0f * map->GetSizeX(); //����p
		float y = 4.0f * map->GetSizeY() + hit_size - 0.01f; //����p
		float center_y = map->GetY() + 4.0f * map->GetSizeY(); //�}�b�v�`�b�v�̒��S
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf((cx + hit_size) - map->GetX()) < x && fabsf(cy - center_y) < y) {
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�L�������}�b�v�`�b�v�ɓ������Ă��邩(��̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckTop(float cx, float cy, float hit_size) {
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag() || map->GetThrough()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.0f * map->GetSizeX() + hit_size - 0.01f; //����p
		float y = 8.0f * map->GetSizeY(); //����p
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf(cx - map->GetX()) < x && fabsf((cy - hit_size) - map->GetY()) < y && map->GetY() + y < cy) {
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�L�������}�b�v�`�b�v�ɓ������Ă��邩(���̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckBottom(float cx, float cy, float hit_size) {
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.0f * map->GetSizeX() + hit_size - 0.01f; //����p
		float y = hit_size; //����p
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf(cx - map->GetX()) < x && fabsf(cy - map->GetY()) < y) {
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�L�������}�b�v�`�b�v�ɏ���Ă��邩
void MapChipManager::CheckStep(float cx, float cy, float hit_size) {
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.0f * map->GetSizeX() + hit_size; //����p
		float y = 8.0f * map->GetSizeY(); //����p
		float sub_y = (cy + hit_size) - map->GetY();
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf(cx - map->GetX()) < x && sub_y < y && 0.0f < sub_y) {
			map->SetStep(true); //����Ă���t���O��true��
		}
		//�����łȂ����
		else {
			map->SetStep(false); //����Ă���t���O��false��
		}
	}
}

//�}�b�v�`�b�v�ɏ���Ă���L�����ɑ������x���擾
float MapChipManager::GetPlusSpeedX(float cx, float cy, float hit_size) {
	float sx = 0.0f; //�Ԃ����x
	//�ړ��O�̍��W���g���i���O�܂ŏ���Ă��������m�F�j
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.0f * map->GetSizeX() + hit_size; //����p
		float y = 8.0f * map->GetSizeY(); //����p
		float sub_y = (cy + hit_size) - map->GetLastY();
		float map_sx = map->GetAmountX() + map->GetMoveX();
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf(cx - map->GetLastX()) < x && sub_y < y && 0.0f < sub_y) {
			//���݂̑��x�Ɣ��΂Ȃ��
			if ((sx < 0.0f && 0.0f < map_sx) || (0.0f < sx && map_sx < 0.0f)) {
				sx += map_sx; //�}�b�v�`�b�v�̑��x�𑊎E����
			}
			//���݂̑��x���傫���Ȃ�
			else if (fabsf(sx) < fabsf(map_sx)) {
				sx = map_sx; //���x���㏑��
			}
		}
	}
	return sx;
}

//�}�b�v�`�b�v�ɏ���Ă���L�����ɑ������x���擾
float MapChipManager::GetPlusSpeedY(float cx, float cy, float hit_size) {
	float sy = 0.0f; //�Ԃ����x
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.0f * map->GetSizeX() + hit_size; //����p
		float y = 8.0f * map->GetSizeY(); //����p
		float sub_y = (cy + hit_size) - map->GetLastY();
		float map_sy = map->GetAmountY() + map->GetMoveY();
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf(cx - map->GetLastX()) < x && sub_y < y && 0.0f < sub_y) {
			//���݂̑��x�Ɣ��΂Ȃ��
			if ((sy < 0.0f && 0.0f < map_sy) || (0.0f < sy && map_sy < 0.0f)) {
				sy += map_sy; //�}�b�v�`�b�v�̑��x�𑊎E����
			}
			//���݂̑��x���傫���Ȃ�
			else if (fabsf(sy) < fabsf(map_sy)) {
				sy = map_sy; //���x���㏑��
			}
		}
	}
	return sy;
}

//�L�������C�x���g�����ʒu�ɓ������Ă��邩
void MapChipManager::EventHitCheck(shared_ptr<EventManager> event, float cx, float cy) {
	for (unsigned int i = 0; i < standby_event.size(); i++) {
		bool hit_x = (fabsf(cx - standby_event[i].x) < 32.0f) || event->GetPosition(i);
		bool hit_y = (fabsf(cy - standby_event[i].y) < 32.0f) || !event->GetPosition(i);
		if (hit_x && hit_y && standby_event[i].flag) {
			//sound->PlaySoundEffect(7); //���ʉ���炷
			event->SetEventList(standby_event[i].num, standby_event[i].x, standby_event[i].y); //�C�x���g��\��
			standby_event[i].flag = false; //�t���O��false��
			break;
		}
	}
}

//�L���������[�v���ɓ������Ă��邩
void MapChipManager::WarpHitCheck(shared_ptr<EventManager> event, shared_ptr<Key> key, shared_ptr<Sound> sound, float cx, float cy) {
	if (warp_door.size() <= 0 || warp_flag) return; //���[�v�����Ȃ������łɃ��[�v�ҋ@�Ȃ�I��
	for (auto& warp : warp_door) {
		if (!key->KeyCheckOnce(Up)) continue; //�オ������Ă��Ȃ��Ȃ��΂�
		bool hit_x = (fabsf(cx - warp.x) < 4.0f * warp_data[warp.num].size_x);
		bool hit_y = (fabsf(cy - warp.y) < 4.0f * warp_data[warp.num].size_y);
		//���[�v���ɓ������Ă���Ȃ�
		if (hit_x && hit_y) {
			warp_flag = true; //���[�v�t���O��true��
			warp_num = warp.num; //�Q�Ƃ������ݒ�
			next_map = warp_data[warp_num].next_num; // ���̃}�b�v��ݒ�
			event->SetEvent(0); //��~�C�x���g��\��
			sound->PlaySoundEffect(15); //���ʉ���炷
			break;
		}
	}
}

//���[�v���邩�擾
bool MapChipManager::GetWarpFlag() {
	return warp_flag;
}

//�}�b�v�`�b�v�����̃}�b�v�`�b�v�ɓ������Ă��邩(���̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckLeftMap(std::shared_ptr<AbstractMapChip> check_map) {
	
	int size_x = check_map->GetSizeX();//�m�F�p�}�b�v�`�b�v�̑傫��
	int size_y = check_map->GetSizeY();//�m�F�p�}�b�v�`�b�v�̑傫��
	float check_x = check_map->GetX(); //�m�F�p�}�b�v�`�b�v��x���W
	float check_y = check_map->GetY() + 4.0f + size_y; //�m�F�p�}�b�v�`�b�v��y���W

	for (auto& map : mapchip) {
		if (check_map == map || !map->GetHitFlag() || !map->GetLiveFlag() || !map->GetHitMap()) continue; //�����}�b�v�`�b�v�������蔻�肪�Ȃ���Δ�΂�

		float y = 4.0f * map->GetSizeY() + 4.0f * size_y; //����p
		float center_y = map->GetY() + 4.0f * map->GetSizeY(); //�}�b�v�`�b�v�̒��S
		//���炩�ɉ����Ȃ��΂�
		if (!(fabsf(check_y - center_y) < y)) {
			continue;
		}

		float x = 4.0f * map->GetSizeX(); //����p
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf((check_x - 4.0f * size_x) - map->GetX()) < x) {
			return map; //map��Ԃ�
		}

	}
	return NULL;
}

//�}�b�v�`�b�v�����̃}�b�v�`�b�v�ɓ������Ă��邩(�E�̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckRightMap(std::shared_ptr<AbstractMapChip> check_map) {

	int size_x = check_map->GetSizeX();//�m�F�p�}�b�v�`�b�v�̑傫��
	int size_y = check_map->GetSizeY();//�m�F�p�}�b�v�`�b�v�̑傫��
	float check_x = check_map->GetX(); //�m�F�p�}�b�v�`�b�v��x���W
	float check_y = check_map->GetY() + 4.0f + size_y; //�m�F�p�}�b�v�`�b�v��y���W

	for (auto& map : mapchip) {
		if (check_map == map || !map->GetHitFlag() || !map->GetLiveFlag() || !map->GetHitMap()) continue; //�����}�b�v�`�b�v�������蔻�肪�Ȃ���Δ�΂�

		float y = 4.0f * map->GetSizeY() + 4.0f * size_y; //����p
		float center_y = map->GetY() + 4.0f * map->GetSizeY(); //�}�b�v�`�b�v�̒��S
		//���炩�ɉ����Ȃ��΂�
		if (!(fabsf(check_y - center_y) < y)) {
			continue;
		}

		float x = 4.0f * map->GetSizeX(); //����p
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf((check_x + 4.0f * size_x) - map->GetX()) < x) {
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�}�b�v�`�b�v�����̃}�b�v�`�b�v�ɓ������Ă��邩(��̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckTopMap(std::shared_ptr<AbstractMapChip> check_map) {
	
	int size_x = check_map->GetSizeX();//�m�F�p�}�b�v�`�b�v�̑傫��
	float check_x = check_map->GetX(); //�m�F�p�}�b�v�`�b�v��x���W
	float check_y = check_map->GetY(); //�m�F�p�}�b�v�`�b�v��y���W

	for (auto& map : mapchip) {
		if (check_map == map || !map->GetHitFlag() || !map->GetLiveFlag() || !map->GetHitMap() || map->GetThrough()) continue; //�����}�b�v�`�b�v�������蔻�肪�Ȃ���Δ�΂�

		float x = 4.0f * map->GetSizeX() + 4.0f * size_x; //����p
		//���炩�ɉ����Ȃ��΂�
		if (!(fabsf(check_x - map->GetX()) < x)) {
			continue;
		}

		float y = 8.0f * map->GetSizeY(); //����p
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf(check_y - map->GetY()) < y && map->GetY() < check_y) {
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�}�b�v�`�b�v�����̃}�b�v�`�b�v�ɓ������Ă��邩(���̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckBottomMap(std::shared_ptr<AbstractMapChip> check_map, bool plus_one) {

	int size_x = check_map->GetSizeX(); //�m�F�p�}�b�v�`�b�v�̑傫��
	int size_y = check_map->GetSizeY(); //�m�F�p�}�b�v�`�b�v�̑傫��
	float check_x = check_map->GetX(); //�m�F�p�}�b�v�`�b�v��x���W
	float check_y = check_map->GetY(); //�m�F�p�}�b�v�`�b�v��y���W
	if (plus_one) check_y += 1.0f;

	for (auto& map : mapchip) {
		if (check_map == map || !map->GetHitFlag() || !map->GetLiveFlag() || !map->GetHitMap()) continue; //�����}�b�v�`�b�v�������蔻�肪�Ȃ���Δ�΂�
		
		float x = 4.0f * map->GetSizeX() + 4.0f * size_x; //����p
		//���炩�ɉ����Ȃ��΂�
		if (!(fabsf(check_x - map->GetX()) < x)) {
			continue;
		}

		float y = 8.0f * size_y; //����p
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf(check_y - map->GetY()) < y) {
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�ʒu�̒���
void MapChipManager::AdjustPosition() {
	//�擾�p�N���X
	shared_ptr<AbstractMapChip> hit_map;

	for (auto& map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag() || !map->GetDrawFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		int size_x = map->GetSizeX();//�}�b�v�`�b�v�̑傫��
		int size_y = map->GetSizeY();//�}�b�v�`�b�v�̑傫��
		float x = map->GetX(); //�}�b�v�`�b�v��x���W
		float y = map->GetY(); //�}�b�v�`�b�v��y���W
		float sx = map->GetXSpeed(); //�}�b�v�`�b�v�̑��x
		float sy = map->GetYSpeed(); //�}�b�v�`�b�v�̑��x
		bool hit_check = map->GetHitMap(); //�}�b�v�`�b�v�ɓ����邩

		map->SetLastX(x); //�ړ��O�̍��W���i�[
		map->SetLastY(y); //�ړ��O�̍��W���i�[

		map->SetX(x + sx);

		//���E�̔��肩��
		if (sx < -0.1f && hit_check) {
			hit_map = HitCheckLeftMap(map);
			while (hit_map != NULL)
			{
				map->SetX(hit_map->GetX() + 4.0f * ((float)size_x + (float)hit_map->GetSizeX()));
				map->SetXSpeed(0.0f);
				hit_map = HitCheckLeftMap(map);
			}
		}

		if (0.1f < sx && hit_check) {
			hit_map = HitCheckRightMap(map);
			while (hit_map != NULL)
			{
				map->SetX(hit_map->GetX() - 4.0f * ((float)size_x + (float)hit_map->GetSizeX()));
				map->SetXSpeed(0.0f);
				hit_map = HitCheckRightMap(map);
			}
		}

		//�����Ă��Ȃ����
		if (!map->GetFlying()) {
			//�����ɉ����Ȃ��Ȃ�
			if (HitCheckBottomMap(map, true) == NULL) {
				//���x���قڂȂ��Ȃ�
				if (fabsf(sy) < 0.4f) {
					sy = 4.0f; //���x��ݒ�
				}
				//���x������Ȃ�
				else {
					sy += fabsf(sy * 0.3f); //���x��1.3(0.7)�{����
					if (JUMP_SPEED < sy) sy = JUMP_SPEED;
				}
			}
		}

		//�㉺�̔���
		map->SetY(y + sy);

		if (sy < -0.1f && hit_check) {
			hit_map = HitCheckTopMap(map);

			while (hit_map != NULL) {
				map->SetY(hit_map->GetY() + 8.0f * hit_map->GetSizeY());
				map->SetYSpeed(0.0f);
				hit_map = HitCheckTopMap(map);
			}
		}
		if (0.1f < sy && hit_check) {
			hit_map = HitCheckBottomMap(map);
			while (hit_map != NULL) {
				map->SetY(hit_map->GetY() - 8.0f * size_y);
				map->SetYSpeed(0.0f);
				hit_map = HitCheckBottomMap(map);
			}
		}

	}
}

//��ʓ��Ɏ��܂��Ă��邩�m�F
void MapChipManager::WindowCheck(shared_ptr<AbstractMapChip> map, shared_ptr<Camera> camera) {
	float left = (float)camera->GetScrollX(); //��ʍ��[
	float right = (float)camera->GetScrollX() + (float)WINDOW_X; //��ʉE�[
	float top = (float)camera->GetScrollY(); //��ʏ�
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y; //��ʒ�

	bool draw_flag; //�`�悷��t���O
	float x = map->GetX();
	float y = map->GetY();
	int size_x = map->GetSizeX();
	int size_y = map->GetSizeY();

	//��ʓ��Ȃ�`�悷��
	draw_flag = (left - 32.0f - (4.0f * size_x) < x && x < right + 32.0f +(4.0f * size_x) && top - 32.0f - (8.0f * size_y) < y && y < bottom + 32.0f);
	map->SetDrawFlag(draw_flag);
	
}

//�w�i�̍X�V
void MapChipManager::BackUpdate(shared_ptr<Image> image) {
	for (unsigned int i = 0; i < back_data.size(); i++) {
		//�X�N���[���ʂ��擾
		int dif_x = 0;
		int dif_y = 0;

		//�w�i�摜�̑傫�����擾
		int size_x;
		int size_y;
		int image_num = image->GetBackImage(back_data[i].image);
		GetGraphSize(image_num, &size_x, &size_y);

		//�X�N���[���ʂ̕������w�i���ړ�
		//back_data[i].x -= ((float)scroll_speed_x * back_data[i].sx);
		//back_data[i].y -= ((float)scroll_speed_y * back_data[i].sy);
		
		//�w�i�����[�v����ꍇ
		if (back_data[i].loop) {
			//�w�i(�̉E�[)����ʊO(��)�ɏo���ꍇ
			if (back_data[i].x < -size_x) {
				back_data[i].x += size_x; //�摜�̑傫�����E�ֈړ�
			}

			//�w�i(�̉E�[)����ʊO(�E)�ɏo���ꍇ
			if (back_data[i].x > 0) {
				back_data[i].x -= size_x; //�摜�̑傫�������ֈړ�
			}
		}
		//���Ȃ��ꍇ
		else {
			//�w�i(�̍��[)����ʒ[(��)���E�ɏo���ꍇ
			if (back_data[i].x > 0.0f) {
				back_data[i].x = 0.0f; //�w�i�̍��[��0�Ɉړ�
			}
			//�w�i(�̉E�[)����ʒ[(�E)��荶�ɏo���ꍇ
			if (back_data[i].x + (float)size_x < WINDOW_X) {
				back_data[i].x = (float)WINDOW_X - (float)size_x; //�w�i�̍��[���E�B���h�E-�摜�Ɉړ�
			}
		}
	}
}

//�w�i�̕`��
void MapChipManager::BackDraw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	for (auto &back : back_data) {
		//�w�i�摜�̑傫�����擾
		int size_x;
		int size_y;
		int num = image->GetBackImage(back.image); //�w�i���擾
		GetGraphSize(num, &size_x, &size_y);
		float x = back.x;// +(float)size_x;
		float y = back.y;// +(float)size_y;

		Display::BackDraw(x, y, num); //�w�i��`��
		//���[�v����ꍇ����1��
		if (back.loop) {
			Display::BackDraw(x + size_x, y, num); //�w�i��`��
		}
	}
}

//�X�V
void MapChipManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Image> image, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera){
	
	BackUpdate(image);

	for (auto &map : mapchip) {
		if (!map->GetLiveFlag()) continue;

		map->Update(player, enemy, bullet, effect, key, sound);
		map->Timer();
		map->SetHitLeft(false); //���̔����������
		map->SetHitRight(false); //�E�̔����������
		map->SetHitTop(false); //��̔����������
		map->SetHitBottom(false); //���̔����������

		//���Ńt���O��true�Ȃ瓮�삵�Ȃ��Ȃ�
		if (map->GetEndFlag()) {

			map->SetLiveFlag(false);
		}

		WindowCheck(map, camera); //�`�悷�邩�m�F
	}
}

//�`��
void MapChipManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	BackDraw(image, camera); //�w�i�̕`��

	for (auto &map : mapchip) {
		if (map->GetLiveFlag() && map->GetDrawFlag()) {
			map->Draw(image, camera);
			//DrawFormatString((int)map->GetX(), (int)map->GetY(), GetColor(255, 0, 0), "%f %d", map->GetX(), map->GetTime());
		}
	}

	for (auto& warp : warp_door) {
		int hundle = image->GetMapchipImage(warp_data[warp.num].image);
		camera->Draw(warp.x, warp.y, true, 0.0f, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	}

	//DrawFormatString(64, 64, GetColor(255, 0, 0), "%d", mapchip.size());

	/*for (auto eve : standby_event) {
		int hundle = image->GetMapchipImage(0);
		camera->Draw(eve.x, eve.y, LEFT, 0.0f, hundle, DX_BLENDMODE_NOBLEND);
	}*/

	/*for (unsigned int i = 0; i < back_data.size(); i++) {
		DrawFormatString(64, 128 + (24 * i), GetColor(255, 0, 0), "%f %f %d", back_data[i].x, back_data[i].y, back_data[i].image);
	}*/
}