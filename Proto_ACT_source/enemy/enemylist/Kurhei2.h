#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"

//飛行雑魚（クーヘイ）上下のみ

class Kurhei2 : public AbstractEnemy {
protected:
	int hundle_num; //表示する画像
	float speed_angle; //速度用の角度
public:
	Kurhei2(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Kurhei2(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Defeat(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) override; //やられた時の動作
	void Update(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
