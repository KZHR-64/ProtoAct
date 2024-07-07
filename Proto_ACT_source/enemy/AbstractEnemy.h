#pragma once
#include "../character/CharacterBase.h"
#include "EnemyManager.h"
#include "../Define.h"
#include "../player/Player.h"
//#include "../map/MapChipManager.h"
//#include "../map/AbstractMapChip.h"
//#include "../bullet/BulletManager.h"
//#include "../effect/EffectManager.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../tool/Display.h"
#include <memory>

class EnemyManager;
class Player;
class BulletManager;
class MapChipManager;
class EffectManager;
class AbstractMapChip;

class AbstractEnemy : public CharacterBase {
protected:
	EnemyManager* manager;

	std::vector<std::shared_ptr<AbstractEnemy>> parts; //パーツとして扱う敵
	AbstractEnemy* base_enemy; //本体

	bool boss_flag; //ボスキャラか


public:
	AbstractEnemy(EnemyManager* man, int num, float ini_x, float ini_y); //コンストラクタ(画像の番号、座標)
	~AbstractEnemy(); //デストラクタ

	AbstractEnemy* GetBase(); //本体を取得
	void SetBase(AbstractEnemy* base); //本体を設定
	bool GetBossFlag(); //ボスかを取得
	void SetBossFlag(int rank); //ボスかを設定(格)

	void AdjustPosition(std::shared_ptr<MapChipManager> map, std::shared_ptr<EffectManager> effect); //位置の調節
	void HitDamage(int damage_num, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //ダメージ処理(ダメージ値)
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //弾に当たっているか
	void HitCheckEnemy(float cx, float cy, float hit_size, std::shared_ptr<EffectManager> effect); //敵に当たっているか
	bool HitCheckChara(float cx, float cy, float hit_size, bool check_hit = true); //キャラクターとの当たり判定(キャラのx,y座標、当たり判定の大きさ、当たり判定の有無を確認するか)
	void Timer(); //タイマー関連の更新

	virtual void Defeat(std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound) = 0; //やられた時の動作
	virtual void Update(std::shared_ptr<Player> player, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera) = 0; //更新
};