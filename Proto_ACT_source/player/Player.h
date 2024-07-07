#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../bullet/BulletManager.h"
#include "../enemy/EnemyManager.h"
#include "../effect/EffectManager.h"
#include "../camera/Camera.h"
#include <memory>

class MapChipManager;
class BulletManager;
class EnemyManager;
class EffectManager;
class AbstractMapChip;
class AbstractBullet;
class AbstractEnemy;
class AbstractEffect;
class AbstractItem;
class Camera;

typedef enum {
	//キャラの動作
	Move_Stand, //静止
	Move_Walk, //歩行
	Move_Jump, //ジャンプ
	Move_Attack, //攻撃
	Move_Dash //ダッシュ
} MoveSet;

struct AttackStruct
{
	//攻撃の構造体
	bool flag; //攻撃しているか
	int time; //攻撃している時間
	bool stop; //攻撃中に足を止めるか
	int energy; //攻撃エネルギー
	int res_time; //エネルギーが回復するまでの時間
};

struct PlayerPartsStruct
{
	//パーツの構造体
	float x; //座標
	float y;
	float angle; //角度
	float total_angle; //角度の合計
	float def_angle; //計算用の角度
	float def_distance; //計算用の距離
	float spin_angle; //回転軸の位置を求める角度
	float spin_point; //回転軸の位置
};

class Player : public CharacterBase{
private:
	void Control(std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //自機の操作
	void DamageAction(); //ダメージ動作
	void Move(std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //移動
	void SetKeyRecord(std::shared_ptr<Key> key); //キーの履歴を更新
	bool RecordCheck(bool record[], int point = 0); //入力履歴の確認(渡す列、探し始める点)
	void HitUpdate(); //当たり判定の更新
	void SetGraphic(); //表示する画像を決定
	void SetParts(); //パーツをそろえる
	void Attack1(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //攻撃1
	void Attack2(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //攻撃2
	void Attack3(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //攻撃3
	void Attack4(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //攻撃4

	bool jumped; //最後にジャンプしたときから、ジャンプボタンが押しっぱなしか
	bool through_flag; //すり抜けているか
	int move_type; //行っている動作
	int move_time; //動作の時間
	int weapon; //使用する武器
	int handle; //表示する画像の番号
	int inv_time; //無敵時間
	bool draw_flag; //描画するか
	bool move_flag; //操作できるか
	int key_num; //持っている鍵の数
	int weapon_max; //使用できる武器の数
	const float move_speed = 8.0f; //基となる移動速度
	const int max_energy = 4; //最大エネルギー
	const int res_time = 30; //エネルギーが回復するまでの時間

	AttackStruct attack;
	using func = void (Player::*)(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound);
	std::vector<func> attack_move;
	std::shared_ptr<AbstractBullet> player_bullet; //自分が撃った弾
	std::shared_ptr<AbstractEffect> catch_effect; //ビーム用のエフェクト
	std::shared_ptr<AbstractMapChip> step_mapchip; //乗っているマップチップ

	PlayerPartsStruct body, head, left_leg, right_leg, left_arm, right_arm; //各パーツ
	
	bool commando[BUTTON][RECORD]; //入力したキーの履歴
	bool jump_book[RECORD]; //ジャンプの事前入力

	int message_font; //フォント情報

public:
	Player(); //コンストラクタ
	~Player(); //デストラクタ
	void Reset(); //初期化
	void AdjustPosition(std::shared_ptr<MapChipManager> map, bool event_flag); //位置の調節
	void AttackCheck(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //攻撃
	void HitCheckEnemy(std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //敵に当たっているか
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet, std::shared_ptr<Sound> sound); //弾に当たっているか
	bool HitCheckItem(float cx, float cy, float hit_size); //アイテムに当たっているか(キャラのx,y座標、当たり判定の大きさ)
	void SetDrawFlag(bool flag); //描画するか設定
	void SetMoveFlag(bool flag); //操作できるか設定
	int GetKeyNum(); //鍵の数を取得
	void SetKeyNum(int num); //鍵の数を設定
	void SetWeaponMax(int num); //武器の数を設定
	void AbsUpdate(); //必ず行う更新
	void Update(std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //描画
};