#pragma once
#include "DxLib.h"
#include "CharacterBase.h"

using namespace std;

CharacterBase::CharacterBase() {

	time = 0; //タイマーを初期化
	live_flag = true; //生存フラグを初期化
	end_flag = false; //消滅フラグを初期化
	end_time = -1; //消滅までの時間を初期化
	image_num = -1; //使用する画像を初期化
	trance = 255; //透明度を初期化
	hp = 1; //HPを初期化
	max_hp = hp; //最大HPを初期化
	x = 0.0f; //x座標を初期化
	y = 0.0f; //y座標を初期化
	base_x = x; //基となるx座標を初期化
	base_y = y; //基となるy座標を初期化
	sx = 0.0f; //x方向の速度を初期化
	sy = 0.0f; //y方向の速度を初期化
	reverse = false; //反転フラグを初期化
	angle = 0.0f; //角度を初期化
	spin_speed = 0.0f; //回転速度を初期化
	ex_rate = 1.0f; //表示倍率を初期化
	jump_time = 0; //ジャンプ時間を初期化
	jump_flag = false; //ジャンプフラグを初期化
	hit_flag = true; //当たり判定を初期化
	flying_flag = false; //飛行フラグを初期化
	damaged = false; //ダメージフラグを初期化
	damage_time = false; //ダメージ動作時間を初期化
	hit_map = true; //マップチップとの当たり判定を初期化
	adjusted = false; //マップチップに当たったかを初期化
}

CharacterBase::~CharacterBase() {
	hit.clear(); //当たり判定のメモリを解放
}

//関節情報を設定（関節、回転軸の位置、初期位置、先端への距離）
void CharacterBase::SetJoint(JointStruct& joint, float ax, float ay, float set_x, float set_y, float angle_max, float angle_min) {
	joint.axis_x = ax; //回転軸の位置を設定
	joint.axis_y = ay; //回転軸の位置を設定
	joint.angle_max = angle_max; //角度の上限を設定
	joint.angle_min = angle_min; //角度の下限を設定
	joint.dist = sqrtf((set_x * set_x) + (set_y * set_y)); //先端との距離を設定
	joint.local_angle = atan2f(set_y, set_x); //関節の角度を設定
}

//当たり判定の配置
void CharacterBase::SetHit(float cx, float cy, float hit_size) {
	HitStruct new_hit{};

	new_hit.angle = atan2f(cy, cx); //初期角度を設定
	new_hit.distance = sqrtf((cx * cx) + (cy * cy)); //本体との距離を設定
	new_hit.size = hit_size; //判定の大きさを設定
	new_hit.x = x;
	new_hit.y = y;

	hit.emplace_back(new_hit);
}

//関節の位置を設定
void CharacterBase::JointUpdate(vector<JointStruct>& joint, float bx, float by, float bangle) {
	if (joint.size() <= 0) return;

	//根元の位置を設定
	joint[0].total_angle = joint[0].local_angle + bangle; //角度を設定
	joint[0].x = bx + (joint[0].dist * cosf(joint[0].total_angle)); //座標を設定
	joint[0].y = by + (joint[0].dist * sinf(joint[0].total_angle)); //座標を設定

	for (unsigned int i = 1; i < joint.size(); i++)
	{
		joint[i].total_angle = joint[i].local_angle + joint[i - 1].total_angle; //角度を設定
		joint[i].x = joint[i - 1].x + (joint[i].dist * cosf(joint[i].total_angle)); //座標を設定
		joint[i].y = joint[i - 1].y + (joint[i].dist * sinf(joint[i].total_angle)); //座標を設定
	}
}

//インバースキネマティクス
void CharacterBase::IkSetting(std::vector<JointStruct>& joint, float speed, float dx, float dy){
	if (joint.size() <= 0) return;
	int joint_max = joint.size() - 1; //多関節の最後尾

	float dangle = Calculation::LockOn(joint[joint_max].x, joint[joint_max].y, dx, dy); //先端を動かすべき角度

	//角度を先端から求める
	for (unsigned int i = joint_max - 1; 0 < i; i--)
	{	
		//float cangle = Calculation::HomingSpin(joint[i].total_angle, sangle, joint[i].x, joint[i].y, dx, dy); //目標の角度
		//float dangle = cangle - joint[i].total_angle; //回転量
		//上限を超えない場合
		//if (joint[i].total_angle + joint[i].angle_max < cangle) {
		//	joint[i].total_angle += joint[i].angle_max; //上限値に設定
		//}
		//超える場合
		//else {
			//joint[i].total_angle = cangle; //角度を設定
		//}
		//下限を下回らない場合
		//if (joint[i].total_angle + joint[i].angle_min < cangle) {
		//	joint[i].total_angle += joint[i].angle_max; //上限値に設定
		//}
		//下回る場合
		//else {
			//joint[i].total_angle = cangle; //角度を設定
		//}
		//joint[joint_max].x = joint[i].x;
	}

	//座標を根元から求める
	for (unsigned int i = 1; i < joint.size(); i++)
	{

	}
}

