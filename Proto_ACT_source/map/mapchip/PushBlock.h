#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"

//押せるブロック

class PushBlock : public AbstractMapChip {
protected:
	bool pushed_flag; //押されたか
	float next_x; //目的のx座標
	float base_sx; //基となる速度
public:
	PushBlock(MapChipManager* man, int num); //コンストラクタ(番号)
	~PushBlock(); //デストラクタ
	void AbsUpdate(); //必ず行う更新
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
