#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"

//基本的な雑魚（エーヘイ）突撃

class Erhei4 : public AbstractEnemy {
protected:

public:
	Erhei4(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Erhei4(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Defeat(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) override; //やられた時の動作
	void Update(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
