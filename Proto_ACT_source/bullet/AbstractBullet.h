#pragma once
#include "../character/CharacterBase.h"
#include "BulletManager.h"
#include "../Define.h"
#include "../player/Player.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
#include "../item/ItemManager.h"
#include "../item/AbstractItem.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../system/Sound.h"
#include "../tool/Display.h"
#include <vector>
#include <memory>

class BulletManager;
class Player;
class EnemyManager;
class MapChipManager;
class EffectManager;
class ItemManager;
class AbstractMapChip;
class AbstractItem;

class AbstractBullet : public CharacterBase {
protected:
	BulletManager* manager;

	int damage; //ダメージ量
	float base_speed; //始めに設定された速度
	bool breakable; //壊せるか
	bool hit_player; //自機に当たるか
	bool hit_enemy; //敵に当たるか
	bool hit_map; //マップチップに当たるか
	int break_power; //マップチップを壊す力


public:
	AbstractBullet(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //コンストラクタ(画像の番号、座標、速度、角度)
	~AbstractBullet(); //デストラクタ

	int GetDamage(); //ダメージ値を返す
	void SetDamage(int set_damage); //ダメージ値を設定(ダメージ値)
	bool GetBreakable(); //壊せるかを取得
	void SetBreakable(bool flag); //壊せるかを設定
	bool GetHitPlayer(); //自機に当たるかを取得
	void SetHitPlayer(bool flag); //自機に当たるかを設定
	bool GetHitEnemy(); //敵に当たるかを取得
	void SetHitEnemy(bool flag); //敵に当たるかを設定
	bool GetHitMap(); //マップチップに当たるかを取得
	void SetHitMap(bool flag); //マップチップに当たるかを設定
	int GetBreakPower(); //マップチップの破壊力を返す
	void SetBreakPower(int set_power); //マップチップの破壊力を設定

	int HitCheckChara(float cx, float cy, float hit_size); //キャラクターとの当たり判定(キャラのx,y座標、当たり判定の大きさ)
	void HitCheckMap(std::shared_ptr<MapChipManager> map); //マップチップとの当たり判定

	virtual void Erase(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) = 0; //消える時の動作
	virtual void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<ItemManager> item, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera) = 0; //更新
};