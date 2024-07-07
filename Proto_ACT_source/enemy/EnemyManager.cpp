#pragma once
#include "DxLib.h"
#include "EnemyManager.h"
#include "enemylist/NoMove.h"
#include "enemylist/Erhei1.h"
#include "enemylist/Erhei2.h"
#include "enemylist/Erhei3.h"
#include "enemylist/Erhei4.h"
#include "enemylist/Kurhei1.h"
#include "enemylist/Kurhei2.h"
#include "enemylist/Cannon1.h"
#include "enemylist/Cannon2.h"
#include "enemylist/Missile.h"
#include "enemylist/HomingMissile.h"
#include "enemylist/FallBomb.h"
#include "enemylist/FallBomb2.h"
#include "enemylist/DekaKurhei.h"
#include "enemylist/Desdragud.h"
#include "enemylist/DesdragudArm.h"
#include "enemylist/RaidCloud.h"
#include "enemylist/CloudBit.h"
#include <math.h>

using namespace std;

EnemyManager::EnemyManager(){
	midboss_flag = false;
	boss_flag = false;
	boss_battle = false;
	SetData();
}

EnemyManager::~EnemyManager(){
	enemy.clear();
	enemy_data.clear();
	standby_enemy.clear();
}

//������
void EnemyManager::Reset(){
	midboss_flag = false;
	boss_flag = false;
	enemy.clear();
	standby_enemy.clear();
}

//�G���̐ݒ�
void EnemyManager::SetData() {
	int num;

	ifstream ifs("data/enemy/enemy_data.csv");

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
		enemy_data[num].type = atoi(s.c_str()); //��ނ��擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		enemy_data[num].hp = atoi(s.c_str()); //HP���擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		enemy_data[num].image = atoi(s.c_str()); //�摜�̔ԍ����擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		enemy_data[num].size_x = atoi(s.c_str()); //���̑傫�����擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		enemy_data[num].size_y = atoi(s.c_str()); //�c�̑傫�����擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		enemy_data[num].rank = atoi(s.c_str()); //�i���擾
	}
	ifs.close();
}

//�����邩�m�F
void EnemyManager::EraseCheck(shared_ptr<Camera> camera) {
	if (enemy.size() == 0) return;
	float left = (float)camera->GetScrollX() - 64.0f; //��ʍ��[
	float right = (float)camera->GetScrollX() + (float)WINDOW_X + 64.0f; //��ʉE�[
	float top = (float)camera->GetScrollY() - 64.0f; //��ʏ�
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y + 64.0f; //��ʒ�

	for (auto ene = enemy.begin(); ene != enemy.end();) {
		bool erase_flag; //������t���O
		float x = (*ene)->GetX();
		float y = (*ene)->GetY();
		float size_x = 128.0f;// *(*ene)->GetSizeX();
		float size_y = 128.0f;// *(*ene)->GetSizeY();
		int end_time = (*ene)->GetEndTime(); //������܂ł̎���

		//��ʊO�Ȃ����
		erase_flag = (x < left - size_x || right + size_x < x || y < top - size_y || bottom + size_y < y) && (*ene)->GetBase() == NULL && !(*ene)->GetBossFlag();

		//������܂ł̎��Ԃ�0���傫���Ȃ�
		if (0 < end_time) {
			end_time--; //���Ԃ����炷
			//���Ԃ�0�ɂȂ����������
			if (end_time <= 0) erase_flag = true;
			(*ene)->SetEndTime(end_time); //���Ԃ�ݒ�
		}

		//�����t���O��true�Ȃ����
		if (erase_flag) {
			(*ene)->SetEndFlag(true);
		}
		ene++;
	}

	for (auto ene = enemy.begin(); ene != enemy.end();) {
		//�����t���O��true�Ȃ����
		if ((*ene)->GetEndFlag()) {
			ene = enemy.erase(ene);
		}
		else {
			ene++;
		}
	}
}

