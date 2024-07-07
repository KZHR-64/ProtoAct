#pragma once
#include "ModeBase.h"
#include "Parameter.h"
#include "..\player\Player.h"
#include "..\map\MapChipManager.h"
#include "..\enemy\EnemyManager.h"
#include "..\bullet\BulletManager.h"
#include "..\effect\EffectManager.h"
#include "..\item\ItemManager.h"
#include "..\event\EventManager.h"
#include "..\camera\Camera.h"
#include <memory>

class GameBase;
class Player;
class MapChipManager;
class EnemyManager;
class BulletManager;
class EffectManager;
class ItemManager;
class EventManager;
class Camera;

class Game : public ModeBase {
private:
	std::shared_ptr<Player> player;
	std::shared_ptr<MapChipManager> map;
	std::shared_ptr<EnemyManager> enemy;
	std::shared_ptr<BulletManager> bullet;
	std::shared_ptr<ItemManager> item;
	std::shared_ptr<EventManager> event;
	std::shared_ptr<EffectManager> effect;
	int stage_num; //ステージ番号
	int live; //残機
	bool pause_flag; //ポーズ画面を開いているか
	int cursor; //ポーズ画面のカーソル
	
	void GameUpdate(); //ゲームの更新
	void PauseUpdate(); //ポーズ画面の更新

public:
	Game(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~Game(); //デストラクタ
	void Load(); //事前のロード
	void Restart(); //再開
	void Update(); //更新
	void Draw(); //描画
};