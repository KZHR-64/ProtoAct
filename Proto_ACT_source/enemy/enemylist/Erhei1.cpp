#pragma once
#include "DxLib.h"
#include "Erhei1.h"

using namespace std;

//�R���X�g���N�^
Erhei1::Erhei1(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 32.0f);
}

//�f�X�g���N�^
Erhei1::~Erhei1() {

}

//�K���s���X�V
void Erhei1::AbsUpdate() {

}

//���ꂽ���̓���
void Erhei1::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //������
	effect->SetEffect(1, x, y); //����
}

//�X�V
void Erhei1::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//�o�Ă��Ă����Ȃ�
	if (time == 0) {
		float px = player->GetX(); //���@�̍��W
		//���@�̂������������
		reverse = px < x;
		sx = (reverse) ? -4.0f : 4.0f; //�����ɉ����đ��x��ݒ�
	}

	//�ǂɓ���������
	if (adjusted && sx == 0.0f) {
		reverse = !reverse; //�����𔽓]
		sx = (reverse) ? -4.0f : 4.0f; //�����ɉ����đ��x��ݒ�
	}
}

//�`��
void Erhei1::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	int arm_hundle = image->GetCharaImage(5, 0);
	float arm_x = (reverse) ? 16.0f : -16.0f; //�����ɉ����ĕ���̈ʒu��ݒ�

	camera->Draw(x - arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x + arm_x, y - 12.0f, reverse, angle, arm_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}