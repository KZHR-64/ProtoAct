#pragma once
#include "DxLib.h"
#include "BombBlast.h"

using namespace std;

//�R���X�g���N�^
BombBlast::BombBlast(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.0f, 0.0f, 32.0f);
	end_time = 30;
	dx = 0.0f;
	dy = 12.0f;
}

//�f�X�g���N�^
BombBlast::~BombBlast() {

}

//�K���s���X�V
void BombBlast::AbsUpdate() {

}

//�����鎞�̓���
void BombBlast::Erase(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {

}

//�X�V
void BombBlast::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	if (time == 0) {
		sound->PlaySoundEffect(16); //���ʉ���炷
	}

	//��莞�Ԃ��Ƃɕ`��ʒu��ύX
	if (time % 3 == 0) {
		dx = (24.0f * (time % 2)) - 12.0f; //�������W
	}
}

//�`��
void BombBlast::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetBulletImage(image_num, 0);
	camera->Draw(x, y, false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	camera->Draw(x + dx, y + dy, false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	camera->Draw(x - dx, y - dy, false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}