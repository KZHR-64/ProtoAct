#pragma once
#include "DxLib.h"
#include "Aura.h"

using namespace std;

//�R���X�g���N�^
Aura::Aura(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.0f, 0.0f, 48.0f);
}

//�f�X�g���N�^
Aura::~Aura() {

}

//�K���s���X�V
void Aura::AbsUpdate() {

}

//�����鎞�̓���
void Aura::Erase(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {

}

//�X�V
void Aura::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

}

//�`��
void Aura::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetBulletImage(image_num, 0);
	camera->Draw(x, y, false, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, 192);
}