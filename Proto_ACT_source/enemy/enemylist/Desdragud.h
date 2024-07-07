#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"

//ボス3（デスドラグド）

class Desdragud : public AbstractEnemy {
protected:
	bool move_flag; //移動するか
	int pattern; //攻撃パターン
	float head_distance, head_angle, arm1_distance, arm1_angle, arm2_distance, arm2_angle, leg1_distance, leg1_angle, leg2_distance, leg2_angle;
	float arm1_spin_distance, arm1_spin_angle, arm2_spin_distance, arm2_spin_angle, leg1_spin_distance, leg1_spin_angle, leg2_spin_distance, leg2_spin_angle;
	float head_x, head_y, arm1_x, arm1_y, arm2_x, arm2_y, leg1_x, leg1_y, leg2_x, leg2_y;

	void Pattern1(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //攻撃1（バリアとミサイル）
	void Pattern2(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //攻撃2（ミサイルと自機狙い）
	void Pattern3(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //攻撃3（突進）
public:
	Desdragud(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Desdragud(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Defeat(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) override; //やられた時の動作
	void Update(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
