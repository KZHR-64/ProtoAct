#pragma once
#include "DxLib.h"
#include "CharacterBase.h"

using namespace std;

CharacterBase::CharacterBase() {

	time = 0; //�^�C�}�[��������
	live_flag = true; //�����t���O��������
	end_flag = false; //���Ńt���O��������
	end_time = -1; //���ł܂ł̎��Ԃ�������
	image_num = -1; //�g�p����摜��������
	trance = 255; //�����x��������
	hp = 1; //HP��������
	max_hp = hp; //�ő�HP��������
	x = 0.0f; //x���W��������
	y = 0.0f; //y���W��������
	base_x = x; //��ƂȂ�x���W��������
	base_y = y; //��ƂȂ�y���W��������
	sx = 0.0f; //x�����̑��x��������
	sy = 0.0f; //y�����̑��x��������
	reverse = false; //���]�t���O��������
	angle = 0.0f; //�p�x��������
	spin_speed = 0.0f; //��]���x��������
	ex_rate = 1.0f; //�\���{����������
	jump_time = 0; //�W�����v���Ԃ�������
	jump_flag = false; //�W�����v�t���O��������
	hit_flag = true; //�����蔻���������
	flying_flag = false; //��s�t���O��������
	damaged = false; //�_���[�W�t���O��������
	damage_time = false; //�_���[�W���쎞�Ԃ�������
	hit_map = true; //�}�b�v�`�b�v�Ƃ̓����蔻���������
	adjusted = false; //�}�b�v�`�b�v�ɓ�����������������
}

CharacterBase::~CharacterBase() {
	hit.clear(); //�����蔻��̃����������
}

//�֐ߏ���ݒ�i�֐߁A��]���̈ʒu�A�����ʒu�A��[�ւ̋����j
void CharacterBase::SetJoint(JointStruct& joint, float ax, float ay, float set_x, float set_y, float angle_max, float angle_min) {
	joint.axis_x = ax; //��]���̈ʒu��ݒ�
	joint.axis_y = ay; //��]���̈ʒu��ݒ�
	joint.angle_max = angle_max; //�p�x�̏����ݒ�
	joint.angle_min = angle_min; //�p�x�̉�����ݒ�
	joint.dist = sqrtf((set_x * set_x) + (set_y * set_y)); //��[�Ƃ̋�����ݒ�
	joint.local_angle = atan2f(set_y, set_x); //�֐߂̊p�x��ݒ�
}

//�����蔻��̔z�u
void CharacterBase::SetHit(float cx, float cy, float hit_size) {
	HitStruct new_hit{};

	new_hit.angle = atan2f(cy, cx); //�����p�x��ݒ�
	new_hit.distance = sqrtf((cx * cx) + (cy * cy)); //�{�̂Ƃ̋�����ݒ�
	new_hit.size = hit_size; //����̑傫����ݒ�
	new_hit.x = x;
	new_hit.y = y;

	hit.emplace_back(new_hit);
}

//�֐߂̈ʒu��ݒ�
void CharacterBase::JointUpdate(vector<JointStruct>& joint, float bx, float by, float bangle) {
	if (joint.size() <= 0) return;

	//�����̈ʒu��ݒ�
	joint[0].total_angle = joint[0].local_angle + bangle; //�p�x��ݒ�
	joint[0].x = bx + (joint[0].dist * cosf(joint[0].total_angle)); //���W��ݒ�
	joint[0].y = by + (joint[0].dist * sinf(joint[0].total_angle)); //���W��ݒ�

	for (unsigned int i = 1; i < joint.size(); i++)
	{
		joint[i].total_angle = joint[i].local_angle + joint[i - 1].total_angle; //�p�x��ݒ�
		joint[i].x = joint[i - 1].x + (joint[i].dist * cosf(joint[i].total_angle)); //���W��ݒ�
		joint[i].y = joint[i - 1].y + (joint[i].dist * sinf(joint[i].total_angle)); //���W��ݒ�
	}
}

//�C���o�[�X�L�l�}�e�B�N�X
void CharacterBase::IkSetting(std::vector<JointStruct>& joint, float speed, float dx, float dy){
	if (joint.size() <= 0) return;
	int joint_max = joint.size() - 1; //���֐߂̍Ō��

	float dangle = Calculation::LockOn(joint[joint_max].x, joint[joint_max].y, dx, dy); //��[�𓮂����ׂ��p�x

	//�p�x���[���狁�߂�
	for (unsigned int i = joint_max - 1; 0 < i; i--)
	{	
		//float cangle = Calculation::HomingSpin(joint[i].total_angle, sangle, joint[i].x, joint[i].y, dx, dy); //�ڕW�̊p�x
		//float dangle = cangle - joint[i].total_angle; //��]��
		//����𒴂��Ȃ��ꍇ
		//if (joint[i].total_angle + joint[i].angle_max < cangle) {
		//	joint[i].total_angle += joint[i].angle_max; //����l�ɐݒ�
		//}
		//������ꍇ
		//else {
			//joint[i].total_angle = cangle; //�p�x��ݒ�
		//}
		//�����������Ȃ��ꍇ
		//if (joint[i].total_angle + joint[i].angle_min < cangle) {
		//	joint[i].total_angle += joint[i].angle_max; //����l�ɐݒ�
		//}
		//�����ꍇ
		//else {
			//joint[i].total_angle = cangle; //�p�x��ݒ�
		//}
		//joint[joint_max].x = joint[i].x;
	}

	//���W���������狁�߂�
	for (unsigned int i = 1; i < joint.size(); i++)
	{

	}
}