//多関節を伸縮させる
void CharacterBase::ZoomJoint(std::vector<JointStruct>& joint, float zoom_limit, float dx, float dy) {

}

//当たり判定の更新
void CharacterBase::HitUpdate() {
	if (hit.size() <= 0) return;
	for (unsigned int i = 0; i < hit.size(); i++) {
		float direction = (reverse) ? -1.0f : 1.0f; //向きに応じた計算用
		hit[i].x = x + ((hit[i].distance * cosf(hit[i].angle + angle)) * direction);
		hit[i].y = y + (hit[i].distance * sinf(hit[i].angle + angle));
	}
}

//消去するかを取得
bool CharacterBase::GetEndFlag() {
	return end_flag;
}

//消去するかを設定
void CharacterBase::SetEndFlag(bool flag) {
	end_flag = flag;
}

//消滅までの時間を返す
int CharacterBase::GetEndTime() {
	return end_time;
}

//消滅までの時間を設定
void CharacterBase::SetEndTime(int set_time) {
	end_time = set_time;
}

//当たり判定を取得
bool CharacterBase::GetHitFlag() {
	return hit_flag;
}

//当たり判定を設定
void CharacterBase::SetHitFlag(bool flag) {
	hit_flag = flag;
}

//透明度を設定
void CharacterBase::SetTrance(int set_trance) {
	trance = set_trance;
}

//時間を返す
int CharacterBase::GetTime() {
	return time;
}

//時間を設定
void CharacterBase::SetTime(int set_time) {
	time = set_time;
}

//HPを返す
int CharacterBase::GetHp() {
	return hp;
}

//HPを設定
void CharacterBase::SetHp(int set_hp) {
	hp = set_hp;
}

//最大HPを設定
void CharacterBase::SetMaxHp(int set_hp) {
	max_hp = set_hp;
}

//x座標を返す
float CharacterBase::GetX() {
	return x;
}

//x座標を設定
void CharacterBase::SetX(float set_x) {
	x = set_x;
	HitUpdate();
}

//y座標を返す
float CharacterBase::GetY() {
	return y;
}

//y座標を設定
void CharacterBase::SetY(float set_y) {
	y = set_y;
	HitUpdate();
}

//元のx座標を返す
float CharacterBase::GetBaseX() {
	return x;
}

//元のx座標を設定
void CharacterBase::SetBaseX(float set_x) {
	x = set_x;
}

//元のy座標を返す
float CharacterBase::GetBaseY() {
	return y;
}

//元のy座標を設定
void CharacterBase::SetBaseY(float set_y) {
	y = set_y;
}

//角度を基に速度を設定
void CharacterBase::SetSpeed(float speed) {
	sx = speed * cosf(angle);
	sy = speed * sinf(angle);
}

//x方向の速度を返す
float CharacterBase::GetXSpeed() {
	return sx;
}

//x方向の速度を設定
void CharacterBase::SetXSpeed(float set_x) {
	sx = set_x;
}

//y方向の速度を返す
float CharacterBase::GetYSpeed() {
	return sy;
}

//y方向の速度を設定
void CharacterBase::SetYSpeed(float set_y) {
	sy = set_y;
}

//角度を取得
float CharacterBase::GetAngle() {
	return angle;
}

//角度を設定(角度)
void CharacterBase::SetAngle(float set_angle) {
	angle = set_angle;
}

//回転速度を取得
float CharacterBase::GetSpinSpeed() {
	return spin_speed;
}

//回転速度を設定(角度)
void CharacterBase::SetSpinSpeed(float set_angle) {
	spin_speed = set_angle;
}

//向きを取得
bool CharacterBase::GetReverse() {
	return reverse;
}

//向きを設定
void CharacterBase::SetReverse(bool flag) {
	reverse = flag;
}

//表示倍率を設定
void CharacterBase::SetExRate(float set_rate) {
	ex_rate = set_rate;
}

//飛んでいるかを取得
bool CharacterBase::GetFlying() {
	return flying_flag;
}

//飛んでいるかを設定
void CharacterBase::SetFlying(bool flag) {
	flying_flag = flag;
}

//ダメージを受けているかを取得
bool CharacterBase::GetDamaged() {
	return damaged;
}

//マップチップに当たるかを取得
bool CharacterBase::GetHitMap() {
	return hit_map;
}

//マップチップに当たるかを設定
void CharacterBase::SetHitMap(bool flag) {
	hit_map = flag;
}

//当たり判定の描画
void CharacterBase::DrawHit(shared_ptr<Camera> camera) {
	if (hit.empty()) return;
	for (auto& h : hit) {
		camera->HitDraw(h.x, h.y, h.size); //当たり判定を描画
	}
}

//キャラクターとの当たり判定
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

//タイマー関連の更新
void CharacterBase::Timer() {
	time++;
	if (0 < damage_time) {
		damage_time--;
		if (damage_time <= 0) {
			damaged = false;
		}
	}
}