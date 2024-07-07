#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"

//一定時間停止するイベント

class WaitEvent : public AbstractEvent{
protected:
	int wait_time; //待ち時間
public:
	WaitEvent(EventManager* man, int waiting, bool stop_player, bool stop_enemy); //コンストラクタ(待ち時間、自機を止めるか、敵を止めるか)
	~WaitEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //描画
};
