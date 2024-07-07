#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"

//導火線

class FuseBlock : public AbstractMapChip {
protected:

public:
	FuseBlock(MapChipManager* man, int num); //コンストラクタ(番号)
	~FuseBlock(); //デストラクタ
	void AbsUpdate(); //必ず行う更新
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
