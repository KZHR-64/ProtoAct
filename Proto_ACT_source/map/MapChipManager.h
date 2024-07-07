#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "AbstractMapChip.h"
#include "../player/Player.h"
#include "../enemy/EnemyManager.h"
#include "../item/ItemManager.h"
#include "../event/EventManager.h"
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

class AbstractMapChip;
class WarpDoor;
class Player;
class EnemyManager;
class ItemManager;
class EventManager;
class Camera;

struct MapChipDataStruct
{
	//マップチップ情報の構造体
	int type; //種類
	int image; //表示する画像
	int size_x; //横の大きさ
	int size_y; //縦の大きさ
	bool through; //すり抜けるか
	int breakable; //壊せるか(0=壊せない、1=脆い、2=硬い)
	bool hit_map; //他のマップチップに当たるか
	bool flying; //浮いているか
	float friction; //摩擦
	int link_x1; //連結するマップチップ1（横）（基の番号よりどれだけ大きいか）
	int link_x2;//連結するマップチップ2（横）
};

struct EventDataStruct
{
	//イベント配置情報の構造体
	bool flag; //発生するか
	int num; //番号
	float x; //x座標
	float y; //y座標
};

struct MapDataStruct
{
	//マップ情報の構造体
	std::string back_name; //BGMと背景設定のファイル名
	std::string mapfile_name; //マップチップ配置のファイル名
	std::string mapfile_name2; //マップチップ配置のファイル名(見えない部分)
	std::string scroll_name; //スクロール情報のファイル名
	std::string enemy_name; //敵配置のファイル名
	std::string item_name; //アイテム配置のファイル名
	std::string warp_name; //ワープ扉配置のファイル名
	std::string warp_data_name; //ワープ情報のファイル名
	std::string event_name; //イベント配置のファイル名
	std::string event_data_name; //イベント情報のファイル名
};

struct BackStruct
{
	//背景の構造体
	int image; //画像
	float x; //座標(左下を基準とする)
	float y;
	float sx; //スクロールする速度(倍率)
	float sy;
	bool loop; //ループするか
};

struct WarpDataStruct
{
	//ワープ情報の構造体
	int next_num; //次のマップ番号
	int image; //表示する画像
	int size_x; //横の大きさ
	int size_y; //縦の大きさ
	float next_x; //次の座標
	float next_y;
	bool check_key; //キーの入力を確認するか
};

struct WarpStruct
{
	//ワープ扉の構造体
	int num; //参照する情報
	float x; //座標
	float y;
};

class MapChipManager{
private:
	std::list<std::shared_ptr<AbstractMapChip>> mapchip; //マップチップ
	std::vector<EventDataStruct> standby_event; //イベント
	std::vector<std::string> stage_data; //ステージ情報
	std::vector<MapDataStruct> map_data; //マップ情報
	std::map<int, MapChipDataStruct> mapchip_data; //マップチップ情報
	std::vector<BackStruct> back_data; //背景
	std::vector<WarpDataStruct> warp_data; //ワープ情報
	std::vector<WarpStruct> warp_door; //ワープ扉

	void SetData(); //マップチップ情報の設定
	void SetStageData(); //ステージ情報の設定
	void SetMapData(std::string file_name); //マップ情報の設定
	void SetBackData(std::shared_ptr<Image> image); //BGMと背景情報の設定
	void SetWarpData(); //ワープ情報の設定
	void MakeMapChip(); //マップチップの配置
	void MakeMapFront(); //マップチップの配置(見えない部分)
	void MakeMapScroll(std::shared_ptr<Camera> camera); //スクロール範囲の設定
	void MakeMapEvent(); //イベント開始位置の設定
	void MakeWarpDoor(); //ワープ扉の設定
	void WindowCheck(std::shared_ptr<AbstractMapChip>, std::shared_ptr<Camera> camera); //画面内に収まっているか確認
	void BackUpdate(std::shared_ptr<Image> image); //背景の更新
	void BackDraw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //背景の描画


	int stage_num; //ステージ番号
	int next_map; //次のマップ
	int warp_num; //使用するワープ扉
	bool warp_flag; //ワープするか
	int bgm; //再生するBGM
	float gravity; //重力

public:
	MapChipManager(int set_num); //コンストラクタ
	~MapChipManager(); //デストラクタ
	void Reset(); //初期化
	void MakeMap(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<ItemManager> item, std::shared_ptr<EventManager> event, std::shared_ptr<Image> image, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //マップの生成(自機、敵、アイテム、イベントのクラス)
	std::shared_ptr<AbstractMapChip> SetMapChip(int num, float ini_x, float ini_y, bool hit_map = true); //マップチップの配置(データの番号、座標、他マップチップとの当たり判定)
	bool HitCheck(float cx, float cy, float hit_size, int break_power, bool abs_check = false); //キャラがマップチップに当たっているか(キャラのx,y座標、当たり判定の大きさ、壊す側の強さ、当たり判定にかかわらず確認するか)
	std::shared_ptr<AbstractMapChip> HitCheckLeft(float cx, float cy, float hit_size); //キャラがマップチップに当たっているか(左の判定)(キャラのx,y座標、当たり判定の大きさ)
	std::shared_ptr<AbstractMapChip> HitCheckRight(float cx, float cy, float hit_size); //キャラがマップチップに当たっているか(右の判定)(キャラのx,y座標、当たり判定の大きさ)
	std::shared_ptr<AbstractMapChip> HitCheckTop(float cx, float cy, float hit_size); //キャラがマップチップに当たっているか(上の判定)(キャラのx,y座標、当たり判定の大きさ)
	std::shared_ptr<AbstractMapChip> HitCheckBottom(float cx, float cy, float hit_size); //キャラがマップチップに当たっているか(下の判定)(キャラのx,y座標、当たり判定の大きさ)
	void CheckStep(float cx, float cy, float hit_size); //キャラがマップチップに乗っているか(キャラのx,y座標、当たり判定の大きさ)
	float GetPlusSpeedX(float cx, float cy, float hit_size); //マップチップに乗っているキャラに足す速度を取得(キャラのx,y座標、当たり判定の大きさ)
	float GetPlusSpeedY(float cx, float cy, float hit_size); //マップチップに乗っているキャラに足す速度を取得(キャラのx,y座標、当たり判定の大きさ)
	void EventHitCheck(std::shared_ptr<EventManager> event, float cx, float cy); //キャラがイベント発生位置に当たっているか(キャラのx,y座標)
	void WarpHitCheck(std::shared_ptr<EventManager> event, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound, float cx, float cy); //キャラがワープ扉に当たっているか(キャラのx,y座標)
	bool GetWarpFlag(); //ワープするか取得
	std::shared_ptr<AbstractMapChip> HitCheckLeftMap(std::shared_ptr<AbstractMapChip> check_map); //マップチップが他のマップチップに当たっているか(左の判定)
	std::shared_ptr<AbstractMapChip> HitCheckRightMap(std::shared_ptr<AbstractMapChip> check_map); //マップチップが他のマップチップに当たっているか(右の判定)
	std::shared_ptr<AbstractMapChip> HitCheckTopMap(std::shared_ptr<AbstractMapChip> check_map); //マップチップが他のマップチップに当たっているか(上の判定)
	std::shared_ptr<AbstractMapChip> HitCheckBottomMap(std::shared_ptr<AbstractMapChip> check_map, bool plus_one = false); //マップチップが他のマップチップに当たっているか(下の判定、1ドット下をみるか)
	void AdjustPosition(); //位置の調節

	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Image> image, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound, std::shared_ptr<Camera> camera); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //描画
};