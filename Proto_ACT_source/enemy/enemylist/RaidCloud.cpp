#pragma once
#include "DxLib.h"
#include "RaidCloud.h"

using namespace std;

//�R���X�g���N�^
RaidCloud::RaidCloud(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	shared_ptr<AbstractEnemy> cbit;

	flying_flag = true;
	pattern = 2; //�p�^�[����2����
	parts_num = 12;
	parts_distance = 142.0f;
	parts_angle = 0.0f;
	hit_map = false;

	SetHit(0.0f, 0.0f, 64.0f);

	//�p�[�c�𐶐�
	for (int i = 0; i < parts_num; i++) {
		float pangle = 2.0f * PI * ((float)i / parts_num); //�p�x
		float px = x + parts_distance * cosf(pangle);//�z�u������W
		float py = y + parts_distance * sinf(pangle);
		cbit = manager->SetEnemy(34, px, py);
		parts.emplace_back(cbit);
	}

	AbsUpdate();
}

//�f�X�g���N�^
RaidCloud::~RaidCloud() {

}

//�U��1�i�΂�܂��j
void RaidCloud::Pattern1(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	
	//�p�[�c��������]������
	if (60 < time && time < 240) {
		float direction = (reverse) ? -1.0f : 1.0f; //�����ɉ������v�Z�p
		parts_angle += (0.025f * PI);
	}
	//��莞�Ԃ��Ƃɒe������
	if (120 < time && time < 240 && time % 6 == 0) {
		shared_ptr<AbstractBullet> bul;
		for (int i = 0; i < parts_num; i++) {
			float pangle = parts_angle + 2.0f * PI * ((float)i / parts_num); //�p�x
			float px = parts[i]->GetX();//�z�u������W
			float py = parts[i]->GetY();
			bul = bullet->SetBullet(5, px, py, 8.0f, pangle); //�e�𔭎�
			bul->SetEndTime(30); //������܂ł̎��Ԃ�ݒ�
		}
		sound->PlaySoundEffect(7); //���ʉ���炷
	}

	//��莞�Ԍo������
	if (300 <= time) {
		pattern = 3; //�p�^�[����3��
		time = 0; //���Ԃ�������
	}
}

//�U��2�i�ːi�j
void RaidCloud::Pattern2(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float left = (float)camera->GetScrollX() + 160.0f; //���[
	float right = (float)camera->GetScrollX() + (float)WINDOW_X - 160.0f; //�E�[
	float top = (float)camera->GetScrollY() + 416.0f; //��
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y - 96.0f; //��

	//���x��ݒ�
	if (time == 60) {
		float center = (float)camera->GetScrollX() + ((float)WINDOW_X / 2.0f); //���S
		sx = (center < x) ? 2.0f : -2.0f; //�ʒu�ɉ����đ��x��ݒ�
		sy = 0.0f; //���x��ݒ�
		return;
	}
	if (time < 90) return;
	if (time == 90) {
		sx = 0.0f; //���x��ݒ�
		sy = 8.0f;
		return;
	}

	//�p�[�c��������]������
	parts_angle += (0.025 * PI);

	//��ɋ߂��Ȃ�����
	if (bottom < y && fabsf(sx) < 0.1f && 0.0f < sy) {
		float center = (float)camera->GetScrollX() + ((float)WINDOW_X / 2.0f); //���S
		y = bottom; //�ʒu�𒲐�
		sy = 0.0f; //���x��ݒ�
		sx = (center < x) ? -10.0f : 10.0f; //�ʒu�ɉ����đ��x��ݒ�
	}
	//���ɋ߂��Ȃ�����
	else if (fabsf(x - left) < 8.0f && sx < 0.0f && fabsf(y - bottom) < 1.0f) {
		x = left; //�ʒu�𒲐�
		sx = 0.0f; //���x��ݒ�
		sy = -8.0f;
	}
	//�E�ɋ߂��Ȃ�����
	else if (fabsf(x - right) < 8.0f && 0.0f < sx && fabsf(y - bottom) < 1.0f) {
		x = right; //�ʒu�𒲐�
		sx = 0.0f; //���x��ݒ�
		sy = -8.0f;
	}
	//��ɋ߂��Ȃ�����
	else if (fabsf(y - top) < 8.0f && fabsf(sx) < 0.1f && sy < 0.0f) {
		y = top; //�ʒu�𒲐�
		sy = 0.0f; //���x��ݒ�
		pattern = 3; //�p�^�[����3��
		time = 0; //���Ԃ�������
	}
}

