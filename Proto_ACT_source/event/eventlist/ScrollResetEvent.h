#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include <iostream>
#include <string>
#include <sstream>

//スクロール位置調整イベント

class ScrollResetEvent : public AbstractEvent {
protected:
public:
	ScrollResetEvent(EventManager* man, bool stop_player, bool stop_enemy); //コンストラクタ(座標、自機を止めるか、敵を止めるか)
	~ScrollResetEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //描画
};
