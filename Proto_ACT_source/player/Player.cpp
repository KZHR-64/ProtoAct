#pragma once
#include "DxLib.h"
#include "Player.h"
#include <math.h>

using namespace std;

Player::Player(){

	message_font = CreateFontToHandle("Meiryo UI", 32, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2); //�t�H���g���

	head.def_angle = atan2f(-30.0f, 0.0f);
	head.def_distance = sqrtf(30.0f * 30.0f);
	head.spin_angle = 0.0f;
	head.spin_point = 0.0f;

	body.def_angle = atan2f(8.0f, 0.0f);
	body.def_distance = sqrtf(8.0f * 8.0f);
	body.spin_angle = 0.0f;
	body.spin_point = 0.0f;

	right_leg.def_angle = atan2f(18.0f, 8.0f);
	right_leg.def_distance = sqrtf((18.0f * 18.0f) + (8.0f * 8.0f));
	right_leg.spin_angle = atan2f(0.0f, 12.0f);
	right_leg.spin_point = sqrtf(12.0f * 12.0f);

	left_leg.def_angle = atan2f(18.0f, -8.0f);
	left_leg.def_distance = sqrtf((18.0f * 18.0f) + (8.0f * 8.0f));
	left_leg.spin_angle = atan2f(0.0f, 12.0f);
	left_leg.spin_point = sqrtf(12.0f * 12.0f);

	right_arm.def_angle = atan2f(-12.0f, 12.0f);
	right_arm.def_distance = sqrtf((12.0f * 12.0f) + (12.0f * 12.0f));
	right_arm.spin_angle = atan2f(0.0f, 10.0f);
	right_arm.spin_point = sqrtf(10.0f * 10.0f);

	left_arm.def_angle = atan2f(-12.0f, -12.0f);
	left_arm.def_distance = sqrtf((12.0f * 12.0f) + (12.0f * 12.0f));
	left_arm.spin_angle = atan2f(0.0f, 10.0f);
	left_arm.spin_point = sqrtf(10.0f * 10.0f);

	Reset(); //������
	hp = 6;
	weapon = 0;

	attack_move.push_back(&Player::Attack1);
	attack_move.push_back(&Player::Attack2);
	attack_move.push_back(&Player::Attack3);
	attack_move.push_back(&Player::Attack4);

	//�����蔻���ݒ�
	SetHit(0.0f, 0.0f, 16.0f);
	SetHit(0.0f, 32.0f, 16.0f);
	hit[0].check_bottom = false; //�����̔���͍s��Ȃ�
	hit[1].check_top = false; //����̔���͍s��Ȃ�

}

Player::~Player(){
	attack_move.clear();
}

//������
void Player::Reset(){
	if(hp <= 0) hp = 6; //HP��������
	x = 128.0f;
	y = 128.0f;
	sx = 0.0f; //���x��������
	sy = 0.0f; //���x��������
	angle = 0.0f; //�p�x��������
	spin_speed = 0.0f; //��]���x��������
	move_time = 0;
	move_type = Move_Stand; //�Î~��Ԃɐݒ�
	jump_flag = false; //�W�����v��Ԃ�������
	flying_flag = false; //��s�t���O��������
	through_flag = false; //���蔲���t���O��������
	damaged = false; //�_���[�W���󂯂��t���O��������
	damage_time = false; //�_���[�W����̎��Ԃ�������
	handle = 0; //�\������摜�̔ԍ���������
	inv_time = 0; //���G���Ԃ�������
	draw_flag = true; //�`��t���O��������
	move_flag = true; //����t���O��������
	key_num = 0; //���̐���������

	weapon_max = 4; //����̐���������

	body.angle = angle;
	right_leg.angle = angle;
	left_leg.angle = angle;
	right_arm.angle = 0.0f;
	left_arm.angle = angle;

	SetParts();

	catch_effect = NULL;
	step_mapchip = NULL;

	attack.flag = false; //�U���t���O��������
	attack.time = 0; //���������Ԃ�������
	attack.stop = false; //�����~�߂�t���O��������
	attack.energy = max_energy; //�U���G�l���M�[��������
	attack.res_time = 0; //�񕜎��Ԃ�������
	
}

//���͗����̊m�F
bool Player::RecordCheck(bool record[], int point){

	for (int i = 1; i < RECORD; i++){
		//�O�ɉ�����Ă��邩
		if (record[i]) return true; //������Ă�����true
	}
	return false; //�Ȃ�������false
}

