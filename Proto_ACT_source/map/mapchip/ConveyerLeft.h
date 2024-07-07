#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//ベルトコンベア（左）

class ConveyerLeft : public AbstractMapChip{
protected:

public:
	ConveyerLeft(MapChipManager* man, int num); //コンストラクタ(番号)
	~ConveyerLeft(); //デストラクタ
	void AbsUpdate(); //必ず行う更新
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};
