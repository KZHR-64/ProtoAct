#pragma once
#include "../AbstractBullet.h"
#include "../Define.h"

//自機狙い弾

class LockShoot : public AbstractBullet {
protected:
	
public:
	LockShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //コンストラクタ(画像の番号、座標、速度、角度)
	~LockShoot(); //デストラクタ
	void AbsUpdate(); //必ず行う更新
	void Erase(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //消える時の動作
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<ItemManager> item, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
