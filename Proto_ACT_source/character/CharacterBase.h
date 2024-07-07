#pragma once
#include "DxLib.h"
#include "..\system\Fps.h"
#include "..\system\Image.h"
#include "..\system\Key.h"
#include "..\system\Sound.h"
#include "..\camera\Camera.h"
#include "..\tool\Display.h"
#include "..\tool\Calculation.h"
#include <math.h>
#include <vector>
#include <memory>

struct HitStruct
{
	//当たり判定の構造体
	float x; //x座標
	float y; //y座標
	float distance; //本体との直線距離
	float angle; //初期の角度
	float size; //大きさ
	bool check_bottom = true; //足下の判定を行うか
	bool check_top = true; //頭上の判定を行うか
	bool check_left = true; //左の判定を行うか
	bool check_right = true; //右の判定を行うか
};

struct JointStruct
{
	//間接の構造体
	float x; //座標
	float y;
	float local_angle; //自分の角度
	float total_angle; //基と合わせた角度
	float angle_max; //角度の上限
	float angle_min; //角度の下限
	float axis_x; //回転軸（付け根）のx座標
	float axis_y; //回転軸（付け根）のy座標
	float dist; //先端への距離
};

class Key;
class Sound;
class Image;
class Fps;
class MapChipManager;
class Camera;

class CharacterBase{
protected:

	std::vector<HitStruct> hit; //当たり判定

	bool live_flag; //表示するか
	bool end_flag; //消去するか
	int end_time; //消えるまでの時間
	bool hit_flag; //当たり判定
	int image_num; //表示する画像
	int trance; //透明度
	int time; //タイマー
	int hp; //HP
	int max_hp; //HPの最大値
	float x; //x座標
	float y; //y座標
	float base_x; //元々のx座標
	float base_y; //元々のy座標
	float sx; //x方向の速度
	float sy; //y方向の速度
	float angle; //角度
	float spin_speed; //回転速度
	bool reverse; //反転しているか
	float ex_rate; //表示倍率
	int jump_time; //ジャンプしている時間
	bool jump_flag; //ジャンプしているか
	bool flying_flag; //飛んでいるか
	bool damaged; //ダメージを受けているか
	int damage_time; //ダメージ動作の時間
	bool hit_map; //マップチップに当たるか
	bool adjusted; //マップチップと接触したか

	void SetJoint(JointStruct& joint, float ax, float ay, float set_x, float set_y, float angle_max, float angle_min); //関節情報を設定（関節、回転軸の位置、初期位置、角度の上限、下限）
	void SetHit(float cx, float cy, float hit_size); //当たり判定の配置（x,y座標、当たり判定の大きさ）
	void JointUpdate(std::vector<JointStruct>& joint, float bx, float by, float bangle); //関節の位置を設定（関節、基の座標、角度）
	void IkSetting(std::vector<JointStruct>& joint, float speed, float dx, float dy); //インバースキネマティクス（関節、速度、目標の座標）
	void ZoomJoint(std::vector<JointStruct>& joint, float zoom_limit, float dx, float dy); //多関節を伸縮させる（関節、伸ばせる限界、目標の座標）

public:
	CharacterBase(); //コンストラクタ
	virtual ~CharacterBase(); //デストラクタ

	bool GetEndFlag(); //消去するかを取得
	void SetEndFlag(bool flag); //消去するかを設定
	int GetEndTime(); //消滅までの時間を返す
	void SetEndTime(int set_time); //消滅までの時間を設定(時間)
	bool GetHitFlag(); //当たり判定を取得
	void SetHitFlag(bool flag); //当たり判定を設定
	void SetTrance(int set_trance); //透明度を設定
	int GetTime(); //時間を返す
	void SetTime(int set_time); //時間を設定(時間)
	int GetHp(); //HPを返す
	void SetHp(int set_hp); //HPを設定(HP)
	void SetMaxHp(int set_hp); //最大HPを設定(HP)
	float GetX(); //x座標を返す
	void SetX(float set_x); //x座標を設定
	float GetY(); //y座標を返す
	void SetY(float set_y); //y座標を設定
	float GetBaseX(); //元のx座標を返す
	void SetBaseX(float set_x); //元のx座標を設定
	float GetBaseY(); //元のy座標を返す
	void SetBaseY(float set_y); //元のy座標を設定
	void SetSpeed(float speed); //角度を基に速度を設定
	float GetXSpeed(); //x方向の速度を返す
	void SetXSpeed(float set_x); //x方向の速度を設定
	float GetYSpeed(); //y方向の速度を返す
	void SetYSpeed(float set_y); //y方向の速度を設定
	float GetAngle(); //角度を取得
	void SetAngle(float set_angle); //角度を設定(角度)
	float GetSpinSpeed(); //回転速度を取得
	void SetSpinSpeed(float set_angle); //回転速度を設定(角度)
	bool GetReverse(); //向きを取得
	void SetReverse(bool flag); //向きを設定
	void SetExRate(float set_rate); //表示倍率を設定
	bool GetFlying(); //飛んでいるかを取得
	virtual void SetFlying(bool flag); //飛んでいるかを設定
	virtual bool GetDamaged(); //ダメージを受けているかを取得
	virtual bool GetHitMap(); //マップチップに当たるかを取得
	virtual void SetHitMap(bool flag); //マップチップに当たるかを設定

	void HitUpdate(); //当たり判定の更新
	void DrawHit(std::shared_ptr<Camera> camera); //当たり判定の描画

	virtual bool HitCheckChara(float cx, float cy, float hit_size, bool check_hit = true); //キャラクターとの当たり判定(キャラのx,y座標、当たり判定の大きさ、当たり判定の有無を確認するか)
	virtual void Timer(); //タイマー関連の更新

	virtual void AbsUpdate() = 0; //必ず行う更新
	virtual void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) = 0; //描画
};