//���@�̑���
void Player::Control(shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	if (!move_flag) {
		attack.flag = false;
		attack.time = 0;
		return; //����s�Ȃ�I��
	}

	//����������Ă�����
	if (key->KeyCheck(Left) && !attack.flag) {
		//�U����ԂłȂ��ꍇ
		if (!attack.flag) {
			reverse = true; //����������
		}
		// ���O�ɍ���������Ă��Ȃ�������
		if (!commando[Left][0]) {
			//���̑O�ɉ�����Ă����ꍇ
			if (RecordCheck(commando[Left], 1)) {
			}
		}
	}
	//�E��������Ă�����
	if (key->KeyCheck(Right) && !attack.flag) {
		//�U����ԂłȂ��ꍇ
		if (!attack.flag) {
			reverse = false; //�������E��
		}
		// ���O�ɉE��������Ă��Ȃ�������
		if (!commando[Right][0]) {
			//���̑O�ɉ�����Ă����ꍇ
			if (RecordCheck(commando[Right], 1)) {
			}
		}
	}

	float max_speed = (reverse ? -move_speed : move_speed); //�����ɂ���đ��x�����ݒ�

	float start_speed = (reverse ? -0.5f : 0.5f); //�ړ����n�߂̑��x(�����ɂ���đ��x��ݒ�)

	float accel = (reverse ? -0.2f : 0.2f); //�������x(�����ɂ���ĉ������x��ݒ�)

	float slip = 0.9f; //����

	//�}�b�v�`�b�v�ɏ���Ă����炻�̊���₷����������
	if (step_mapchip != NULL) {
		float sl = 1.0f - step_mapchip->GetFriction();
		slip += (sl / 10.0f);
	}

	//����������Ă��Ȃ�������������Ă��邩�U�����Ȃ�
	if ((!key->KeyCheck(Left) && !key->KeyCheck(Right)) || (key->KeyCheck(Left) && key->KeyCheck(Right)) || attack.flag) {
		if (fabsf(sx) <= (move_speed * 0.5f) && !jump_flag) sx = 0.0f; //�����̑��x��5���ŃW�����v���ĂȂ��Ȃ��~
		else {
			sx *= slip; //�Ⴄ�Ȃ猸��
			if (fabsf(sx) <= 0.1f) sx = 0.0f; //���Ȃ茸�������Ȃ��~
		}
	}
	//�ǂ��炩������Ă�����
	else {
		if (fabsf(sx) < fabsf(start_speed)) sx = start_speed; //�����n�߂̑��x�����Ői��ł��邩�~�܂��Ă���Ȃ瑬�x��0.5��
		else sx += (fabsf(sx) * accel); //����(����)
		if (fabsf(max_speed) < fabsf(sx)) sx = max_speed; //���x������𒴂��Ă����璲��
	}

	//�W�����v
	//�W�����v��������Ă��āA���W�����v���Ă��Ȃ��āA�U�����Ă��Ȃ��Ȃ�
	if (key->KeyCheck(Jump) && !jump_flag && !jumped && !attack.flag) {
		//���߂ĉ����ꂽ��������ƑO���牟����Ă�����
		if (!commando[Jump][0] || RecordCheck(jump_book)) {
			jump_flag = true; //�t���O��true��
			jump_time = 0; //�W�����v���Ԃ�0��
			jumped = true; //�{�^���������ꂽ���Ƃ𔽉f
			sy = -JUMP_SPEED; //�㏸�J�n
			effect->SetEffect(10, x, y + 40.0f, 0.25f); //�G�t�F�N�g�𔭐�
			effect->SetEffect(10, x - 16.0f, y + 32.0f, 0.4f);
			effect->SetEffect(10, x + 16.0f, y + 32.0f, 0.4f);
			sound->PlaySoundEffect(5); //���ʉ���炷
		}
	}

	//�����蔲��
	//����������Ă��āA�W�����v���Ă��Ȃ�������
	if (key->KeyCheckOnce(Down) && !jump_flag && !through_flag) {
		through_flag = true; //���蔲���J�n
		jump_flag = true;
		jump_time = JUMP_TIME_MAX;
		sy = JUMP_SPEED / 10.0f;
	}
}

//�_���[�W����
void Player::DamageAction() {
	//�_���[�W���󂯂��΂���Ȃ�
	if (damage_time == DAMAGE_TIME_MAX) {
		sx = 0.0f; //x���x��������
		sy = 0.0f; //y���x��������
		move_type = Move_Stand; //�����Î~��Ԃ�
	}
	damage_time--; //���쎞�Ԃ�����
	//���쎞�Ԃ�����������
	if (damage_time == 0) {
		damaged = false; //�t���O��false��
	}
}

//�ړ�
void Player::Move(shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	//�_���[�W���󂯂Ă�����
	if (damaged) {
		DamageAction(); //�_���[�W����
	}
	//�󂯂Ă��Ȃ�������
	else {
		Control(effect, key, sound); //�ʏ�̑���
	}
}

//�����蔻��̍X�V
void Player::HitUpdate() {
	for (int i = 0; i < 2; i++) {
		hit[i].x = x + (hit[i].distance * cosf(hit[i].angle));
		hit[i].y = y + (hit[i].distance * sinf(hit[i].angle));
	}
}

