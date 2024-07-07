#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "AbstractItem.h"
#include "../main/Parameter.h"
#include "../player/Player.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
#include "../camera/Camera.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../system/Sound.h"
#include "../tool/Display.h"
#include <map>
#include <list>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class AbstractItem;
class Player;
class EnemyManager;
class MapChipManager;
class EffectManager;
class Camera;

struct ItemDataStruct
{
	//アイテム情報の構造体
	int type; //種類
	int image; //表示する画像
	bool hit_player; //自機に当たるか
	bool hit_enemy; //敵に当たるか
	bool hit_map; //マップチップに当たるか
};

class ItemManager {
private:
	std::map<int, ItemDataStruct> item_data; //アイテム情報
	std::list<std::shared_ptr<AbstractItem>> item; //アイテム

	void SetData(); //アイテム情報の設定
	void EraseCheck(); //消えるか確認

public:
	ItemManager(); //コンストラクタ
	~ItemManager(); //デストラクタ
	void Reset(); //初期化
	void SetStandby(std::string file_name); //アイテムをマップに配置
	std::shared_ptr<AbstractItem> SetItem(int num, float ini_x, float ini_y); //アイテムの配置(データの番号、座標)
	void HitCheckMap(std::shared_ptr<MapChipManager> map); //マップチップとの当たり判定
	void HitCheckPlayer(std::shared_ptr<Player> player, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //プレイヤーとの当たり判定(キャラのx,y座標、当たり判定の大きさ、自機に当たるか敵に当たるか)
	std::shared_ptr<AbstractItem> HitCheckChara(float cx, float cy, float hit_size); //キャラクターとの当たり判定(キャラのx,y座標、当たり判定の大きさ)

	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //描画
};