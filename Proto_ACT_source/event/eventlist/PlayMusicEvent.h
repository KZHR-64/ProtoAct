#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include <iostream>
#include <string>
#include <sstream>

//BGM再生イベント

class PlayMusicEvent : public AbstractEvent {
protected:
	int bgm_num; //BGM番号
public:
	PlayMusicEvent(EventManager* man, int num, bool stop_player, bool stop_enemy); //コンストラクタ(BGM番号、自機を止めるか、敵を止めるか)
	~PlayMusicEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //描画
};