//�\������摜������
void Player::SetGraphic() {
	int old_move = move_type; //�O�̓���

	//�_�b�V���U�������Ă���Ȃ�
	if (attack.flag && weapon == 3) {
		move_type = Move_Dash; //������_�b�V����Ԃ�
	}
	//�U�����Ă���Ȃ�
	else if (attack.flag) {
		move_type = Move_Attack; //������U����Ԃ�
	}
	//�W�����v���Ă���Ȃ�
	else if (jump_flag) {
		move_type = Move_Jump; //������W�����v��Ԃ�
	}
	//�����Ă���Ȃ�
	else if (0.8f < fabsf(sx)) {
		move_type = Move_Walk; //�������s��Ԃ�
	}
	//�~�܂��Ă���Ȃ�
	else {
		move_type = Move_Stand; //�����Î~��Ԃ�
	}

	//�O�̓���Ɠ����Ȃ�
	if (old_move == move_type) {
		move_time++; //���쎞�Ԃ𑝉�
	}
	//�O�̓���ƈقȂ��
	else {
		move_time = 0; //���쎞�Ԃ�0��
		//��~��ԂłȂ����
		if (move_type != Move_Stand) {
			//�p�[�c�̊p�x��������
			body.angle = 0.0f;
			right_leg.angle = 0.5f * PI;
			right_arm.angle = 0.5f * PI;
			left_leg.angle = 0.5f * PI;
			left_arm.angle = 0.5f * PI;
		}
	}
}

//�L�[�̗������X�V
void Player::SetKeyRecord(shared_ptr<Key> key) {
	//���͗����̍X�V
	for (int i = 0; i < BUTTON; i++){
		for (int j = RECORD - 1; j > 0; j--){
			commando[i][j] = commando[i][j - 1]; //�O�̃L�[���擾
		}
	}
	for (int i = 0; i < BUTTON; i++) commando[i][0] = key->KeyCheck(i); //��������Ă���̂�}��

	for (int i = RECORD - 1; i > 0; i--) jump_book[i] = jump_book[i - 1]; //�O�̃W�����v���������������擾
	jump_book[0] = key->KeyCheckOnce(Jump); //�����߂ăW�����v�����������}��
	//�W�����v���Ă���{�^���������ꂽ��
	if (jumped && !key->KeyCheck(Jump)) {
		jumped = false; //�{�^���������ꂽ�̂𔽉f
	}

}

