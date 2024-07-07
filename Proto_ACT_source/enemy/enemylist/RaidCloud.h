#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"

//ボス2（レイドクラウド）

class RaidCloud : public AbstractEnemy {
protected:
	int pattern; //攻撃パターン
	int parts_num; //パーツ数
	float parts_angle; //パーツ配置の起点

	float parts_distance;

	void Pattern1(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //攻撃1（ばらまき）
	void Pattern2(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //攻撃2（突進）
	void Pattern3(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //攻撃3（上移動）
public:
	RaidCloud(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~RaidCloud(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Defeat(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) override; //やられた時の動作
	void Update(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
