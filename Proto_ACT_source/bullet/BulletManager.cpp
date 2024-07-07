#pragma once
#include "DxLib.h"
#include "BulletManager.h"
#include "bulletlist/StraightShoot.h"
#include "bulletlist/ControlShoot.h"
#include "bulletlist/RocketHand.h"
#include "bulletlist/Aura.h"
#include "bulletlist/BreakBlast.h"
#include "bulletlist/LockShoot.h"
#include "bulletlist/BombBlast.h"

using namespace std;

BulletManager::BulletManager(){
	SetData();
}

BulletManager::~BulletManager(){
	bullet.clear();
	bullet_data.clear();
}

//������
void BulletManager::Reset(){
	bullet.clear();
}

//�e���̐ݒ�
void BulletManager::SetData() {
	int num;
	ifstream ifs("data/bullet/bullet_data.csv");

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
		bullet_data[num].type = atoi(s.c_str()); //��ނ��擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		bullet_data[num].image = atoi(s.c_str()); //�摜�̔ԍ����擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		bullet_data[num].breakable = (1 == atoi(s.c_str())); //�󂹂邩���擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		bullet_data[num].hit_player = (1 == atoi(s.c_str())); //���@�ɓ����邩���擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		bullet_data[num].hit_enemy = (1 == atoi(s.c_str())); //�G�ɓ����邩���擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		bullet_data[num].hit_map = (1 == atoi(s.c_str())); //�}�b�v�`�b�v�ɓ����邩���擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		bullet_data[num].damage = atoi(s.c_str()); //�_���[�W�l���擾��
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		bullet_data[num].break_power = atoi(s.c_str()); //�󂷗͂��擾
	}
	ifs.close();

}

//�����邩�m�F
void BulletManager::EraseCheck(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	if (bullet.empty()) return;
	float left = (float)camera->GetScrollX(); //��ʍ��[
	float right = (float)camera->GetScrollX() + (float)WINDOW_X; //��ʉE�[
	float top = (float)camera->GetScrollY(); //��ʏ�
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y; //��ʒ�

	for (auto bul = bullet.begin(); bul != bullet.end();) {
		bool erase_flag; //������t���O
		float x = (*bul)->GetX();
		float y = (*bul)->GetY();
		int end_time = (*bul)->GetEndTime(); //������܂ł̎���
		
		//��ʊO�Ȃ����
		erase_flag = (x < left - 64.0f || right + 64.0f < x || y < top - 64.0f || bottom + 64.0f < y);

		//������܂ł̎��Ԃ�0���傫���Ȃ�
		if (0 < end_time) {
			end_time--; //���Ԃ����炷
			//���Ԃ�0�ɂȂ����������
			if (end_time <= 0) erase_flag = true;
			(*bul)->SetEndTime(end_time); //���Ԃ�ݒ�
		}

		//�����t���O��true�Ȃ����
		if ((*bul)->GetEndFlag() || erase_flag) {
			//��ʊO�ɂ����łłȂ����
			if (!erase_flag) {
				(*bul)->Erase(effect, sound); //������Ƃ��̓���
			}
			bul = bullet.erase(bul);
		}
		else {
			bul++;
		}
	}
}

//�e�̔z�u
shared_ptr<AbstractBullet> BulletManager::SetBullet(int num, float ini_x, float ini_y, float speed, float angle) {
	shared_ptr<AbstractBullet> new_bullet;

	switch (bullet_data[num].type)
	{
	case 0:
		new_bullet = make_shared<StraightShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 1:
		new_bullet = make_shared<ControlShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 2:
		new_bullet = make_shared<RocketHand>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 3:
		new_bullet = make_shared<Aura>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 4:
		new_bullet = make_shared<BreakBlast>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 5:
		new_bullet = make_shared<LockShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 8:
		new_bullet = make_shared<BombBlast>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	default:
		new_bullet = make_shared<StraightShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	}

	new_bullet->SetDamage(bullet_data[num].damage); //�_���[�W�l��ݒ�
	new_bullet->SetBreakable(bullet_data[num].breakable); //�󂹂邩�ݒ�
	new_bullet->SetHitPlayer(bullet_data[num].hit_player); //���@�ɓ����邩�ݒ�
	new_bullet->SetHitEnemy(bullet_data[num].hit_enemy); //�G�ɓ����邩�ݒ�
	new_bullet->SetHitMap(bullet_data[num].hit_map); //�}�b�v�`�b�v�ɓ����邩�ݒ�
	new_bullet->SetBreakPower(bullet_data[num].break_power); //�}�b�v�`�b�v���󂷗͂�ݒ�

	bullet.emplace_back(new_bullet);
	
	return new_bullet;
}

//�}�b�v�`�b�v�Ƃ̓����蔻��
void BulletManager::HitCheckMap(shared_ptr<MapChipManager> map) {
	if (bullet.empty()) return;
	for (auto &bul : bullet) {
		if (!bul->GetHitMap()) continue;
		bul->HitCheckMap(map);
	}
}

//�L�����N�^�[�Ƃ̓����蔻��
int BulletManager::HitCheckChara(float cx, float cy, float hit_size, bool check_player, bool check_enemy) {
	int damage = 0; //�_���[�W�l
	for (auto &bul : bullet) {
		if (!((check_player && bul->GetHitPlayer()) || (check_enemy && bul->GetHitEnemy()))) continue;
		int bullet_damage = bul->HitCheckChara(cx, cy, hit_size); //�_���[�W�l
		//�_���[�W�l������A�O�̂��̂��傫���Ȃ�
		if (damage < bullet_damage) {
			damage = bullet_damage; //�_���[�W�l���X�V
		}
	}
	return damage;
}

//�X�V
void BulletManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera){
	if (bullet.empty()) return;
	for (auto &bul : bullet) {
		
		bul->Update(player, enemy, item, effect, key, sound, camera);
		
		bul->SetX(bul->GetX() + bul->GetXSpeed());
		bul->SetY(bul->GetY() + bul->GetYSpeed());
		int time = bul->GetTime();
		time++;
		bul->SetTime(time);
		bul->HitUpdate();
	}

	EraseCheck(effect, sound, camera); //�e���������m�F
}

//�`��
void BulletManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	if (bullet.empty()) return;
	for (auto &bul : bullet) {
		bul->Draw(image, camera);
		bul->DrawHit(camera);
	}
	//DrawFormatString(64, 96, GetColor(255, 255, 255), "%d", bullet.size());
}