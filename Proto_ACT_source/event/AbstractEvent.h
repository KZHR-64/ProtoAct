#pragma once
#include "../character/CharacterBase.h"
#include "EventManager.h"
#include "../Define.h"
//#include "Map.h"
#include "../player/Player.h"
#include "../enemy/EnemyManager.h"
#include "../effect/EffectManager.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../system/Sound.h"
#include "../tool/Display.h"
#include <memory>

class EventManager;
class Player;
class EnemyManager;
class EffectManager;

class AbstractEvent{
protected:
	EventManager* manager;
	int time; //タイマー
	bool end_flag; //終了したか
	bool player_stop; //自機の動きを止めるか
	bool enemy_stop; //敵の動きを止めるか

public:
	AbstractEvent(EventManager* man, bool stop_player, bool stop_enemy); //コンストラクタ(自機を止めるか、敵を止めるか)
	~AbstractEvent(); //デストラクタ

	int GetTime(); //時間を返す
	void SetTime(int set_time); //時間を設定(時間)
	bool GetEndFlag(); //終了したか取得
	bool GetPlayerStop(); //自機を止めるか取得
	bool GetEnemyStop(); //敵を止めるか取得

	virtual void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound) = 0;
	virtual void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) = 0; //描画
};