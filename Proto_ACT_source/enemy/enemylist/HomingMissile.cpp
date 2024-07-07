#pragma once
#include "DxLib.h"
#include "HomingMissile.h"

using namespace std;

//�R���X�g���N�^
HomingMissile::HomingMissile(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(16.0f, 0.0f, 16.0f);
	SetHit(-16.0f, 0.0f, 16.0f);

	reverse = false;
	flying_flag = true;
}

//�f�X�g���N�^
HomingMissile::~HomingMissile() {

}

//�K���s���X�V
void HomingMissile::AbsUpdate() {
}

//���ꂽ���̓���
void HomingMissile::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //������
	effect->SetEffect(1, x, y); //����
}

//�X�V
void HomingMissile::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float px = player->GetX(); //���@�̍��W
	float py = player->GetY(); //���@�̍��W

	//���n�����甚��
	if (0 < time && adjusted) {
		Defeat(effect, sound);
	}

	if (30 < time && time < 300) {
		angle = Calculation::HomingSpin(angle, 0.01f * PI, x, y, px, py); //���@��ǔ�
	}
	//���x��ݒ�
	SetSpeed(4.0f);
}

//�`��
void HomingMissile::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}