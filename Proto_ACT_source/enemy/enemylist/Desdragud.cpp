#pragma once
#include "DxLib.h"
#include "Desdragud.h"

using namespace std;

//�R���X�g���N�^
Desdragud::Desdragud(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	shared_ptr<AbstractEnemy> arm;

	flying_flag = true;
	pattern = 0; //�p�^�[����0����
	move_flag = true; //�܂��͈ړ�
	hit_map = false;
	reverse = true;

	SetHit(0.0f, 0.0f, 64.0f);
	SetHit(112.0f, -32.0f, 32.0f);

	head_angle = atan2f(-34.0f, 118.0f);
	head_distance = sqrtf((34.0f * 34.0f) + (118.0f * 118.0f));
	arm1_angle = atan2f(-48.0f, 24.0f);
	arm1_distance = sqrtf((48.0f * 48.0f) + (24.0f * 24.0f));
	arm1_spin_angle = atan2f(0.0f, 72.0f);
	arm1_spin_distance = sqrtf(72.0f * 72.0f);
	arm2_angle = atan2f(-48.0f, 24.0f);
	arm2_distance = sqrtf((48.0f * 48.0f) + (24.0f * 24.0f));
	arm2_spin_angle = atan2f(0.0f, 72.0f);
	arm2_spin_distance = sqrtf(72.0f * 72.0f);
	leg1_angle = atan2f(48.0f, 16.0f);
	leg1_distance = sqrtf((48.0f * 48.0f) + (16.0f * 16.0f));
	leg2_angle = atan2f(48.0f, 16.0f);
	leg2_distance = sqrtf((48.0f * 48.0f) + (16.0f * 16.0f));
	
	//�r
	arm = ene->SetEnemy(36, x, y, this);
	parts.emplace_back(arm);
	arm = ene->SetEnemy(36, x, y, this);
	parts.emplace_back(arm);

	AbsUpdate();
}

//�f�X�g���N�^
Desdragud::~Desdragud() {

}

//�U��1�i�o���A�ƃ~�T�C���j
void Desdragud::Pattern1(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	
	parts[0]->SetAngle(0.25 * PI);
	parts[1]->SetAngle(0.25 * PI);

	//��莞�Ԃ��Ƃɒe������
	if (90 <= time % 120 && time % 6 == 0) {
		manager->SetEnemy(11, x, y - 64.0f);
		sound->PlaySoundEffect(9); //���ʉ���炷
	}

	//��莞�Ԍo������
	if (240 < time) {
		pattern = 3; //�p�^�[����3��
		time = 0; //���Ԃ�������
	}
}

//�U��2�i�~�T�C���Ǝ��@�_���j
void Desdragud::Pattern2(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	float dy = (float)camera->GetScrollY() + 224.0f; //�ړI�n
	float px = player->GetX(); //���@�̍��W
	float py = player->GetY(); //���@�̍��W
	float direction = (reverse) ? -1.0f : 1.0f; //�����ɉ������v�Z�p

	float aangle; //�r�̊p�x
	float parts_dx; //�p�[�c�̉�]�̖ڕW�ƂȂ�x���W

	//��ʒu�Ɉړ�����Ȃ�
	if (move_flag) {
		//��ʒu�Ɉړ�
		float sangle = atan2f(dy - y, 0); //��ʒu�ւ̊p�x���擾
		sx = 8.0f * cosf(sangle);
		sy = 8.0f * sinf(sangle);
		//�߂��Ȃ�
		if (fabsf(dy - y) < 16.0f) {
			sx = 0.0f;
			sy = 0.0f;
			move_flag = false; //�ړ����I��
		}
		return;
	}

	parts[0]->SetAngle(0.25 * PI);

	//���@�Ɍ����r����]
	if (60 < time % 240 && time % 240 < 120) {
		aangle = parts[1]->GetAngle();
		parts_dx = (reverse) ? px + ((parts[1]->GetX() - px) * 2.0f) : px;
		aangle = Calculation::HomingSpin(aangle, (3.0f / 180.0f) * PI, parts[1]->GetX(), parts[1]->GetY(), parts_dx, py);
		parts[1]->SetAngle(aangle);
	}
	if (150 < time % 240 && time % 240 < 210 && time % 3 == 0) {
		aangle = parts[1]->GetAngle();
		float sangle = (reverse) ? (PI) - aangle : aangle; //�����ɉ����Ēe�̊p�x��ݒ�
		//�e�̈ʒu���v�Z
		float shoot_x = parts[1]->GetX() + ((80.0f * cosf(aangle)) * direction);
		float shoot_y = parts[1]->GetY() + (80.0f * sinf(aangle));

		bullet->SetBullet(5, shoot_x, shoot_y, 16.0f, sangle); //�e�𔭎�
		sound->PlaySoundEffect(7); //���ʉ���炷
	}

	//��莞�Ԃ��Ƃɒe������
	if (time % 240 == 0) {
		shared_ptr<AbstractEnemy> mis;
		mis = manager->SetEnemy(9, x, y - 64.0f);
		mis->SetAngle(1.5f * PI);
		sound->PlaySoundEffect(9); //���ʉ���炷
	}

	//��莞�Ԍo������
	if (720 <= time) {
		pattern = 3; //�p�^�[����3��
		time = 0; //���Ԃ�������
	}
}

