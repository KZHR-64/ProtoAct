#pragma once
#include "DxLib.h"
#include "BreakBlast.h"

using namespace std;

//�R���X�g���N�^
BreakBlast::BreakBlast(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.0f, 0.0f, 8.0f);
}

//�f�X�g���N�^
BreakBlast::~BreakBlast() {

}

//�K���s���X�V
void BreakBlast::AbsUpdate() {

}

//�����鎞�̓���
void BreakBlast::Erase(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {

}

//�X�V
void BreakBlast::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//���Œ��O�Ŕ��肪��������
	if (end_time == 2) {
		hit_map = true;
	}
}

//�`��
void BreakBlast::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
}