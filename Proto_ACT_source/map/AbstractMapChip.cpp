#pragma once
#include "DxLib.h"
#include "AbstractMapChip.h"
#include <math.h>

using namespace std;

AbstractMapChip::AbstractMapChip(MapChipManager* man, int num) : CharacterBase(){
	manager = man;

	live_flag = true;
	draw_flag = true;
	end_flag = false;
	time = 0;
	image_num = num;
	last_x = x;
	last_y = y;
	base_x = x;
	base_y = y;
	size_x = 1;
	size_y = 1;
	through = false;
	breakable = false;
	flying_flag = true;
	hit_flag = true;
	hit_map = true;
	friction = 1.0f;
	move_x = 0.0f;
	move_y = 0.0f;
	step = false;
	hit_left = false;
	hit_right = false;
	hit_top = false;
	hit_bottom = false;
	link_x = 1;
	link_y = 1;
	link_img_x1 = -1;
	link_img_x2 = -1;
	link_img_y1 = -1;
	link_img_y2 = -1;
}

AbstractMapChip::~AbstractMapChip(){

}

//���삷�邩���擾
bool AbstractMapChip::GetLiveFlag() {
	return live_flag;
}

//���삷�邩��ݒ�
void AbstractMapChip::SetLiveFlag(bool flag) {
	live_flag = flag;
}

//�`�悷�邩���擾
bool AbstractMapChip::GetDrawFlag() {
	return draw_flag;
}

//�`�悷�邩��ݒ�
void AbstractMapChip::SetDrawFlag(bool flag) {
	draw_flag = flag;
}

//�A������摜��ݒ�
void AbstractMapChip::SetLinkImgX(int ini_x1, int ini_x2) {
	link_img_x1 = ini_x1;
	link_img_x2 = ini_x2;
}

//�A������摜��ݒ�
void AbstractMapChip::SetLinkImgY(int ini_y1, int ini_y2) {
	link_img_y1 = ini_y1;
	link_img_y2 = ini_y2;
}

//��O��x���W��Ԃ�
float AbstractMapChip::GetLastX() {
	return last_x;
}

//��O��x���W��ݒ�
void AbstractMapChip::SetLastX(float set_x) {
	last_x = set_x;
}

//��O��y���W��Ԃ�
float AbstractMapChip::GetLastY() {
	return last_y;
}

//��O��y���W��ݒ�
void AbstractMapChip::SetLastY(float set_y) {
	last_y = set_y;
}

//x�����̈ړ��ʂ��擾
float AbstractMapChip::GetAmountX() {
	return x - last_x;
}

//y�����̈ړ��ʂ��擾
float AbstractMapChip::GetAmountY() {
	return y - last_y;
}

//�}�b�v�`�b�v�̉��̑傫����Ԃ�
int AbstractMapChip::GetSizeX() {
	return size_x;
}

//�}�b�v�`�b�v�̉��̑傫����ݒ�
void AbstractMapChip::SetSizeX(int set_size) {
	size_x = set_size;
}

//�}�b�v�`�b�v�̏c�̑傫����Ԃ�
int AbstractMapChip::GetSizeY() {
	return size_y;
}

//�}�b�v�`�b�v�̏c�̑傫����ݒ�
void AbstractMapChip::SetSizeY(int set_size) {
	size_y = set_size;
}

//���̃}�b�v�ɓ����邩���擾
bool AbstractMapChip::GetHitMap() {
	return hit_map;
}

//���̃}�b�v�ɓ����邩��ݒ�
void AbstractMapChip::SetHitMap(bool flag) {
	hit_map = flag;
}

//���蔲���邩���擾
bool AbstractMapChip::GetThrough() {
	return through;
}

//���蔲���邩��ݒ�
void AbstractMapChip::SetThrough(bool flag) {
	through = flag;
}

//�󂹂邩���擾
int AbstractMapChip::GetBreakable() {
	return breakable;
}

//�󂹂邩��ݒ�
void AbstractMapChip::SetBreakable(int set_bre) {
	breakable = set_bre;
}

//���C���擾
float AbstractMapChip::GetFriction() {
	return friction;
}

//���C���擾
void AbstractMapChip::SetFriction(float set_fri) {
	friction = set_fri;
}

//����Ă���L�����ɑ΂���x�����̑��x��Ԃ�
float AbstractMapChip::GetMoveX() {
	return move_x;
}

//����Ă���L�����ɑ΂���x�����̑��x��ݒ�
void AbstractMapChip::SetMoveX(float set_x) {
	move_x = set_x;
}

//����Ă���L�����ɑ΂���y�����̑��x��Ԃ�
float AbstractMapChip::GetMoveY() {
	return move_y;
}

//����Ă���L�����ɑ΂���y�����̑��x��ݒ�
void AbstractMapChip::SetMoveY(float set_y) {
	move_y = set_y;
}

//�L����������Ă��邩���擾
bool AbstractMapChip::GetStep() {
	return step;
}

//�L����������Ă��邩��ݒ�
void AbstractMapChip::SetStep(bool flag) {
	step = flag;
}

//�����ɍU�����������������擾
bool AbstractMapChip::GetHitLeft() {
	return hit_left;
}

//�����ɍU����������������ݒ�
void AbstractMapChip::SetHitLeft(bool flag) {
	hit_left = flag;
}

//�E���ɍU�����������������擾
bool AbstractMapChip::GetHitRight() {
	return hit_right;
}

//�E���ɍU����������������ݒ�
void AbstractMapChip::SetHitRight(bool flag) {
	hit_right = flag;
}

//�㑤�ɍU�����������������擾
bool AbstractMapChip::GetHitTop() {
	return hit_top;
}

//�㑤�ɍU����������������ݒ�
void AbstractMapChip::SetHitTop(bool flag) {
	hit_top = flag;
}

//�����ɍU�����������������擾
bool AbstractMapChip::GetHitBottom() {
	return hit_bottom;
}

//�����ɍU����������������ݒ�
void AbstractMapChip::SetHitBottom(bool flag) {
	hit_bottom = flag;
}

//�A�������}�b�v�`�b�v����ݒ�
void AbstractMapChip::SetLinkX(int ini_link) {
	link_x = ini_link;
}

//�A�������}�b�v�`�b�v����ݒ�
void AbstractMapChip::SetLinkY(int ini_link) {
	link_y = ini_link;
}