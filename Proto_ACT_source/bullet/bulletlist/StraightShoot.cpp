#pragma once
#include "DxLib.h"
#include "StraightShoot.h"

using namespace std;

//�R���X�g���N�^
StraightShoot::StraightShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.0f, 0.0f, 16.0f);
}

//�f�X�g���N�^
StraightShoot::~StraightShoot() {

}

//�K���s���X�V
void StraightShoot::AbsUpdate() {

}

//�����鎞�̓���
void StraightShoot::Erase(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	int effect_num = hit_player ? 4 : 3; //���@�ɓ����邩�ŃG�t�F�N�g��ݒ�
	effect->SetEffect(effect_num, x, y, 0.5f); //�G�t�F�N�g�𔭐�
}

//�X�V
void StraightShoot::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera){
	//��莞�Ԃ��ƂɃG�t�F�N�g�𔭐�
	if (time % 3 == 0 && 0 < time) {
		int effect_num = hit_player ? 9 : 8; //���@�ɓ����邩�ŃG�t�F�N�g��ݒ�
		effect->SetEffect(effect_num, x, y, 0.2f); //�G�t�F�N�g�𔭐�
	}
}

//�`��
void StraightShoot::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetBulletImage(image_num, 0);
	camera->Draw(x, y, false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}