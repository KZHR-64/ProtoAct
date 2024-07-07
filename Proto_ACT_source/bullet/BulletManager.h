#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "AbstractBullet.h"
#include "../main/Parameter.h"
#include "../player/Player.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
#include "../item/ItemManager.h"
#include "../camera/Camera.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../system/Sound.h"
#include "../tool/Display.h"
#include <map>
#include <list>
#include <vector>
#include <memory>

class AbstractBullet;
class Player;
class EnemyManager;
class MapChipManager;
class EffectManager;
class ItemManager;
class Camera;

struct BulletDataStruct
{
	//弾情報の構造体
	int type; //種類
	int image; //表示する画像
	bool breakable; //壊せるか
	bool hit_player; //自機に当たるか
	bool hit_enemy; //敵に当たるか
	bool hit_map; //マップチップに当たるか
	int damage; //ダメージ値
	int break_power; //マップチップを壊す力
};

class BulletManager {
private:
	std::map<int, BulletDataStruct> bullet_data; //弾情報
	std::list<std::shared_ptr<AbstractBullet>> bullet; //弾

	void SetData(); //弾情報の設定
	void EraseCheck(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //消えるか確認

public:
	BulletManager(); //コンストラクタ
	~BulletManager(); //デストラクタ
	void Reset(); //初期化
	std::shared_ptr<AbstractBullet> SetBullet(int num, float ini_x, float ini_y, float speed, float angle); //弾の配置(データの番号、座標、速度、角度)
	void HitCheckMap(std::shared_ptr<MapChipManager> map); //マップチップとの当たり判定
	int HitCheckChara(float cx, float cy, float hit_size, bool check_player, bool check_enemy); //キャラクターとの当たり判定(キャラのx,y座標、当たり判定の大きさ、自機に当たるか敵に当たるか)
	
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<ItemManager> item, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //描画
};