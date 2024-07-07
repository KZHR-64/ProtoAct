#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

//会話イベント

class TalkEvent : public AbstractEvent {
protected:
	std::string chara_name; //キャラクター名
	std::string message; //文章
public:
	TalkEvent(EventManager* man, std::string, std::string, bool stop_player, bool stop_enemy); //コンストラクタ(キャラ名、文章、自機を止めるか、敵を止めるか)
	~TalkEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //描画
};
