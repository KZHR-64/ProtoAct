#pragma once
#include "DxLib.h"
#include "AbstractEnemy.h"
#include <math.h>

using namespace std;

AbstractEnemy::AbstractEnemy(EnemyManager* man, int num, float ini_x, float ini_y) : CharacterBase() {
	manager = man;

	boss_flag = false;
	image_num = num;
	trance = 255;
	hp = 1;
	max_hp = hp;
	x = ini_x;
	y = ini_y;
	base_x = x;
	base_y = y;
	base_enemy = NULL; //�{�̂͊�{�I��NULL
}

AbstractEnemy::~AbstractEnemy(){

	for (auto &ene : parts) {
		ene->SetEndFlag(true); //�p�[�c������
		ene.reset();
	}
	parts.clear();
	hit.clear(); //�����蔻��̃����������
}

//�{�̂��擾
AbstractEnemy* AbstractEnemy::GetBase() {
	return base_enemy;
}

//�{�̂�ݒ�
void AbstractEnemy::SetBase(AbstractEnemy* base) {
	base_enemy = base;
}

//�ʒu�̒���
void AbstractEnemy::AdjustPosition(shared_ptr<MapChipManager> map, shared_ptr<EffectManager> effect) {
	shared_ptr<AbstractMapChip> mapchip;

	bool step_flag = false; //�}�b�v�`�b�v�ɏ���Ă��邩
	bool left_hit = false; //�������������Ă��邩
	bool right_hit = false; //�E�����������Ă��邩
	bool top_hit = false; //�㑤���������Ă��邩
	bool bottom_hit = false; //�������������Ă��邩

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
			left_hit = true; //�����������������Ƃ�
			adjusted = true; //�����������Ƃ�
			sub_x = (hit[i].x - hit[i].size) - (mapchip->GetX() + 4.0f * mapchip->GetSizeX());
			x += fabsf(sub_x);
			sx = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			right_hit = true; //�E���������������Ƃ�
			adjusted = true; //�����������Ƃ�
			sub_x = (hit[i].x + hit[i].size) - (mapchip->GetX() - 4.0f * mapchip->GetSizeX());
			x -= fabsf(sub_x);
			sx = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//�������������Ă�����
	if (left_hit && right_hit) {
		hp = 0; //HP��0��
		damaged = true;
		//���x��������
		sx = 0.0f;
		sy = 0.0f;
		end_flag = true; //������
		effect->SetEffect(1, x, y); //����
		return;
	}

	//�W�����v��
	if (jump_flag && !flying_flag) {
		//�㏸���Ԓ��Ȃ�
		if (0 < jump_time) {
			jump_time--; //���Ԃ�����
		}
		else
		{
			if (sy < 0.4f && sy > -0.4f) sy = 0.4f;
			sy += fabsf(sy * 1.3f); //���x��1.3(0.7)�{(��s����1.1�{)����
			if (sy > 10.0f) sy = 10.0f;
		}
	}

	y += sy + my; //�s���\��̍��W������
	HitUpdate(); //�����蔻����X�V

	//�㉺�Ƃ̔���
	for (unsigned int i = 0; i < hit.size(); i++) {
		mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			top_hit = true; //�㑤�������������Ƃ�
			adjusted = true; //�����������Ƃ�
			sub_x = (hit[i].y - hit[i].size) - (mapchip->GetY() + 8.0f * mapchip->GetSizeY());
			y += fabsf(sub_x);
			sy = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL && hit_map) {
			bottom_hit = true; //�����������������Ƃ�
			adjusted = true; //�����������Ƃ�
			sub_x = (hit[i].y + hit[i].size) - (mapchip->GetY());
			y -= fabsf(sub_x);
			sy = 0.0f;
			HitUpdate();
			mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//�������������Ă�����
	if (top_hit && bottom_hit) {
		hp = 0; //HP��0��
		damaged = true;
		//���x��������
		sx = 0.0f;
		sy = 0.0f;
		end_flag = true; //������
		effect->SetEffect(1, x, y); //����
		return;
	}

	for (unsigned int i = 0; i < hit.size(); i++)
	{
		mapchip = map->HitCheckBottom(hit[i].x, hit[i].y + 1.0f, hit[i].size); //����Ă��鑫���ݒ�

		if (mapchip != NULL) {
			jump_flag = false;
			break; //����Ă��鑫�ꂪ��������I��
		}
	}
	//�W�����v���Ă��Ȃ��ŋ󒆂ɂ���ꍇ
	if (mapchip == NULL && !jump_flag && !flying_flag) {
		jump_flag = true; //�t���O��true��
		jump_time = 0; //���~�J�n
	}
}

//�_���[�W����
void AbstractEnemy::HitDamage(int damage_num, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	//���łɃ_���[�W���󂯂Ă���Ȃ�
	if (damaged) {
		return; //�I��
	}

	damaged = true;
	damage_time = 18;

	//�{�̂�����Ȃ炻�����Ƀ_���[�W
	if (base_enemy != NULL) {
		base_enemy->HitDamage(damage_num, effect, sound);
		return;
	}

	hp -= damage_num;

	//HP��0�ɂȂ�����
	if (hp <= 0) {
		// �{�̂�����Ȃ炻�����̂���
		if (base_enemy != NULL) {
			base_enemy->Defeat(effect, sound);
		}
		else {
			Defeat(effect, sound); //���ꂽ�Ƃ��̓���
		}
	}
	//0�łȂ����
	else {
		sound->PlaySoundEffect(12); //���ʉ���炷
	}
}

//�{�X�����擾
bool AbstractEnemy::GetBossFlag() {
	return boss_flag;
}

//�{�X����ݒ�
void AbstractEnemy::SetBossFlag(int rank) {
	boss_flag = (0 < rank); //�i��0�ȏ�Ȃ�{�X
}

//�e�ɓ������Ă��邩
void AbstractEnemy::HitCheckBullet(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (hit.size() <= 0) return;

	for (auto& h : hit) {
		int damage = bullet->HitCheckChara(h.x, h.y, h.size, false, true);

		if (0 < damage && !damaged) {
			//hp -= damage;
			//damaged = true;
			//damage_time = 6;
			HitDamage(damage, effect, sound);
		}
	}
}

//�G�ɓ������Ă��邩
void AbstractEnemy::HitCheckEnemy(float cx, float cy, float hit_size, shared_ptr<EffectManager> effect) {
	if (hit.size() <= 0 || !hit_flag) return;

	for (auto& h : hit) {


	}

}

//�L�����N�^�[�Ƃ̓����蔻��
bool AbstractEnemy::HitCheckChara(float cx, float cy, float hit_size, bool check_hit) {
	if (hit.size() <= 0) return false;

	for (auto& h : hit) {

		float dif_x = cx - h.x;
		float dif_y = cy - h.y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + h.size) {
			return true;
		}
	}

	return false;
}

//�^�C�}�[�֘A�̍X�V
void AbstractEnemy::Timer() {
	time++;
	if (0 < damage_time) {
		damage_time--;
		if (damage_time <= 0) {
			damaged = false;
		}
	}
}