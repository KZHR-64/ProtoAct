#pragma once
#include "DxLib.h"
#include "AbstractBullet.h"
#include <math.h>

using namespace std;

AbstractBullet::AbstractBullet(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : CharacterBase() {
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
	base_speed = ini_speed;
	angle = ini_angle;
	SetSpeed(ini_speed);
	damage = 0;
	hit_player = false;
	hit_enemy = false;
	hit_map = false;
	breakable = false;
	break_power = 1;
}

AbstractBullet::~AbstractBullet(){
	hit.clear(); //�����蔻��̃����������
}

//�_���[�W�l��Ԃ�
int AbstractBullet::GetDamage() {
	return damage;
}

//�_���[�W�l��ݒ�
void AbstractBullet::SetDamage(int set_damage) {
	damage = set_damage;
}

//�󂹂邩���擾
bool AbstractBullet::GetBreakable() {
	return breakable;
}

//�󂹂邩��ݒ�
void AbstractBullet::SetBreakable(bool flag) {
	breakable = flag;
}

//���@�ɓ����邩���擾
bool AbstractBullet::GetHitPlayer() {
	return hit_player;
}

//���@�ɓ����邩��ݒ�
void AbstractBullet::SetHitPlayer(bool flag) {
	hit_player = flag;
}

//�G�ɓ����邩���擾
bool AbstractBullet::GetHitEnemy() {
	return hit_enemy;
}

//�G�ɓ����邩��ݒ�
void AbstractBullet::SetHitEnemy(bool flag) {
	hit_enemy = flag;
}

//�}�b�v�`�b�v�ɓ����邩���擾
bool AbstractBullet::GetHitMap() {
	return hit_map;
}

//�}�b�v�`�b�v�ɓ����邩��ݒ�
void AbstractBullet::SetHitMap(bool flag) {
	hit_map = flag;
}

//�}�b�v�`�b�v�̔j��͂�Ԃ�
int AbstractBullet::GetBreakPower() {
	return break_power;
}

//�}�b�v�`�b�v�̔j��͂�ݒ�
void AbstractBullet::SetBreakPower(int set_power) {
	break_power = set_power;
}

//�L�����N�^�[�Ƃ̓����蔻��
int AbstractBullet::HitCheckChara(float cx, float cy, float hit_size) {
	if (hit.size() <= 0) return -1;

	for (auto &h : hit) {
		float dif_x = cx - h.x;
		float dif_y = cy - h.y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + h.size) {
			//�󂹂�e�Ȃ����
			if (breakable) {
				end_flag = true;
			}
			return damage;
		}
	}

	return -1;
}

//�}�b�v�`�b�v�Ƃ̓����蔻��
void AbstractBullet::HitCheckMap(shared_ptr<MapChipManager> map) {
	if (hit.size() <= 0) return;

	for (auto& h : hit) {
		if (map->HitCheck(h.x, h.y, h.size, break_power)) {
			//�󂹂�e�Ȃ����
			if (breakable) {
				end_flag = true;
			}
		}
	}
}