//�U��3�i�ːi�j
void Desdragud::Pattern3(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	float left = (float)camera->GetScrollX() + 160.0f; //���[
	float left2 = (float)camera->GetScrollX() - 64.0f;
	float right = (float)camera->GetScrollX() + (float)WINDOW_X - 160.0f; //�E�[
	float right2 = (float)camera->GetScrollX() + (float)WINDOW_X + 64.0f;
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y - 192.0f; //��
	float direction = (reverse) ? -1.0f : 1.0f; //�����ɉ������v�Z�p

	//�J�n�ʒu�ֈړ�
	if (60 < time && time < 180) {
		//��ʒu�Ɉړ�
		float dx = (reverse) ? right : left; //�ړI�n
		float sangle = atan2f(bottom - y, dx - x); //��ʒu�ւ̊p�x���擾
		sx = 8.0f * cosf(sangle); //���x��ݒ�
		sy = 8.0f * sinf(sangle);
		//parts[0]->Spin((3.0f / 180.0f) * PI, PI, -PI); //�r�̊p�x�𒲐�
		float aangle = Calculation::Spin(parts[0]->GetAngle(), (3.0f / 180.0f) * PI, PI, -PI); //�r�̊p�x�𒲐�
		parts[0]->SetAngle(aangle);
		aangle = Calculation::Spin(parts[1]->GetAngle(), (3.0f / 180.0f) * PI, PI, -PI); //�r�̊p�x�𒲐�
		parts[1]->SetAngle(aangle);
		//�߂��Ȃ�
		if (fabsf(dx - x) < 16.0f && fabsf(bottom - y) < 16.0f) {
			sx = 0.0f;
			sy = 0.0f;
		}
	}
	//���x��ݒ�
	else if (time == 300) {
		sx = -8.0f * direction;
	}
	//����
	else if(300 < time && time < 600) {
		float max_speed = (reverse ? -28.0f : 28.0f); //�����ɂ���đ��x�����ݒ�

		float accel = (reverse ? -0.05f : 0.05f); //�����ɂ���ĉ����x��ݒ�

		if(fabsf(sx) < 2.0f) sx = 2.0f * direction;

		sx += (fabsf(sx) * accel); //���i���j��
	}
	//�����𔽓]
	else if (time == 600) {
		reverse = !reverse;
	}
	//��ʊO����߂�
	else if (600 < time) {
		//��ʒu�Ɉړ�
		float dx = (reverse) ? right : left; //�ړI�n
		float sangle = atan2f(bottom - y, dx - x); //��ʒu�ւ̊p�x���擾
		sx = 8.0f * cosf(sangle);
		sy = 8.0f * sinf(sangle);
		//�߂��Ȃ�
		if (fabsf(dx - x) < 16.0f && fabsf(bottom - y) < 16.0f) {
			sx = 0.0f;
			sy = 0.0f;
			pattern = 3; //�p�^�[����3��
			time = 0; //���Ԃ�������
		}
	}

	//��ʊO�ɏo����
	if ((x < left2 && sx < 0.0f && reverse) || (right2 < x && 0.0f < sx && !reverse)) {
		sx = 0.0f; //��~
		parts[0]->SetAngle(0.25 * PI); //�r�̊p�x�𒲐�
		parts[1]->SetAngle(0.25 * PI);
	}
}

//�K���s���X�V
void Desdragud::AbsUpdate() {
	parts[0]->SetReverse(reverse);
	parts[1]->SetReverse(reverse);

	float direction = (reverse) ? -1.0f : 1.0f; //�����ɉ������v�Z�p
	head_x = x + ((head_distance * cosf(angle + head_angle) * direction));
	head_y = y + (head_distance * sinf(angle + head_angle));
	arm1_x = x + (((arm1_distance * cosf(angle + arm1_angle)) + (arm1_spin_distance * cosf(arm1_spin_angle + parts[0]->GetAngle()))) * direction);
	arm1_y = y + (arm1_distance * sinf(angle + arm1_angle)) + (arm1_spin_distance * sinf(arm1_spin_angle + parts[0]->GetAngle()));
	arm2_x = x + (((arm2_distance * cosf(angle + arm2_angle)) + (arm2_spin_distance * cosf(arm2_spin_angle + parts[1]->GetAngle()))) * direction);
	arm2_y = y + (arm2_distance * sinf(angle + arm2_angle)) + (arm2_spin_distance * sinf(arm2_spin_angle + parts[1]->GetAngle()));
	leg1_x = x + ((leg1_distance * cosf(angle + leg1_angle) * direction));
	leg1_y = y + (leg1_distance * sinf(angle + leg1_angle));
	leg2_x = x + ((leg2_distance * cosf(angle + leg2_angle) * direction));
	leg2_y = y + (leg2_distance * sinf(angle + leg2_angle));

	parts[0]->SetX(arm1_x);
	parts[0]->SetY(arm1_y);
	parts[1]->SetX(arm2_x);
	parts[1]->SetY(arm2_y);
}

//���ꂽ���̓���
void Desdragud::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_time = 60; //������܂ł̎��Ԃ�ݒ�
	sy = 0.5f;
}

//�X�V
void Desdragud::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
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
			move_flag = true;
			time = 0; //���Ԃ�������
		}
		break;
	}
}

//�`��
void Desdragud::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {

	int hundle = image->GetCharaImage(image_num, 0);
	int head_hundle = image->GetCharaImage(37, 0);
	int leg_hundle = image->GetCharaImage(39, 0);

	camera->Draw(leg1_x, leg1_y, reverse, angle, leg_hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	parts[0]->Draw(image, camera);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
	camera->Draw(head_x, head_y, reverse, angle, head_hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	camera->Draw(leg2_x, leg2_y, reverse, angle, leg_hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	parts[1]->Draw(image, camera);
}