#pragma once
#include "DxLib.h"
#include "ControlShoot.h"

using namespace std;

//�R���X�g���N�^
ControlShoot::ControlShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.0f, 0.0f, 16.0f);
	control_flag = true;
}

//�f�X�g���N�^
ControlShoot::~ControlShoot() {

}

//�K���s���X�V
void ControlShoot::AbsUpdate() {

}

//�����鎞�̓���
void ControlShoot::Erase(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	effect->SetEffect(3, x, y, 0.5f); //�G�t�F�N�g�𔭐�
}

//�X�V
void ControlShoot::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//��莞�Ԃ��ƂɃG�t�F�N�g�𔭐�
	if (time % 6 == 0 && 0 < time) {
		int effect_num = hit_player ? 9 : 8; //���@�ɓ����邩�ŃG�t�F�N�g��ݒ�
		effect->SetEffect(effect_num, x, y, 0.2f); //�G�t�F�N�g�𔭐�
	}

	if (!control_flag) return; //�R���g���[������Ă��Ȃ���Ζ߂�

	//�オ�����ꂽ��
	if (key->KeyCheckOnce(Up)) {
		angle = -0.5f * PI; //�p�x���������
	}
	//���������ꂽ��
	if (key->KeyCheckOnce(Down)) {
		angle = 0.5f * PI; //�p�x����������
	}
	//�E�������ꂽ��
	if (key->KeyCheckOnce(Right)) {
		angle = 0.0f; //�p�x���E������
	}
	//���������ꂽ��
	if (key->KeyCheckOnce(Left)) {
		angle = PI; //�p�x����������
	}

	//�U���{�^���������ꂽ��
	if (!key->KeyCheck(Attack)) {
		control_flag = false; //����t���O��false��
	}

	SetSpeed(base_speed); //���x��ݒ�
}

//�`��
void ControlShoot::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetBulletImage(image_num, 0);
	camera->Draw(x, y, false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}