//�p�[�c�����낦��
void Player::SetParts() {
	//�����Ă���Ȃ�葫��U��
	if (move_type == Move_Walk) {
		body.angle = Calculation::HomingSpin(body.angle, PI * 0.025f, 0.0f);
		right_leg.angle = 0.5f * PI + (0.125f * PI * sinf(PI * 2.0f / 60.0f * move_time)); //����O��ɐU��
		right_arm.angle = 0.5f * PI - (0.25f * PI * sinf(PI * 2.0f / 60.0f * move_time)); //�r��O��ɐU��
		left_leg.angle = 0.5f * PI - (0.125f * PI * sinf(PI * 2.0f / 60.0f * move_time)); //����O��ɐU��
		left_arm.angle = 0.5f * PI + (0.25f * PI * sinf(PI * 2.0f / 60.0f * move_time)); //�r��O��ɐU��
	}
	//�U�����Ă���Ȃ�r��O�ɏo��
	else if (move_type == Move_Attack) {
		body.angle = Calculation::HomingSpin(body.angle, PI * 0.025f, 0.0f);
		right_arm.angle = 0.0f;
	}
	//�_�b�V���U�������Ă���Ȃ�r�����ɂ���
	else if (move_type == Move_Dash) {
		body.angle = Calculation::HomingSpin(body.angle, PI * 0.025f, 0.125f * PI);
		right_arm.angle = Calculation::HomingSpin(right_arm.angle, PI * 0.125, 0.875f * PI);
		left_arm.angle = Calculation::HomingSpin(left_arm.angle, PI * 0.1f, 0.875f * PI);
	}
	//�W�����v���Ă���Ȃ�r���グ�A���͏�������
	else if (move_type == Move_Jump) {
		body.angle = Calculation::HomingSpin(body.angle, PI * 0.025f, 0.0f);
		right_arm.angle = Calculation::HomingSpin(right_arm.angle, PI * 0.125f, -0.475f * PI);
		left_arm.angle = Calculation::HomingSpin(left_arm.angle, PI * 0.125f, -0.475f * PI);
		right_leg.angle = Calculation::HomingSpin(right_leg.angle, PI * 0.025f, 0.625f * PI);
		left_leg.angle = Calculation::HomingSpin(left_leg.angle, PI * 0.025f, 0.375f * PI);
	}
	//�~�܂��Ă���Ȃ�߂�
	else {
		body.angle = Calculation::HomingSpin(body.angle, PI * 0.025, 0.0f);
		right_leg.angle = Calculation::HomingSpin(right_leg.angle, PI * 0.05f, 0.5f * PI);
		right_arm.angle = Calculation::HomingSpin(right_arm.angle, PI * 0.05f, 0.5f * PI);
		left_leg.angle = Calculation::HomingSpin(left_leg.angle, PI * 0.05f, 0.5f * PI);
		left_arm.angle = Calculation::HomingSpin(left_arm.angle, PI * 0.05f, 0.5f * PI);
	}

	head.angle = 0.0f;

	float sum_angle = 0.0f; //���v�̊p�x
	float sum_spin = 0.0f; //���v�̉�]�p
	float direction = (reverse) ? -1.0f : 1.0f; //�����ɉ������v�Z�p

	//����
	body.total_angle = (angle + body.angle) * direction;
	sum_angle = (body.def_angle + body.total_angle) * direction;
	body.x = x + (body.def_distance * cosf(sum_angle));
	body.y = y + (body.def_distance * sinf(sum_angle)) * direction;

	//��
	head.total_angle = body.total_angle + head.angle;
	sum_angle = head.def_angle + head.total_angle;
	head.x = body.x + (head.def_distance * cosf(sum_angle));
	head.y = body.y + (head.def_distance * sinf(sum_angle));

	//�E��
	right_leg.total_angle = body.total_angle + (right_leg.angle * direction);
	sum_angle = body.total_angle + (right_leg.def_angle * direction);
	sum_spin = (right_leg.spin_angle + right_leg.total_angle) * direction;
	right_leg.x = body.x + (((right_leg.def_distance * cosf(sum_angle) * direction)) + (right_leg.spin_point * cosf(sum_spin) * direction));
	right_leg.y = body.y + ((right_leg.def_distance * sinf(sum_angle) * direction)) + (right_leg.spin_point * sinf(sum_spin));

	//����
	left_leg.total_angle = body.total_angle + (left_leg.angle * direction);
	sum_angle = body.total_angle + (left_leg.def_angle * direction);
	sum_spin = (left_leg.spin_angle + left_leg.total_angle) * direction;
	left_leg.x = body.x + (((left_leg.def_distance * cosf(sum_angle) * direction)) + (left_leg.spin_point * cosf(sum_spin) * direction));
	left_leg.y = body.y + ((left_leg.def_distance * sinf(sum_angle) * direction)) + (left_leg.spin_point * sinf(sum_spin));

	//�E�r
	right_arm.total_angle = body.total_angle + (right_arm.angle * direction);
	sum_angle = body.total_angle + (right_arm.def_angle * direction);
	sum_spin = (right_arm.spin_angle + right_arm.total_angle) * direction;
	right_arm.x = body.x + (((right_arm.def_distance * cosf(sum_angle) * direction) + (right_arm.spin_point * cosf(sum_spin) * direction)));
	right_arm.y = body.y + ((right_arm.def_distance * sinf(sum_angle) * direction) + (right_arm.spin_point * sinf(sum_spin)));

	//���r
	left_arm.total_angle = body.total_angle + (left_arm.angle * direction);
	sum_angle = body.total_angle + (left_arm.def_angle * direction);
	sum_spin = (left_arm.spin_angle + left_arm.total_angle) * direction;
	left_arm.x = body.x + (((left_arm.def_distance * cosf(sum_angle) * direction) + (left_arm.spin_point * cosf(sum_spin) * direction)));
	left_arm.y = body.y + ((left_arm.def_distance * sinf(sum_angle) * direction) + (left_arm.spin_point * sinf(sum_spin)));
}

//�U��1�i���˒e�j
void Player::Attack1(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	shared_ptr<AbstractBullet> bul;
	float shoot_angle = (reverse ? PI : 0.0f); //�����ɂ���Č��p�x������
	//�U��(����)�̃{�^����������Ă�����
	if (key->KeyCheck(Attack)) {
		attack.flag = true; //�U���t���O��true��
		attack.stop = true; //��~�t���O��true��
		//���߂čU���{�^�����������������Ă��΂炭������
		if (attack.time % 12 == 0) {
			//�G�l���M�[������ꍇ
			if (0 < attack.energy) {
				bul = bullet->SetBullet(0, x, y, 16.0f, shoot_angle); //�e�𔭎�sound
				sound->PlaySoundEffect(7); //���ʉ���炷
				attack.energy--; //�G�l���M�[������
				attack.res_time = res_time; //�񕜎��Ԃ�ݒ�
			}
			//�Ȃ��ꍇ
			else {
				sound->PlaySoundEffect(3); //���ʉ���炷
			}
		}
		attack.time++; //�U�����Ă��鎞�Ԃ𑝉�
	}
	else {
		attack.flag = false; //�U���t���O��false��
		attack.stop = false; //��~�t���O��false��
		attack.time = 0; //�����Ă��鎞�Ԃ�������
	}
}

