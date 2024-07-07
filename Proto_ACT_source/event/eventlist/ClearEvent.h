#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"

//クリアイベント

class ClearEvent : public AbstractEvent {
protected:
	int wait_time; //待ち時間
public:
	ClearEvent(EventManager* man, int waiting, bool stop_player, bool stop_enemy); //コンストラクタ(待ち時間、自機を止めるか、敵を止めるか)
	~ClearEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //描画
};
