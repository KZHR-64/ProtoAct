#pragma once
#include "DxLib.h"
#include "Erhei2.h"

using namespace std;

//�R���X�g���N�^
Erhei2::Erhei2(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 32.0f);
}

//�f�X�g���N�^
Erhei2::~Erhei2() {

}

//�K���s���X�V
void Erhei2::AbsUpdate() {

}

//���ꂽ���̓���
void Erhei2::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //������
	effect->SetEffect(1, x, y); //����
}

//�X�V
void Erhei2::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	float px = player->GetX(); //���@�̍��W
	//���@�̂������������
	reverse = px < x;

	//��莞�Ԃ��Ƃɒe������
	if (time % 120 == 0 && 0 < time) {
		float shoot_x = (reverse ? -8.0f : 8.0f); //�e��
		float shoot_angle = (reverse ? PI : 0.0f); //�����ɂ���Č��p�x������
		bullet->SetBullet(5, x + shoot_x, y - 12.0f, 6.0f, shoot_angle); //�e�𔭎�
		sound->PlaySoundEffect(7); //���ʉ���炷
	}
}

//�`��
void Erhei2::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	int arm_hundle = image->GetCharaImage(5, 0);
	float arm_x = (reverse) ? 16.0f : -16.0f; //�����ɉ����ĕ���̈ʒu��ݒ�

	camera->Draw(x - arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x + arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}