//���֐߂�L�k������
void CharacterBase::ZoomJoint(std::vector<JointStruct>& joint, float zoom_limit, float dx, float dy) {

}

//�����蔻��̍X�V
void CharacterBase::HitUpdate() {
	if (hit.size() <= 0) return;
	for (unsigned int i = 0; i < hit.size(); i++) {
		float direction = (reverse) ? -1.0f : 1.0f; //�����ɉ������v�Z�p
		hit[i].x = x + ((hit[i].distance * cosf(hit[i].angle + angle)) * direction);
		hit[i].y = y + (hit[i].distance * sinf(hit[i].angle + angle));
	}
}

//�������邩���擾
bool CharacterBase::GetEndFlag() {
	return end_flag;
}

//�������邩��ݒ�
void CharacterBase::SetEndFlag(bool flag) {
	end_flag = flag;
}

//���ł܂ł̎��Ԃ�Ԃ�
int CharacterBase::GetEndTime() {
	return end_time;
}

//���ł܂ł̎��Ԃ�ݒ�
void CharacterBase::SetEndTime(int set_time) {
	end_time = set_time;
}

//�����蔻����擾
bool CharacterBase::GetHitFlag() {
	return hit_flag;
}

//�����蔻���ݒ�
void CharacterBase::SetHitFlag(bool flag) {
	hit_flag = flag;
}

//�����x��ݒ�
void CharacterBase::SetTrance(int set_trance) {
	trance = set_trance;
}

//���Ԃ�Ԃ�
int CharacterBase::GetTime() {
	return time;
}

//���Ԃ�ݒ�
void CharacterBase::SetTime(int set_time) {
	time = set_time;
}

//HP��Ԃ�
int CharacterBase::GetHp() {
	return hp;
}

//HP��ݒ�
void CharacterBase::SetHp(int set_hp) {
	hp = set_hp;
}

//�ő�HP��ݒ�
void CharacterBase::SetMaxHp(int set_hp) {
	max_hp = set_hp;
}

//x���W��Ԃ�
float CharacterBase::GetX() {
	return x;
}

//x���W��ݒ�
void CharacterBase::SetX(float set_x) {
	x = set_x;
	HitUpdate();
}

//y���W��Ԃ�
float CharacterBase::GetY() {
	return y;
}

//y���W��ݒ�
void CharacterBase::SetY(float set_y) {
	y = set_y;
	HitUpdate();
}

//����x���W��Ԃ�
float CharacterBase::GetBaseX() {
	return x;
}

//����x���W��ݒ�
void CharacterBase::SetBaseX(float set_x) {
	x = set_x;
}

//����y���W��Ԃ�
float CharacterBase::GetBaseY() {
	return y;
}

//����y���W��ݒ�
void CharacterBase::SetBaseY(float set_y) {
	y = set_y;
}

//�p�x����ɑ��x��ݒ�
void CharacterBase::SetSpeed(float speed) {
	sx = speed * cosf(angle);
	sy = speed * sinf(angle);
}

//x�����̑��x��Ԃ�
float CharacterBase::GetXSpeed() {
	return sx;
}

//x�����̑��x��ݒ�
void CharacterBase::SetXSpeed(float set_x) {
	sx = set_x;
}

//y�����̑��x��Ԃ�
float CharacterBase::GetYSpeed() {
	return sy;
}

//y�����̑��x��ݒ�
void CharacterBase::SetYSpeed(float set_y) {
	sy = set_y;
}

//�p�x���擾
float CharacterBase::GetAngle() {
	return angle;
}

//�p�x��ݒ�(�p�x)
void CharacterBase::SetAngle(float set_angle) {
	angle = set_angle;
}

//��]���x���擾
float CharacterBase::GetSpinSpeed() {
	return spin_speed;
}

//��]���x��ݒ�(�p�x)
void CharacterBase::SetSpinSpeed(float set_angle) {
	spin_speed = set_angle;
}

//�������擾
bool CharacterBase::GetReverse() {
	return reverse;
}

//������ݒ�
void CharacterBase::SetReverse(bool flag) {
	reverse = flag;
}

//�\���{����ݒ�
void CharacterBase::SetExRate(float set_rate) {
	ex_rate = set_rate;
}

//���ł��邩���擾
bool CharacterBase::GetFlying() {
	return flying_flag;
}

//���ł��邩��ݒ�
void CharacterBase::SetFlying(bool flag) {
	flying_flag = flag;
}

//�_���[�W���󂯂Ă��邩���擾
bool CharacterBase::GetDamaged() {
	return damaged;
}

//�}�b�v�`�b�v�ɓ����邩���擾
bool CharacterBase::GetHitMap() {
	return hit_map;
}

//�}�b�v�`�b�v�ɓ����邩��ݒ�
void CharacterBase::SetHitMap(bool flag) {
	hit_map = flag;
}

//�����蔻��̕`��
void CharacterBase::DrawHit(shared_ptr<Camera> camera) {
	if (hit.empty()) return;
	for (auto& h : hit) {
		camera->HitDraw(h.x, h.y, h.size); //�����蔻���`��
	}
}

//�L�����N�^�[�Ƃ̓����蔻��
bool CharacterBase::HitCheckChara(float cx, float cy, float hit_size, bool check_hit) {
	if (hit.size() <= 0) return false;

	for (auto& h : hit) {

		float dif_x = cx - h.x;
		float dif_y = cy - h.y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + h.size) {
			return true;
		}
	}

	return false;
}

//�^�C�}�[�֘A�̍X�V
void CharacterBase::Timer() {
	time++;
	if (0 < damage_time) {
		damage_time--;
		if (damage_time <= 0) {
			damaged = false;
		}
	}
}