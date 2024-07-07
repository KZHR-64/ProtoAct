#pragma once
#include "../AbstractItem.h"

//ドアの鍵

class DoorKey : public AbstractItem {
protected:
	std::shared_ptr<AbstractEffect> mark; //エフェクト
public:
	DoorKey(ItemManager* man, int num, float ini_x, float ini_y); //コンストラクタ(番号)
	~DoorKey(); //デストラクタ
	void ItemGet(std::shared_ptr<Player> player, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //アイテム取得時の処理
	void AbsUpdate(); //必ず行う更新
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
