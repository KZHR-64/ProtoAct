#pragma once
#include "DxLib.h"
#include "SpinMassDriver.h"

using namespace std;

//�R���X�g���N�^
SpinMassDriver::SpinMassDriver(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	loaded = false;
	fire_time = 0;
	hit_flag = false;
}

//�f�X�g���N�^
SpinMassDriver::~SpinMassDriver() {

}

//�K���s���X�V
void SpinMassDriver::AbsUpdate() {

}

//�X�V
void SpinMassDriver::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	//���@�̍��W���擾
	float px = player->GetX();
	float py = player->GetY();

	//���@�������Ă���Ȃ�
	if (loaded) {
		player->SetX(x); //���@�̍��W��ݒ�
		player->SetY(y + (4.0f * size_y));
		//�W�����v�{�^���������ꂽ�Ȃ�
		if (key->KeyCheckOnce(Attack)) {
			shared_ptr<AbstractEffect> eff;
			float x_speed = 12.0f * cosf(angle); //x�����̑��x��ݒ�
			float y_speed = 12.0f * sinf(angle); //y�����̑��x��ݒ�
			float eff_x = x + 48.0f * cosf(angle); //�G�t�F�N�g�̈ʒu��ݒ�
			float eff_y = y + (4.0f * size_y) + 48.0f * sinf(angle);
			player->SetXSpeed(x_speed); //���@�̑��x��ݒ�
			player->SetYSpeed(y_speed);
			player->SetSpinSpeed(0.05f * PI); //��]���x��ݒ�
			player->SetDrawFlag(true); //���@�̕\�����s��
			loaded = false; //���@����ꂽ��Ԃ�false��
			fire_time = 18; //���΂炭�͎��@�����Ȃ�
			eff = effect->SetEffect(2, eff_x, eff_y, 0.7f); //�G�t�F�N�g�𔭐�
			eff->SetAngle(angle + (0.5f * PI)); //�p�x��ݒ�
			sound->PlaySoundEffect(16); //���ʉ���炷
		}
	}
	//�����Ă��Ȃ��Ȃ�
	else {
		//���@���߂��Ȃ�
		if (fabsf(px - x) < 24.0f + (4.0f * size_x) && fabsf(py - y - (4.0f * size_y)) < 4.0f * size_y && fire_time == 0) {
			loaded = true; //���@����������Ԃ�
			player->SetXSpeed(0.0f); //���@�̑��x��0��
			player->SetYSpeed(0.0f);
			player->SetFlying(true); //���@���s��Ԃ�
			player->SetDrawFlag(false); //���@�̕\�����s��Ȃ�
			player->SetMoveFlag(false); //���@�𑀍�s��
		}
		//����������Ȃ�
		if (0 < fire_time) {
			fire_time--; //���Ԃ�����
		}
	}

	//��莞�Ԃ��Ƃɉ�]
	if(time % 30 == 0) {
		angle += 0.25f * PI;
	}
}

//�`��
void SpinMassDriver::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetMapchipImage(image_num);
	//�摜�̑傫�����擾
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);

	camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);

	//���@�������Ă���Ȃ甭�ˎw����\��
	if (loaded && time % 60 < 30) {
		int ehundle = image->GetEffectImage(15, 0);
		camera->Draw(x + 32.0f, y - 32.0f, false, 0.0f, ehundle, 1.0f, DX_BLENDMODE_NOBLEND);
	}
}