//�U��3�i��ړ��j
void RaidCloud::Pattern3(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float left = (float)camera->GetScrollX() + 160.0f; //���[
	float right = (float)camera->GetScrollX() + (float)WINDOW_X - 160.0f; //�E�[
	float top = (float)camera->GetScrollY() + 128.0f; //��
	float bottom = (float)camera->GetScrollY() + 416.0f; //��

	//���x��ݒ�
	if (time == 60) {
		sx = 0.0f; //���x��ݒ�
		sy = -8.0f;
		return;
	}
	if (time < 60) return;

	//�p�[�c��������]������
	parts_angle += (0.025f * PI);

	//��ɋ߂��Ȃ�����
	if (y < top && fabsf(sx) < 0.1f && sy < 0.0f) {
		float center = (float)camera->GetScrollX() + ((float)WINDOW_X / 2.0f); //���S
		y = top; //�ʒu�𒲐�
		sy = 0.0f; //���x��ݒ�
		sx = (center < x) ? -10.0f : 10.0f; //�ʒu�ɉ����đ��x��ݒ�
	}
	//���ɋ߂��Ȃ�����
	else if (fabsf(x - left) < 8.0f && sx < 0.0f && fabsf(y - top) < 1.0f) {
		x = left; //�ʒu�𒲐�
		sx = 0.0f; //���x��ݒ�
		sy = 8.0f;

		//�e������
		for (int i = 0; i < parts_num; i++) {
			float pangle = parts_angle + 2.0f * PI * ((float)i / parts_num); //�p�x
			float px = parts[i]->GetX();//�z�u������W
			float py = parts[i]->GetY();
			bullet->SetBullet(6, px, py, 8.0f, pangle); //�e�𔭎�
		}
		sound->PlaySoundEffect(7); //���ʉ���炷
	}
	//�E�ɋ߂��Ȃ�����
	else if (fabsf(x - right) < 8.0f && 0.0f < sx && fabsf(y - top) < 1.0f) {
		x = right; //�ʒu�𒲐�
		sx = 0.0f; //���x��ݒ�
		sy = 8.0f;

		//�e������
		for (int i = 0; i < parts_num; i++) {
			float pangle = parts_angle + 2.0f * PI * ((float)i / parts_num); //�p�x
			float px = parts[i]->GetX();//�z�u������W
			float py = parts[i]->GetY();
			bullet->SetBullet(6, px, py, 8.0f, pangle); //�e�𔭎�
		}
		sound->PlaySoundEffect(7); //���ʉ���炷
	}
	//��ɋ߂��Ȃ�����
	else if (fabsf(bottom - y) < 8.0f && fabsf(sx) < 0.1f && 0.0f < sy) {
		y = bottom; //�ʒu�𒲐�
		sy = 0.0f; //���x��ݒ�
		pattern = 3; //�p�^�[����3��
		time = 0; //���Ԃ�������
	}
}

//�K���s���X�V
void RaidCloud::AbsUpdate() {
	float direction = (reverse) ? -1.0f : 1.0f; //�����ɉ������v�Z�p

	//�p�[�c�̈ʒu��ݒ�
	for (int i = 0; i < parts_num; i++) {
		float pangle = parts_angle + 2.0f * PI * ((float)i / parts_num); //�p�x
		float px = x + parts_distance * cosf(pangle);//�z�u������W
		float py = y + parts_distance * sinf(pangle);
		parts[i]->SetX(px);
		parts[i]->SetY(py);
	}
}

//���ꂽ���̓���
void RaidCloud::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_time = 60; //������܂ł̎��Ԃ�ݒ�
	sy = 0.5f;
}

//�X�V
void RaidCloud::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//������܂ł̎��Ԃ��ݒ肳��Ă���Ȃ�
	if (end_time != -1) {
		//�����鐡�O�Ȃ�
		if (end_time == 1) {
			end_flag = true; //������
			effect->SetEffect(1, x, y, 2.0f); //����
		}
		//������O�Ȃ�
		else if (end_time % 12 == 0) {
			effect->SetEffect(2, x, y - 64.0f); //��
		}
		return; //�I��
	}

	//�U���p�^�[���ɂ���čs����ύX
	switch (pattern)
	{
	case 0:
		Pattern1(player, bullet, effect, sound, camera);
		break;
	case 1:
		Pattern2(player, bullet, effect, sound, camera);
		break;
	case 2:
		Pattern3(player, bullet, effect, sound, camera);
		break;
	default:
		//��莞�Ԍo������p�^�[����ύX
		if (60 <= time) {
			pattern = GetRand(3);
			time = 0; //���Ԃ�������
		}
		break;
	}

}

//�`��
void RaidCloud::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

	int hundle = image->GetCharaImage(image_num, 0);

	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}