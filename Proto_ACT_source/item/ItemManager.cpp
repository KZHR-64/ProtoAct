#pragma once
#include "DxLib.h"
#include "ItemManager.h"
#include "itemlist\DoorKey.h"

using namespace std;

ItemManager::ItemManager() {
	SetData();
}

ItemManager::~ItemManager() {
	item.clear();
	item_data.clear();
}

//������
void ItemManager::Reset() {
	item.clear();
}

//�A�C�e�����̐ݒ�
void ItemManager::SetData() {
	int num;
	ifstream ifs("data/item/item_data.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		// ���s�R�[�h���폜
		if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
		if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

		stringstream ss{ str };
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		item_data[num].type = atoi(s.c_str()); //��ނ��擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		item_data[num].image = atoi(s.c_str()); //�摜�̔ԍ����擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		item_data[num].hit_player = (1 == atoi(s.c_str())); //���@�ɓ����邩���擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		item_data[num].hit_enemy = (1 == atoi(s.c_str())); //�G�ɓ����邩���擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		item_data[num].hit_map = (1 == atoi(s.c_str())); //�}�b�v�`�b�v�ɓ����邩���擾
	}
	ifs.close();

}

//�����邩�m�F
void ItemManager::EraseCheck() {
	if (item.size() == 0) return;

	for (auto it = item.begin(); it != item.end();) {
		bool erase_flag = false; //������t���O
		int end_time = (*it)->GetEndTime(); //������܂ł̎���

		//������܂ł̎��Ԃ�0���傫���Ȃ�
		if (0 < end_time) {
			end_time--; //���Ԃ����炷
			//���Ԃ�0�ɂȂ����������
			if (end_time <= 0) erase_flag = true;
			(*it)->SetEndTime(end_time); //���Ԃ�ݒ�
		}

		//�����t���O��true�Ȃ����
		if ((*it)->GetEndFlag() || erase_flag) {
			it = item.erase(it);
		}
		else {
			it++;
		}
	}
}

//�A�C�e�����}�b�v�ɔz�u
void ItemManager::SetStandby(string file_name) {
	int row = 0; //�s
	int col = 0; //��

	ifstream ifs(file_name);
	
	//�Ȃ���ΏI��
	if (ifs.fail()) {
		ifs.close();
		return;
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
				//�A�C�e����z�u
				SetItem(num, 32.0f * col, 32.0f * row);
			}
			col++; //�񐔂𑝂₷
		}

		//�񐔂����Z�b�g���čs���𑝂₷
		col = 0;
		row++;
	}

	ifs.close();
}

//�A�C�e���̔z�u
shared_ptr<AbstractItem> ItemManager::SetItem(int num, float ini_x, float ini_y) {
	shared_ptr<AbstractItem> new_item;

	switch (item_data[num].type)
	{
	case 0:
		new_item = make_shared<DoorKey>(this, item_data[num].image, ini_x, ini_y);
		break;
	default:
		new_item = make_shared<DoorKey>(this, item_data[num].image, ini_x, ini_y);
		break;
	}

	new_item->SetHitPlayer(item_data[num].hit_player); //���@�ɓ����邩�ݒ�
	new_item->SetHitEnemy(item_data[num].hit_enemy); //�G�ɓ����邩�ݒ�
	new_item->SetHitMap(item_data[num].hit_map); //�}�b�v�`�b�v�ɓ����邩�ݒ�

	item.emplace_back(new_item);

	return new_item;
}

//�}�b�v�`�b�v�Ƃ̓����蔻��
void ItemManager::HitCheckMap(shared_ptr<MapChipManager> map) {
	if (item.size() == 0) return;
	for (auto& it : item) {
		if (!it->GetHitMap()) continue;
		it->HitCheckMap(map);
	}
}

//�v���C���[�Ƃ̓����蔻��
void ItemManager::HitCheckPlayer(shared_ptr<Player> player, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (item.size() == 0) return;
	for (auto& it : item) {
		if (!it->GetHitPlayer()) continue;
		//���@�ɓ������Ă���Ȃ�
		if (it->HitCheckPlayer(player)) {
			it->ItemGet(player, effect, sound); //�A�C�e���擾���̏���
			it->SetEndFlag(true); //���Ńt���O��true��
		}
	}
}

//�L�����N�^�[�Ƃ̓����蔻��
shared_ptr<AbstractItem> ItemManager::HitCheckChara(float cx, float cy, float hit_size) {
	if (item.size() == 0) return NULL;
	for (auto& it : item) {
		if (it->HitCheckChara(cx, cy, hit_size)) {
			return it;
		}
	}
	return NULL;
}

//�X�V
void ItemManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (item.size() == 0) return;
	for (auto& it : item) {

		it->Update(player, enemy, effect, sound);

		it->SetX(it->GetX() + it->GetXSpeed());
		it->SetY(it->GetY() + it->GetYSpeed());
		int time = it->GetTime();
		time++;
		it->SetTime(time);
		it->HitUpdate();
	}

	EraseCheck(); //�A�C�e�����������m�F
}

//�`��
void ItemManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	if (item.size() == 0) return;
	for (auto& it : item) {
		it->Draw(image, camera);
		it->DrawHit(camera);
	}
	//DrawFormatString(64, 96, GetColor(255, 255, 255), "%d", item.size());
}