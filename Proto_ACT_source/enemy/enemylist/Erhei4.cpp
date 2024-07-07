#pragma once
#include "DxLib.h"
#include "Erhei4.h"

using namespace std;

//�R���X�g���N�^
Erhei4::Erhei4(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 32.0f);
}

//�f�X�g���N�^
Erhei4::~Erhei4() {

}

//�K���s���X�V
void Erhei4::AbsUpdate() {

}

//���ꂽ���̓���
void Erhei4::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //������
	effect->SetEffect(1, x, y); //����
}

//�X�V
void Erhei4::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	//��莞�Ԍo�߂��Ă��Ȃ��Ȃ�
	if (time < 120) {
		float px = player->GetX(); //���@�̍��W
		//���@�̂������������
		reverse = px < x;
	}
	//��莞�Ԍo�߂�����
	else
	{
		float max_speed = (reverse) ? -12.0f : 12.0f;
		if (fabsf(sx) < 0.5f) {
			//���x��ݒ�
			sx = (reverse) ? -1.0f : 1.0f;
		}
		sx *= 1.05f;  //���X�ɉ���
		//�����ݒ�
		if (fabsf(max_speed) < fabsf(sx)) {
			sx = max_speed;
		}
	}
}

//�`��
void Erhei4::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	int arm_hundle = image->GetCharaImage(7, 0);
	float arm_x = (reverse) ? 16.0f : -16.0f; //�����ɉ����ĕ���̈ʒu��ݒ�

	camera->Draw(x - arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x + arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}