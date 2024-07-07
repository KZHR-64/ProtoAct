#pragma once
#include "DxLib.h"
#include "Missile.h"

using namespace std;

//�R���X�g���N�^
Missile::Missile(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(8.0f, 0.0f, 8.0f);
	SetHit(-8.0f, 0.0f, 8.0f);

	reverse = false;
	flying_flag = true;
}

//�f�X�g���N�^
Missile::~Missile() {

}

//�K���s���X�V
void Missile::AbsUpdate() {
}

//���ꂽ���̓���
void Missile::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //������
	effect->SetEffect(1, x, y, 0.5f); //����
}

//�X�V
void Missile::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	//���n�����甚��
	if (0 < time && adjusted) {
		Defeat(effect, sound);
	}

	//��莞�Ԃ��ƂɃG�t�F�N�g�𔭐�
	if (time % 12 == 0) {
		shared_ptr <AbstractEffect> eff;
		float ex = x + -16.0f * cosf(angle);
		float ey = y + -16.0f * sinf(angle);
		eff = effect->SetEffect(10, ex, ey, 0.3f);
		eff->SetAngle(angle - 0.5f * PI);
	}
}

//�`��
void Missile::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}