//�U��2�i����e�j
void Player::Attack2(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	float shoot_angle = (reverse ? PI : 0.0f); //�����ɂ���Č��p�x������
	//�U��(����)�̃{�^����������Ă�����
	if (key->KeyCheck(Attack)) {
		attack.flag = true; //�U���t���O��true��
		attack.stop = true; //��~�t���O��true��
		//���߂čU���{�^������������
		if (attack.time == 0) {
			//�G�l���M�[������ꍇ
			if (1 < attack.energy) {
				player_bullet = bullet->SetBullet(1, x, y, 8.0f, shoot_angle); //�e�𔭎�
				sound->PlaySoundEffect(8); //���ʉ���炷
				attack.energy -= 2; //�G�l���M�[������
				attack.res_time = res_time; //�񕜎��Ԃ�ݒ�
			}
			//�Ȃ��ꍇ
			else {
				sound->PlaySoundEffect(3); //���ʉ���炷
			}
		}
		attack.time++; //�U�����Ă��鎞�Ԃ𑝉�
	}
	else {
		player_bullet.reset(); //�e�̌��������
		attack.flag = false; //�U���t���O��false��
		attack.stop = false; //��~�t���O��false��
		attack.time = 0; //�����Ă��鎞�Ԃ�������
	}
}

//�U��3�i���P�b�g�n���h�j
void Player::Attack3(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	float shoot_angle = (reverse ? PI : 0.0f); //�����ɂ���Č��p�x������
	//�U�����Ă��Ȃ���ԂōU��(����)�̃{�^���������ꂽ��
	if (key->KeyCheckOnce(Attack) && !attack.flag) {
		//�G�l���M�[������ꍇ
		if (1 < attack.energy) {
			attack.flag = true; //�U���t���O��true��
			attack.stop = true; //��~�t���O��true��
			player_bullet = bullet->SetBullet(2, x, y, 16.0f, shoot_angle); //�e�𔭎�
			sound->PlaySoundEffect(6); //���ʉ���炷
			attack.energy -= 2; //�G�l���M�[������
			attack.res_time = res_time; //�񕜎��Ԃ�ݒ�
		}
		//�Ȃ��ꍇ
		else {
			sound->PlaySoundEffect(3); //���ʉ���炷
		}
	}
	//�U�����Ȃ�
	if (attack.flag) {
		attack.time++; //�U�����Ă��鎞�Ԃ𑝉�
		//�e����������
		if (player_bullet.use_count() <= 1) {
			player_bullet.reset(); //�e�̌��������
			attack.flag = false; //�U���t���O��false��
			attack.stop = false; //��~�t���O��false��
			attack.time = 0; //�����Ă��鎞�Ԃ�������
		}
	}
}

//�U��4�i�_�b�V���j
void Player::Attack4(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	//�U�����Ă��Ȃ���ԂōU��(����)�̃{�^���������ꂽ��
	if (key->KeyCheckOnce(Attack) && !attack.flag) {
		//�G�l���M�[������ꍇ
		if (1 < attack.energy) {
			inv_time = DAMAGE_INV_TIME; //���G���Ԃ�ݒ�
			flying_flag = true; //��s�t���O��true��
			attack.flag = true; //�U���t���O��true��
			attack.stop = false; //��~�t���O��false��
			player_bullet = bullet->SetBullet(3, x, y, 0.0f, 0.0f); //�e�𔭎�
			sound->PlaySoundEffect(9); //���ʉ���炷
			attack.energy -= 2; //�G�l���M�[������
			attack.res_time = res_time; //�񕜎��Ԃ�ݒ�
		}
		//�Ȃ��ꍇ
		else {
			sound->PlaySoundEffect(3); //���ʉ���炷
		}
	}
	//�U�����Ȃ�
	if (attack.flag) {
		if (player_bullet != NULL) {
			player_bullet->SetX(x); //���W�����킹��
			player_bullet->SetY(y);
		}
		//��莞�Ԍo�߂�����
		if (30 == attack.time) {
			inv_time = 0; //���G���Ԃ�0��
			flying_flag = false; //��s�t���O��false��
			attack.stop = true; //��~�t���O��true��
			player_bullet->SetEndFlag(true); //�e������
			player_bullet.reset();//�e�̌��������
			player_bullet = NULL;
		}
		else if (attack.time < 30) {
			sx = (reverse ? -8.0f : 8.0f); //�����ɂ���đ��x������
			sy = 0.0f;
		}
		else if (36 < attack.time) {
			attack.flag = false; //�U���t���O��false��
			attack.stop = false; //��~�t���O��false��
			attack.time = 0; //�����Ă��鎞�Ԃ�������
		}
		attack.time++; //�U�����Ă��鎞�Ԃ𑝉�
	}
}

