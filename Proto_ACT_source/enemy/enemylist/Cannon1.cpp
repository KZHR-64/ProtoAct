#pragma once
#include "DxLib.h"
#include "Cannon1.h"

using namespace std;

//�R���X�g���N�^
Cannon1::Cannon1(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 24.0f);
}

//�f�X�g���N�^
Cannon1::~Cannon1() {

}

//�K���s���X�V
void Cannon1::AbsUpdate() {

}

//���ꂽ���̓���
void Cannon1::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //������
	effect->SetEffect(1, x, y); //����
}

//�X�V
void Cannon1::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	//��莞�Ԃ��Ƃɒe������
	if (time % 120 == 0 && 0 < time) {
		bullet->SetBullet(5, x, y - 32.0f, 12.0f, -0.5f * PI); //�e�𔭎�
		sound->PlaySoundEffect(7); //���ʉ���炷
	}
}

//�`��
void Cannon1::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	int barrel_hundle = image->GetCharaImage(image_num, 1);
	camera->Draw(x, y - 16.0f, false, -0.5f * PI, barrel_hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}