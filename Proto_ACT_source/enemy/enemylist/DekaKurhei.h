#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"

//ボス1（デカクーヘイ）

class DekaKurhei : public AbstractEnemy {
protected:
	int hundle_num; //表示する画像
	bool move_flag; //移動するか
	int pattern; //攻撃パターン
	float parts1_distance, parts1_angle, parts2_distance, parts2_angle, parts3_distance, parts3_angle, parts4_distance, parts4_angle;
	float parts1_x, parts1_y, parts2_x, parts2_y, parts3_x, parts3_y, parts4_x, parts4_y;
	const int arm_num = 8; //関節の数

	std::vector<JointStruct> arm; //多関節の腕

	void Pattern1(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //攻撃1（低空で機関砲）
	void Pattern2(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //攻撃2（高空で機関砲）
	void Pattern3(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //攻撃3（爆撃）
public:
	DekaKurhei(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~DekaKurhei(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Defeat(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) override; //やられた時の動作
	void Update(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
