#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "AbstractEnemy.h"
#include "../player/Player.h"
#include "../map/MapChipManager.h"
#include "../effect/EffectManager.h"
#include "../camera/Camera.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../system/Sound.h"
#include "../tool/Display.h"
#include <map>
#include <list>
#include <vector>
#include <memory>

class Player;
class AbstractEnemy;
class MapChipManager;
class EffectManager;
class Camera;

struct EnemyDataStruct
{
	//敵情報の構造体
	int type; //種類
	int image; //表示する画像
	int hp; //HP
	int size_x; //横の大きさ
	int size_y; //縦の大きさ
	int rank; //格(0=雑魚、1=中ボス、2以上=ボス)
};

struct StandbyEnemyDataStruct
{
	//マップに配置する敵の構造体
	bool flag; //出現したか
	int num; //種類
	float x; //座標
	float y;
};

class EnemyManager {
private:
	std::map<int, EnemyDataStruct> enemy_data; //敵情報
	std::list<std::shared_ptr<AbstractEnemy>> enemy; //敵
	std::vector<StandbyEnemyDataStruct> standby_enemy; //マップに配置する敵

	bool boss_battle; //ボス戦を行っているか
	bool boss_flag; //ボスが出ているか
	bool midboss_flag; //中ボスが出ているか

	void SetData(); //敵情報の設定

public:
	EnemyManager(); //コンストラクタ
	~EnemyManager(); //デストラクタ
	void Reset(); //初期化
	void EraseCheck(std::shared_ptr<Camera> camera); //消えるか確認
	void SetStandby(std::string file_name); //敵をマップに配置
	std::shared_ptr<AbstractEnemy> SetEnemy(int num, float ini_x, float ini_y, AbstractEnemy* base = NULL); //敵の配置(データの番号、座標、本体)
	void SpawnCheck(std::shared_ptr<Camera> camera); //敵が出現できるか確認
	bool HitCheckChara(float cx, float cy, float hit_size, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, int damage = 0); //キャラクターとの当たり判定(キャラのx,y座標、x,y方向の大きさ、ダメージ)
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound); //弾に当たっているか
	void HitCheckEnemy(std::shared_ptr<EffectManager> effect); //敵に当たっているか
	bool GetBossFlag(); //ボス戦中か取得
	bool GetBeatBoss(); //ボスを倒したか取得
	
	void Update(std::shared_ptr<MapChipManager> map, std::shared_ptr<BulletManager> bullet, std::shared_ptr<Player> player, std::shared_ptr<EffectManager> effect, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //描画
};