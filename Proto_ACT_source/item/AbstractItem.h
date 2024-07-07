#pragma once
#include "../character/CharacterBase.h"
#include "ItemManager.h"
#include "../Define.h"
#include "../player/Player.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../tool/Display.h"
#include <vector>
#include <memory>

class ItemManager;
class BulletManager;
class Player;
class EnemyManager;
class MapChipManager;
class EffectManager;
class AbstractMapChip;

class AbstractItem : public CharacterBase{
protected:
	ItemManager* manager;

	bool hit_player; //自機に当たるか
	bool hit_enemy; //敵に当たるか
	bool hit_map; //マップチップに当たるか

public:
	AbstractItem(ItemManager* man, int num, float ini_x, float ini_y); //コンストラクタ(画像の番号、座標)
	~AbstractItem(); //デストラクタ

	bool GetHitPlayer(); //自機に当たるかを取得
	void SetHitPlayer(bool flag); //自機に当たるかを設定
	bool GetHitEnemy(); //敵に当たるかを取得
	void SetHitEnemy(bool flag); //敵に当たるかを設定
	bool GetHitMap(); //マップチップに当たるかを取得
	void SetHitMap(bool flag); //マップチップに当たるかを設定

	bool HitCheckPlayer(std::shared_ptr<Player> player); //プレイヤーとの当たり判定
	void HitCheckMap(std::shared_ptr<MapChipManager> map); //マップチップとの当たり判定
	bool HitCheckChara(float cx, float cy, float hit_size); //キャラクターとの当たり判定(キャラのx,y座標、当たり判定の大きさ)

	virtual void ItemGet(std::shared_ptr<Player> player, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) = 0; //アイテム取得時の処理
	virtual void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) = 0;
};