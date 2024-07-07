#pragma once
#include "DxLib.h"
#include "LockShoot.h"

using namespace std;

//�R���X�g���N�^
LockShoot::LockShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.0f, 0.0f, 16.0f);
}

//�f�X�g���N�^
LockShoot::~LockShoot() {

}

//�K���s���X�V
void LockShoot::AbsUpdate() {

}

//�����鎞�̓���
void LockShoot::Erase(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	effect->SetEffect(9, x, y, 0.5f); //�G�t�F�N�g�𔭐�
}

//�X�V
void LockShoot::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//���@��_��
	if (time == 0) {
		float lock = Calculation::LockOn(x, y, player->GetX(), player->GetY());
		sx = base_speed * cosf(lock);
		sy = base_speed * sinf(lock);
	}
	//��莞�Ԃ��ƂɃG�t�F�N�g�𔭐�
	if (time % 3 == 0 && 0 < time) {
		effect->SetEffect(9, x, y, 0.2f); //�G�t�F�N�g�𔭐�
	}
}

//�`��
void LockShoot::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetBulletImage(image_num, 0);
	camera->Draw(x, y, false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}