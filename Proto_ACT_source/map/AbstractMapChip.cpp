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

//動作するかを取得
bool AbstractMapChip::GetLiveFlag() {
	return live_flag;
}

//動作するかを設定
void AbstractMapChip::SetLiveFlag(bool flag) {
	live_flag = flag;
}

//描画するかを取得
bool AbstractMapChip::GetDrawFlag() {
	return draw_flag;
}

//描画するかを設定
void AbstractMapChip::SetDrawFlag(bool flag) {
	draw_flag = flag;
}

//連結する画像を設定
void AbstractMapChip::SetLinkImgX(int ini_x1, int ini_x2) {
	link_img_x1 = ini_x1;
	link_img_x2 = ini_x2;
}

//連結する画像を設定
void AbstractMapChip::SetLinkImgY(int ini_y1, int ini_y2) {
	link_img_y1 = ini_y1;
	link_img_y2 = ini_y2;
}

//一つ前のx座標を返す
float AbstractMapChip::GetLastX() {
	return last_x;
}

//一つ前のx座標を設定
void AbstractMapChip::SetLastX(float set_x) {
	last_x = set_x;
}

//一つ前のy座標を返す
float AbstractMapChip::GetLastY() {
	return last_y;
}

//一つ前のy座標を設定
void AbstractMapChip::SetLastY(float set_y) {
	last_y = set_y;
}

//x方向の移動量を取得
float AbstractMapChip::GetAmountX() {
	return x - last_x;
}

//y方向の移動量を取得
float AbstractMapChip::GetAmountY() {
	return y - last_y;
}

//マップチップの横の大きさを返す
int AbstractMapChip::GetSizeX() {
	return size_x;
}

//マップチップの横の大きさを設定
void AbstractMapChip::SetSizeX(int set_size) {
	size_x = set_size;
}

//マップチップの縦の大きさを返す
int AbstractMapChip::GetSizeY() {
	return size_y;
}

//マップチップの縦の大きさを設定
void AbstractMapChip::SetSizeY(int set_size) {
	size_y = set_size;
}

//他のマップに当たるかを取得
bool AbstractMapChip::GetHitMap() {
	return hit_map;
}

//他のマップに当たるかを設定
void AbstractMapChip::SetHitMap(bool flag) {
	hit_map = flag;
}

//すり抜けるかを取得
bool AbstractMapChip::GetThrough() {
	return through;
}

//すり抜けるかを設定
void AbstractMapChip::SetThrough(bool flag) {
	through = flag;
}

//壊せるかを取得
int AbstractMapChip::GetBreakable() {
	return breakable;
}

//壊せるかを設定
void AbstractMapChip::SetBreakable(int set_bre) {
	breakable = set_bre;
}

//摩擦を取得
float AbstractMapChip::GetFriction() {
	return friction;
}

//摩擦を取得
void AbstractMapChip::SetFriction(float set_fri) {
	friction = set_fri;
}

//乗っているキャラに対するx方向の速度を返す
float AbstractMapChip::GetMoveX() {
	return move_x;
}

//乗っているキャラに対するx方向の速度を設定
void AbstractMapChip::SetMoveX(float set_x) {
	move_x = set_x;
}

//乗っているキャラに対するy方向の速度を返す
float AbstractMapChip::GetMoveY() {
	return move_y;
}

//乗っているキャラに対するy方向の速度を設定
void AbstractMapChip::SetMoveY(float set_y) {
	move_y = set_y;
}

//キャラが乗っているかを取得
bool AbstractMapChip::GetStep() {
	return step;
}

//キャラが乗っているかを設定
void AbstractMapChip::SetStep(bool flag) {
	step = flag;
}

//左側に攻撃が当たったかを取得
bool AbstractMapChip::GetHitLeft() {
	return hit_left;
}

//左側に攻撃が当たったかを設定
void AbstractMapChip::SetHitLeft(bool flag) {
	hit_left = flag;
}

//右側に攻撃が当たったかを取得
bool AbstractMapChip::GetHitRight() {
	return hit_right;
}

//右側に攻撃が当たったかを設定
void AbstractMapChip::SetHitRight(bool flag) {
	hit_right = flag;
}

//上側に攻撃が当たったかを取得
bool AbstractMapChip::GetHitTop() {
	return hit_top;
}

//上側に攻撃が当たったかを設定
void AbstractMapChip::SetHitTop(bool flag) {
	hit_top = flag;
}

//下側に攻撃が当たったかを取得
bool AbstractMapChip::GetHitBottom() {
	return hit_bottom;
}

//下側に攻撃が当たったかを設定
void AbstractMapChip::SetHitBottom(bool flag) {
	hit_bottom = flag;
}

//連結したマップチップ数を設定
void AbstractMapChip::SetLinkX(int ini_link) {
	link_x = ini_link;
}

//連結したマップチップ数を設定
void AbstractMapChip::SetLinkY(int ini_link) {
	link_y = ini_link;
}