//�ʒu�̒���
void Player::AdjustPosition(std::shared_ptr<MapChipManager> map, bool event_flag) {
	//�擾�p�N���X
	shared_ptr<AbstractMapChip> mapchip;

	bool left_hit = false; //�������������Ă��邩
	bool right_hit = false; //�E�����������Ă��邩
	bool top_hit = false; //�㑤���������Ă��邩
	bool bottom_hit = false; //�������������Ă��邩

	float sub = 0.0f; //����ɂǂꂾ���߂荞��ł��邩

	//����Ă��鑫��̑��x�̍��v
	float mx = map->GetPlusSpeedX(hit[1].x, hit[1].y + 0.1f, hit[1].size);
	float my = map->GetPlusSpeedY(hit[1].x, hit[1].y + 0.1f, hit[1].size);

	//�����x
	float accel = 0.3f;

	float left = 0.0f; //��ʍ��[
	float right = (float)WINDOW_X; //��ʉE�[
	float top = 0.0f; //��ʏ�
	float bottom = (float)WINDOW_Y; //��ʒ�

	//�p�x��ݒ�
	angle += spin_speed;

	//���E�̔��肩��s��

	//�s���\��̍��W������
	x += sx + mx;

	//�����蔻��̍X�V
	HitUpdate();

	//�C�x���g���łȂ���Ή�ʓ��Ɏ��߂�
	/*if (!event_flag) {
		if (fx < left + hit_size) {
			fx = left + hit_size;
			left_hit = true; //�����������������Ƃ�
		}
		if (right - hit_size < fx) {
			fx = right - hit_size;
			right_hit = true; //�E���������������Ƃ�
		}
	}*/

	//�}�b�v�`�b�v�Ƃ̐ڐG����
	for (int i = 0; i < 2; i++)
	{
		//mapchip = map->HitCheckLeft(x, y, hit[i].size);
		mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			left_hit = true; //�����������������Ƃ�
			sub = (hit[i].x - hit[i].size) - (mapchip->GetX() + 4.0f * mapchip->GetSizeX()); //�߂荞�݋���v�Z
			//x = mapchip->GetX() + 4.0f * mapchip->GetSizeX() + hit_size;
			x += fabsf(sub);
			sx = 0.0f;
			angle = 0.0f;
			spin_speed = 0.0f;
			HitUpdate(); //�����蔻��̍X�V
			//����s�\�Ȃ�
			if (!move_flag) {
				flying_flag = false; //��s�I��
				move_flag = true; //����\��
			}
			mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			right_hit = true; //�E���������������Ƃ�
			sub = (hit[i].x + hit[i].size) - (mapchip->GetX() - 4.0f * mapchip->GetSizeX()); //�߂荞�݋���v�Z
			//x = mapchip->GetX() - 4.0f * mapchip->GetSizeX() - hit_size;
			x -= fabsf(sub);
			sx = 0.0f;
			angle = 0.0f;
			spin_speed = 0.0f;
			HitUpdate(); //�����蔻��̍X�V
			//����s�\�Ȃ�
			if (!move_flag) {
				flying_flag = false; //��s�I��
				move_flag = true; //����\��
			}
			mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//�������������Ă�����
	if (left_hit && right_hit) {
		hp = 0; //HP��0��
		damaged = true;
		//���x��������
		sx = 0.0f;
		sy = 0.0f;
		return;
	}

	//���ɏ㉺�̔���

	//�W�����v��
	if (jump_flag) {
		//�W�����v��������Ă��ă_���[�W���󂯂Ă��Ȃ����
		if (commando[Jump][0] && !damaged) {
			jump_time++; //���Ԃ𑝉�
		}
		//������ĂȂ�������
		else {
			jump_time = JUMP_TIME_MAX; //���~�J�n
		}
	}

	//�㏸���ԂɒB�����ꍇ
	if (jump_flag && jump_time >= JUMP_TIME_MAX && !flying_flag) {
		if (fabsf(sy) < 0.4f) sy = 0.4f;
		sy += fabsf(sy * accel); //���x��1.3(0.7)�{����
		if (JUMP_SPEED < sy) sy = JUMP_SPEED;
	}

	//�s���\��̍��W������
	y += sy + my;

	//�����蔻��̍X�V
	HitUpdate();

	//�C�x���g���łȂ���Ή�ʓ��Ɏ��߂�
	/*if (!event_flag) {
		if (y < top + hit_size) {
			y = top + hit_size;
			top_hit = true; //�㑤�������������Ƃ�
		}
		if (bottom - hit_size < y) {
			y = bottom - hit_size;
			bottom_hit = true; //�����������������Ƃ�
		}
	}*/

	//�}�b�v�`�b�v�Ƃ̐ڐG����
	for (int i = 0; i < 2; i++)
	{
		//����
		if (!hit[i].check_top) continue;
		mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			top_hit = true; //�㑤�������������Ƃ�
			sub = (hit[i].y - hit[i].size) - (mapchip->GetY() + 8.0f * mapchip->GetSizeY()); //�߂荞�݋���v�Z
			//y = mapchip->GetY() + 8.0f * mapchip->GetSizeY() + hit_size;
			y += fabsf(sub);
			sy = 0.0f;
			angle = 0.0f;
			spin_speed = 0.0f;
			HitUpdate(); //�����蔻��̍X�V
			//����s�\�Ȃ�
			if (!move_flag) {
				flying_flag = false; //��s�I��
				move_flag = true; //����\��
			}
			mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		//����
		if (!hit[i].check_bottom) continue;
		mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		if (mapchip != NULL) bottom_hit = true; //�����������������Ƃ�
		while (mapchip != NULL && 0.0f < sy && !(mapchip->GetThrough() && through_flag)) {
			sub = (hit[i].y + hit[i].size) - (mapchip->GetY()); //�߂荞�݋���v�Z
			//y = mapchip->GetY() - hit_size;
			y -= fabsf(sub);
			sy = 0.0f;
			angle = 0.0f;
			spin_speed = 0.0f;
			jump_flag = false; //�t���O��false��
			HitUpdate(); //�����蔻��̍X�V
			//����s�\�Ȃ�
			if (!move_flag) {
				flying_flag = false; //��s�I��
				move_flag = true; //����\��
			}
			mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//�������������Ă�����
	if (top_hit && bottom_hit) {
		hp = 0; //HP��0��
		damaged = true;
		//���x��������
		sx = 0.0f;
		sy = 0.0f;
		return;
	}

	//��ʊO�ɗ�������
	if (bottom + 128.0f < y) {
		hp = 0; //HP��0��
		damaged = true;
		//���x��������
		sx = 0.0f;
		sy = 0.0f;
		return;
	}

	HitUpdate(); //�����蔻��̍X�V

	step_mapchip = map->HitCheckBottom(hit[1].x, hit[1].y + 1.0f, hit[1].size); //����Ă��鑫���ݒ�

	//�W�����v���Ă��Ȃ��ŋ󒆂ɂ���ꍇ
	if (step_mapchip == NULL && !jump_flag && !flying_flag) {
		jump_flag = true; //�t���O��true��
		jump_time = JUMP_TIME_MAX; //���~�J�n
	}

	//�󒆂ɂ�����
	if (!bottom_hit) {
		through_flag = false; //���蔲���I��
	}

	//����Ă���}�b�v�`�b�v���m�F
	map->CheckStep(hit[1].x, hit[1].y + 1.0f, hit[1].size);

	SetGraphic(); //�\������|�[�Y��ݒ�
	SetParts(); //�p�[�c�̔z�u
}

//�U��
void Player::AttackCheck(shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	//����ύX�̃{�^����������Ă�����
	if (key->KeyCheckOnce(L) && !attack.flag) {
		weapon--; //�����ύX
		sound->PlaySoundEffect(0); //���ʉ���炷
	}
	if (key->KeyCheckOnce(R) && !attack.flag) {
		weapon++; //�����ύX
		sound->PlaySoundEffect(0); //���ʉ���炷
	}
	//����̔ԍ���0�����Ȃ�
	if (weapon < 0) {
		weapon = weapon_max - 1; //�ő�l�ɂ���
	}
	//����̔ԍ����ő�l�𒴂�����
	if (weapon_max <= weapon) {
		weapon = 0; //0�ɂ���
	}

	if (!move_flag) return; //����s�Ȃ炱���ŏI��

	if ((unsigned)weapon < attack_move.size()) {
		(this->*attack_move[weapon])(bullet, effect, key, sound);
	}

	//�U�����Ă��Ȃ��ꍇ
	if (!attack.flag) {
		//�񕜎��Ԃ�����ꍇ
		if (0 < attack.res_time) {
			attack.res_time--; //�񕜎��Ԃ�����
			//�񕜎��Ԃ�0�̏ꍇ
			if (attack.res_time == 0 && attack.energy < max_energy) {
				attack.energy++; //�G�l���M�[����
				//�G�l���M�[���񕜂������Ă��Ȃ��ꍇ
				if (attack.energy < max_energy) {
					attack.res_time = res_time; //�񕜎��Ԃ�ݒ�
				}
			}
		}
	}

}

//�G�ɓ������Ă��邩
void Player::HitCheckEnemy(shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (0 < inv_time) return; //���G���Ԓ��Ȃ�I��

	int damage = (move_flag) ? 0 : 65535; //��C�Ŕ��ł��邩�ŐڐG�_���[�W��ݒ�

	for (int i = 0; i < 2; i++)
	{
		//�G�ɓ������Ă�����
		if (enemy->HitCheckChara(x, y, hit[i].size, effect, sound, damage)) {
			//��C�Ŕ��ł��Ȃ��Ȃ�
			if (move_flag) {
				hp--; //HP������
				damaged = true; //�_���[�W���
				damage_time = DAMAGE_TIME_MAX; //�_���[�W���Ԃ�ݒ�
				inv_time = DAMAGE_INV_TIME; //���G���Ԃ�ݒ�
				sound->PlaySoundEffect(10); //���ʉ���炷
			}
			return; //�I��
		}
	}
}

//�e�ɓ������Ă��邩
void Player::HitCheckBullet(shared_ptr<BulletManager> bullet, shared_ptr<Sound> sound) {
	if (0 < inv_time || !move_flag) return; //���G���Ԓ��Ȃ�I��
	
	for (int i = 0; i < 2; i++) {
		//�e�ɓ������Ă�����
		if (0 < bullet->HitCheckChara(x, y, hit[i].size, true, false)) {
			hp--; //HP������
			damaged = true; //�_���[�W���
			damage_time = DAMAGE_TIME_MAX; //�_���[�W���Ԃ�ݒ�
			inv_time = DAMAGE_INV_TIME; //���G���Ԃ�ݒ�
			sound->PlaySoundEffect(10); //���ʉ���炷
			return; //�I��
		}
	}
}

//�A�C�e���ɓ������Ă��邩
bool Player::HitCheckItem(float cx, float cy, float hit_size) {
	for (int i = 0; i < 2; i++)
	{
		float dif_x = cx - hit[i].x;
		float dif_y = cy - hit[i].y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + hit[i].size) {
			return true;
		}
	}
	return false;
}

//�`�悷�邩�ݒ�
void Player::SetDrawFlag(bool flag) {
	draw_flag = flag;
}

//����ł��邩�ݒ�
void Player::SetMoveFlag(bool flag) {
	move_flag = flag;
}

//���̐����擾
int Player::GetKeyNum() {
	return key_num;
}

//���̐���ݒ�
void Player::SetKeyNum(int num) {
	key_num = num;
}

//����̐���ݒ�
void Player::SetWeaponMax(int num) {
	weapon_max = num;
}

//�K���s���X�V
void Player::AbsUpdate() {

}

//�X�V
void Player::Update(shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){
	Move(effect, key, sound);
	SetKeyRecord(key); //�L�[�̗������X�V
	
	//���G���Ԓ��Ȃ�
	if (0 < inv_time) {
		inv_time--; //���G���Ԃ�����
	}


}

//�`��
void Player::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	int image1 = image->GetCharaImage(0, 0); //���@�̉摜���擾�i���j
	int image2 = image->GetCharaImage(1, 0); //���@�̉摜���擾�i���j
	int image3 = image->GetCharaImage(2, 0); //���@�̉摜���擾�i�r�j
	int image4 = image->GetCharaImage(3, 0); //���@�̉摜���擾�i���j

	//HP����̉摜���擾
	int en_point = image->GetEffectImage(9, 0);
	int life = image->GetEffectImage(8, 0);
	int life_bar = image->GetEffectImage(7, 0);

	//������̉摜���擾
	int weapon_window = image->GetEffectImage(13, 0);
	int weapon_name = image->GetEffectImage(14, weapon);

	int trance = 255; //�����x

	//HP����̕`��
	Display::Draw(172.0f, (float)WINDOW_Y - 32.0f, false, 0.0f, life_bar);
	for (int i = 0; i < hp; i++) {
		Display::Draw(74.0f + (16.0f * i), (float)WINDOW_Y - 32.0f, false, 0.0f, life);
	}
	for (int i = 0; i < attack.energy; i++) {
		Display::Draw(238.0f + (24.0f * i), (float)WINDOW_Y - 32.0f, false, 0.0f, en_point);
	}
	//����̕\��
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y - 32.0f, false, 0.0f, weapon_window);
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y - 32.0f, false, 0.0f, weapon_name);

	//���G���Ԓ��͓_�ł���
	if (0 < inv_time) {
		if (inv_time % 10 < 5) {
			trance = 96;
		}
		else {
			trance = 192;
		}
	}

	//���@�̕`��
	if (draw_flag) {

		camera->Draw(right_arm.x, right_arm.y, reverse, right_arm.total_angle, image3, 1.0f, DX_BLENDMODE_ALPHA, trance); //���@��`��i�r�j
		camera->Draw(head.x, head.y, reverse, head.total_angle, image2, 1.0f, DX_BLENDMODE_ALPHA, trance); //���@��`��i���j
		camera->Draw(right_leg.x, right_leg.y, reverse, right_leg.total_angle, image4, 1.0f, DX_BLENDMODE_ALPHA, trance);//���@��`��i���j
		camera->Draw(left_leg.x, left_leg.y, reverse, left_leg.total_angle, image4, 1.0f, DX_BLENDMODE_ALPHA, trance);//���@��`��i���j
		camera->Draw(body.x, body.y, reverse, body.total_angle, image1, 1.0f, DX_BLENDMODE_ALPHA, trance); //���@��`��i���j
		camera->Draw(left_arm.x, left_arm.y, reverse, left_arm.total_angle, image3, 1.0f, DX_BLENDMODE_ALPHA, trance);//���@��`��i�r�j

		for (auto &h : hit)
		{
			camera->HitDraw(h.x, h.y, h.size); //�����蔻���`��
		}

	}

	//DrawFormatString(0, 100, GetColor(0, 0, 255), "%d %d", through_flag, key_num);
	//DrawFormatString(0, 128, GetColor(0, 0, 255), "%d %f %f %f", weapon, x, y, hit[1].y);
	
}
