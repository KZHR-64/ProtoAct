#pragma once
#include "DxLib.h"
#include "AbstractItem.h"
#include <math.h>

using namespace std;

AbstractItem::AbstractItem(ItemManager* man, int num, float ini_x, float ini_y) : CharacterBase() {
	manager = man;

	time = 0;
	live_flag = true;
	end_time = -1;
	end_flag = false;
	image_num = num;
	x = ini_x;
	y = ini_y;
	base_x = x;
	base_y = y;
	angle = 0.0f;
	SetSpeed(0.0f);
	hit_player = false;
	hit_enemy = false;
	hit_map = false;
}

AbstractItem::~AbstractItem(){

}

//���@�ɓ����邩���擾
bool AbstractItem::GetHitPlayer() {
	return hit_player;
}

//���@�ɓ����邩��ݒ�
void AbstractItem::SetHitPlayer(bool flag) {
	hit_player = flag;
}

//�G�ɓ����邩���擾
bool AbstractItem::GetHitEnemy() {
	return hit_enemy;
}

//�G�ɓ����邩��ݒ�
void AbstractItem::SetHitEnemy(bool flag) {
	hit_enemy = flag;
}

//�}�b�v�`�b�v�ɓ����邩���擾
bool AbstractItem::GetHitMap() {
	return hit_map;
}

//�}�b�v�`�b�v�ɓ����邩��ݒ�
void AbstractItem::SetHitMap(bool flag) {
	hit_map = flag;
}

//�v���C���[�Ƃ̓����蔻��
bool AbstractItem::HitCheckPlayer(std::shared_ptr<Player> player) {
	for (auto& h : hit) {
		if (player->HitCheckItem(h.x, h.y, h.size)) {
			return true;
		}
	}

	return false;
}

//�}�b�v�`�b�v�Ƃ̓����蔻��
void AbstractItem::HitCheckMap(shared_ptr<MapChipManager> map) {
	/*shared_ptr<AbstractMapChip> mapchip;

	float sub_x = 0.0f; //����ɂǂꂾ���߂荞��ł��邩

	//����Ă��鑫��̑��x�̍��v
	float mx = map->GetPlusSpeedX(hit.x, hit.y + 1.0f, hit.size);
	float my = map->GetPlusSpeedY(hit.x, hit.y + 1.0f, hit.size);

	x += sx + mx; //�s���\��̍��W������

	//���E�Ƃ̔���
	mapchip = map->HitCheckLeft(hit.x, hit.y, hit.size);
	while (mapchip != NULL) {
		sub_x = (hit.x - hit.size) - (mapchip->GetX() + 4.0f * mapchip->GetSizeX());
		x += fabsf(sub_x);
		sx = 0.0f;
		HitUpdate();
		mapchip = map->HitCheckLeft(hit.x, hit.y, hit.size);
	}
	mapchip = map->HitCheckRight(hit.x, hit.y, hit.size);
	while (mapchip != NULL) {
		sub_x = (hit.x + hit.size) - (mapchip->GetX() - 4.0f * mapchip->GetSizeX());
		x -= fabsf(sub_x);
		sx = 0.0f;
		HitUpdate();
		mapchip = map->HitCheckRight(hit.x, hit.y, hit.size);
	}

	//�����Ă��Ȃ��Ȃ�
	//if (!flying_flag) {
		if (sy < 0.4f && sy > -0.4f) sy = 0.4f;
		sy += fabsf(sy * 1.3f); //���x��1.3(0.7)�{(��s����1.1�{)����
		if (sy > 10.0f) sy = 10.0f;
	//}

	y += sy + my; //�s���\��̍��W������
	HitUpdate(); //�����蔻����X�V

	//�㉺�Ƃ̔���
	mapchip = map->HitCheckTop(hit.x, hit.y, hit.size);
	while (mapchip != NULL) {
		sub_x = (hit.y - hit.size) - (mapchip->GetY() + 8.0f * mapchip->GetSizeY());
		y += fabsf(sub_x);
		sy = 0.0f;
		HitUpdate();
		mapchip = map->HitCheckTop(hit.x, hit.y, hit.size);
	}
	mapchip = map->HitCheckBottom(hit.x, hit.y, hit.size);
	while (mapchip != NULL) {
		sub_x = (hit.y + hit.size) - (mapchip->GetY());
		y -= fabsf(sub_x);
		sy = 0.0f;
		HitUpdate();
		mapchip = map->HitCheckBottom(hit.x, hit.y, hit.size);
	}*/
	shared_ptr<AbstractMapChip> mapchip;

	float sub_x = 0.0f; //����ɂǂꂾ���߂荞��ł��邩

	//����Ă��鑫��̑��x�̍��v
	float mx = 0.0f;
	float my = 0.0f;

	for (unsigned int i = 0; i < hit.size(); i++) {
		//����Ă��鑫��̑��x�̍��v
		mx += map->GetPlusSpeedX(hit[i].x, hit[i].y + 1.0f, hit[i].size);
		my += map->GetPlusSpeedY(hit[i].x, hit[i].y + 1.0f, hit[i].size);
	}

	adjusted = false; //�����������͈�Ufalse��

	angle += spin_speed; //��]

	x += sx + mx; //�s���\��̍��W������

	HitUpdate(); //�����蔻����X�V

	//���E�Ƃ̔���
	for (unsigned int i = 0; i < hit.size(); i++) {
		mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			adjusted = true; //�����������Ƃ�
			sub_x = (hit[i].x - hit[i].size) - (mapchip->GetX() + 4.0f * mapchip->GetSizeX());
			x += fabsf(sub_x);
			sx = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			adjusted = true; //�����������Ƃ�
			sub_x = (hit[i].x + hit[i].size) - (mapchip->GetX() - 4.0f * mapchip->GetSizeX());
			x -= fabsf(sub_x);
			sx = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//�����Ă��Ȃ��Ȃ�
	//if (!flying_flag) {
	if (sy < 0.4f && sy > -0.4f) sy = 0.4f;
	sy += fabsf(sy * 1.3f); //���x��1.3(0.7)�{(��s����1.1�{)����
	if (sy > 10.0f) sy = 10.0f;
	//}

	y += sy + my; //�s���\��̍��W������
	HitUpdate(); //�����蔻����X�V

	//�㉺�Ƃ̔���
	for (unsigned int i = 0; i < hit.size(); i++) {
		mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			adjusted = true; //�����������Ƃ�
			sub_x = (hit[i].y - hit[i].size) - (mapchip->GetY() + 8.0f * mapchip->GetSizeY());
			y += fabsf(sub_x);
			sy = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			adjusted = true; //�����������Ƃ�
			sub_x = (hit[i].y + hit[i].size) - (mapchip->GetY());
			y -= fabsf(sub_x);
			sy = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		}
	}
}

//�L�����N�^�[�Ƃ̓����蔻��
bool AbstractItem::HitCheckChara(float cx, float cy, float hit_size) {
	if (hit.size() <= 0) return false;

	for (auto &h : hit) {
		float dif_x = cx - h.x;
		float dif_y = cy - h.y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + h.size) {
			return true;
		}
	}

	return false;
}