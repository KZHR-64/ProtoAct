#pragma once
#include "DxLib.h"
#include "Cannon2.h"

using namespace std;

//�R���X�g���N�^
Cannon2::Cannon2(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 24.0f);

	barrel_angle = 1.5f * PI;
	AbsUpdate();
}

//�f�X�g���N�^
Cannon2::~Cannon2() {

}

//�K���s���X�V
void Cannon2::AbsUpdate() {
	float direction = (reverse) ? 1.0f : -1.0f; //�����ɉ������v�Z�p
	barrel_x = x + ((-16.0f * cosf(angle + barrel_angle) * direction));
	barrel_y = y + (16.0f * sinf(angle + barrel_angle));
}

//���ꂽ���̓���
void Cannon2::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //������
	effect->SetEffect(1, x, y); //����
}

//�X�V
void Cannon2::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float px = player->GetX(); //���@�̍��W
	float py = player->GetY(); //���@�̍��W

	//���@����]�̒��S����Ȃ�
	if (py <= y + 8.0f) {
		//�ǔ�
		barrel_angle = Calculation::HomingSpin(barrel_angle, 0.0125f * PI, x, y, px, py);
	}

	//��莞�Ԃ��Ƃɒe������
	if (time % 120 == 0 && 0 < time) {
		//�e�̈ʒu��ݒ�
		float direction = (reverse) ? -1.0f : 1.0f; //�����ɉ������v�Z�p
		float bx = x + ((-32.0f * cosf(barrel_angle) * direction));
		float by = y + (32.0f * sinf(barrel_angle));

		bullet->SetBullet(5, bx, by, 12.0f, barrel_angle); //�e�𔭎�
		sound->PlaySoundEffect(7); //���ʉ���炷
	}
}

//�`��
void Cannon2::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	int barrel_hundle = image->GetCharaImage(image_num, 1);
	camera->Draw(barrel_x, barrel_y, false, barrel_angle, barrel_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}