//�G���}�b�v�ɔz�u
void EnemyManager::SetStandby(std::string file_name) {
	int row = 0; //�s
	int col = 0; //��
	StandbyEnemyDataStruct sta{};

	ifstream ifs(file_name);

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
				sta.flag = false; //�t���O��false
				sta.num = atoi(s.c_str()); //�ԍ���ݒ�
				sta.x = col * 32.0f + (enemy_data[sta.num].size_x * 4.0f); //x���W��ݒ�
				sta.y = row * 32.0f + 32.0f - (enemy_data[sta.num].size_y * 8.0f); //y���W��ݒ�
				standby_enemy.emplace_back(sta);
			}
			col++; //�񐔂𑝂₷
		}

		//�񐔂����Z�b�g���čs���𑝂₷
		col = 0;
		row++;
	}

	ifs.close();
}

//�G�̔z�u
shared_ptr<AbstractEnemy> EnemyManager::SetEnemy(int num, float ini_x, float ini_y, AbstractEnemy* base) {
	shared_ptr<AbstractEnemy> new_enemy;

	switch (enemy_data[num].type)
	{
	case 0:
		new_enemy = make_shared<NoMove>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 1:
		new_enemy = make_shared<Erhei1>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 2:
		new_enemy = make_shared<Erhei2>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 3:
		new_enemy = make_shared<Erhei3>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 4:
		new_enemy = make_shared<Erhei4>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 6:
		new_enemy = make_shared<Kurhei1>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 7:
		new_enemy = make_shared<Kurhei2>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 8:
		new_enemy = make_shared<Missile>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 9:
		new_enemy = make_shared<HomingMissile>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 10:
		new_enemy = make_shared<FallBomb>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 11:
		new_enemy = make_shared<FallBomb2>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 14:
		new_enemy = make_shared<Cannon1>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 15:
		new_enemy = make_shared<Cannon2>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 32:
		new_enemy = make_shared<DekaKurhei>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 33:
		new_enemy = make_shared<RaidCloud>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 34:
		new_enemy = make_shared<CloudBit>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 35:
		new_enemy = make_shared<Desdragud>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 36:
		new_enemy = make_shared<DesdragudArm>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	default:
		new_enemy = make_shared<NoMove>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	}

	new_enemy->SetHp(enemy_data[num].hp); //HP��ݒ�
	new_enemy->SetMaxHp(enemy_data[num].hp); //�ő�HP��ݒ�
	new_enemy->SetBase(base); //�{�̂�ݒ�
	new_enemy->SetBossFlag(enemy_data[num].rank); //�{�X����ݒ�

	//�i�ɂ���ăt���O�𗧂Ă�
	if (enemy_data[num].rank == 1) midboss_flag = true;
	if (2 <= enemy_data[num].rank){
		boss_flag = true;
		boss_battle = true;
	}

	enemy.emplace_back(new_enemy);

	return new_enemy;
}

//�G���o���ł��邩�m�F
void EnemyManager::SpawnCheck(shared_ptr<Camera> camera) {
	if (standby_enemy.size() == 0) return;
	float left = (float)camera->GetScrollX() - 64.0f; //��ʍ��[
	float right = (float)camera->GetScrollX() + (float)WINDOW_X + 64.0f; //��ʉE�[
	float top = (float)camera->GetScrollY() - 64.0f; //��ʏ�
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y + 64.0f; //��ʒ�

	for (unsigned int i = 0; i < standby_enemy.size(); i++) {
		int num = standby_enemy[i].num;
		float x = 4.0f * enemy_data[num].size_x; //����p
		float y = 4.0f * enemy_data[num].size_y; //����p

		//�G���o�����Ă��Ȃ��Ĕ͈͓��ɂ���Ȃ�
		if (!standby_enemy[i].flag && (0.0f < standby_enemy[i].x - left && standby_enemy[i].x - right < 0.0f && 0.0f < standby_enemy[i].y - top && standby_enemy[i].y - bottom < 0.0f)) {
			standby_enemy[i].flag = true; //�o���ς݂�
			SetEnemy(num, standby_enemy[i].x, standby_enemy[i].y); //�G���o��������
		}

		//�o���ς݂Ŕ͈͊O�ɂ���Ȃ�
		if (standby_enemy[i].flag && (4.0f * x < left - standby_enemy[i].x || 4.0f * x < standby_enemy[i].x - right || 4.0f * y < top - standby_enemy[i].y || 4.0f * y < standby_enemy[i].y - bottom)) {
			standby_enemy[i].flag = false; //�o�����Ă��Ȃ�������
		}
	}
}

//�L�����N�^�[�Ƃ̓����蔻��
bool EnemyManager::HitCheckChara(float cx, float cy, float hit_size, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, int damage) {
	for (auto &ene : enemy) {
		if (ene->GetHp() <= 0) continue; //HP��0�Ȃ��΂�
		if (ene->HitCheckChara(cx, cy, hit_size)) {
			if (0 < damage) {
				ene->HitDamage(damage, effect, sound);
			}
			return true;
		}
	}
	return false;
}

//�e�ɓ������Ă��邩
void EnemyManager::HitCheckBullet(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (enemy.size() == 0) return;

	for (auto &ene : enemy) {
		if (ene->GetEndFlag() || ene->GetHp() <= 0) continue; //�����邩HP��0�Ȃ��΂�
		ene->HitCheckBullet(bullet, effect, sound);
	}
}

//�G�ɓ������Ă��邩
void EnemyManager::HitCheckEnemy(std::shared_ptr<EffectManager> effect) {
	if (enemy.size() == 0) return;

	for (auto &ene : enemy) {
		float x = ene->GetX();
		float y = ene->GetY();
		for (auto &ene2 : enemy) {
			if (ene == ene2) continue; //�����Ȃ��΂�
			ene2->HitCheckEnemy(x, y, 32.0f, effect);
		}
	}
}

//�{�X�풆���擾
bool EnemyManager::GetBossFlag() {
	return (boss_flag || midboss_flag);
}

//�{�X��|�������擾
bool EnemyManager::GetBeatBoss() {
	return (boss_battle && !boss_flag);
}

//�X�V
void EnemyManager::Update(shared_ptr<MapChipManager> map, shared_ptr<BulletManager> bullet, shared_ptr<Player> player, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	if (enemy.empty()) {
		boss_flag = false;
		midboss_flag = false;
		return;
	}

	bool boss = false; //�{�X�����邩

	for (auto &ene : enemy) {
		ene->Update(player, bullet, effect, sound, camera); //���삷��

		ene->AbsUpdate();
		ene->Timer();
		
		ene->AdjustPosition(map, effect);
		
		if (ene->GetBossFlag()) boss = true; //�{�X������΃t���O��true
	}

	//�{�X�����Ȃ��Ȃ�{�X��t���O��false��
	if (!boss) {
		boss_flag = false;
		midboss_flag = false;
	}

	EraseCheck(camera); //�G���������m�F
}

//�`��
void EnemyManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	//if (0 < standby_enemy.size()) DrawFormatString(320, 128, GetColor(255, 0, 0), "%d %d %f", boss_flag, midboss_flag, standby_enemy.size());

	if (enemy.empty()) return;
	for (auto &ene : enemy) {
		//���G���Ԓ��͓_�ł���
		if (ene->GetDamaged()) {
			ene->SetTrance(192);
			
		} else {
			ene->SetTrance(256);
		}
		//�{�̂��Ȃ����̂̂ݕ`��(���͖{�̂ɔC����)
		if (ene->GetBase() == NULL) {
			ene->Draw(image, camera);
		}
		ene->DrawHit(camera);
	}
}