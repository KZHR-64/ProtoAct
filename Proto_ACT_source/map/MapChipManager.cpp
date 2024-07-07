#pragma once
#include "DxLib.h"
#include "MapChipManager.h"
#include "./mapchip/NormalBlock.h"
#include "./mapchip/BombBlock.h"
#include "./mapchip/FuseBlock.h"
#include "./mapchip/PushBlock.h"
#include "./mapchip/LockedDoor.h"
#include "./mapchip/FallBlock.h"
#include "./mapchip/MassDriver.h"
#include "./mapchip/SpinMassDriver.h"
#include <math.h>

using namespace std;

MapChipManager::MapChipManager(int set_num){
	stage_num = set_num;
	next_map = 0;
	warp_num = 0;
	warp_flag = false;

	SetStageData();
	SetData();
	SetWarpData(); //ワープ情報を設定
}

MapChipManager::~MapChipManager(){
	stage_data.clear();
	mapchip.clear();
	mapchip_data.clear();
	standby_event.clear();
	back_data.clear();
	warp_data.clear();
	warp_door.clear();
}

//マップチップ情報の設定
void MapChipManager::SetData() {

	int num;

	ifstream ifs("data/map/mapchip_data.csv");

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ',');
		mapchip_data[num].type = atoi(s.c_str()); //種類を取得
		getline(ss, s, ',');
		mapchip_data[num].image = atoi(s.c_str()); ////画像の番号を取得
		getline(ss, s, ',');
		mapchip_data[num].size_x = atoi(s.c_str()); //横の大きさを取得
		getline(ss, s, ',');
		mapchip_data[num].size_y = atoi(s.c_str()); //縦の大きさを取得
		getline(ss, s, ',');
		mapchip_data[num].through = (1 == atoi(s.c_str())); //すり抜けるかを取得
		getline(ss, s, ',');
		mapchip_data[num].breakable = atoi(s.c_str()); //壊せるかを取得
		getline(ss, s, ',');
		mapchip_data[num].hit_map = (1 == atoi(s.c_str())); //他のマップチップに当たるかを取得
		getline(ss, s, ',');
		mapchip_data[num].flying = (1 == atoi(s.c_str())); //浮いているかを取得
		getline(ss, s, ',');
		mapchip_data[num].friction = (float)atof(s.c_str()); //摩擦を取得
		getline(ss, s, ',');
		mapchip_data[num].link_x1 = atoi(s.c_str()); //つなげるマップチップを取得
		getline(ss, s, ',');
		mapchip_data[num].link_x2 = atoi(s.c_str()); //つなげるマップチップを取得
	}
	ifs.close();
}

//ステージ情報の設定
void MapChipManager::SetStageData() {
	
	ifstream ifs("data/map/stage_data.csv");

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}
	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stage_data.emplace_back(str);
	}

	ifs.close();

	SetMapData(stage_data[stage_num]);
}

//マップ情報の設定
void MapChipManager::SetMapData(string file_name) {

	MapDataStruct new_map{};
	
	ifstream ifs(file_name);

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		new_map.mapfile_name = s; //マップ情報ファイル名を取得
		getline(ss, s, ',');
		new_map.mapfile_name2 = s; //マップ情報ファイル名を取得
		getline(ss, s, ',');
		new_map.scroll_name = s; //スクロール範囲ファイル名を取得
		getline(ss, s, ',');
		new_map.back_name = s; //BGM&背景ファイル名を取得
		getline(ss, s, ',');
		new_map.enemy_name = s; //敵配置ファイル名を取得
		getline(ss, s, ',');
		new_map.item_name = s; //アイテム配置ファイル名を取得
		getline(ss, s, ',');
		new_map.warp_name = s; //ワープ配置ファイル名を取得
		getline(ss, s, ',');
		new_map.warp_data_name = s; //ワープ情報ファイル名を取得
		getline(ss, s, ',');
		new_map.event_name = s; //イベント配置ファイル名を取得
		getline(ss, s, ',');
		new_map.event_data_name = s; //イベント情報ファイル名を取得
		map_data.emplace_back(new_map);
	}

	ifs.close();
}

//BGMと背景情報の設定
void MapChipManager::SetBackData(shared_ptr<Image> image) {

	ifstream ifs(map_data[next_map].back_name);

	//背景があれば初期化
	if (!back_data.empty()) {
		back_data.clear();
	}

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//BGM
	//ファイルから一行読み
	getline(ifs, str);
	bgm = atoi(str.c_str());

	//背景
	//ファイルから一行読み
	while (getline(ifs, str)) {
		BackStruct back{};
		stringstream ss{ str };
		getline(ss, s, ','); //カンマまで読み込む
		back.image = atoi(s.c_str()); //画像番号を設定
		getline(ss, s, ','); //カンマまで読み込む
		back_data.push_back(back);

		image->LoadBackImage(back.image); //背景をロード
	}

	ifs.close();
}

//ワープ情報の設定
void MapChipManager::SetWarpData() {

	//ワープ情報があれば初期化
	if (!warp_data.empty()) {
		warp_data.clear();
	}

	ifstream ifs(map_data[next_map].warp_data_name);

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	int num;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		WarpDataStruct warp{};
		stringstream ss{ str };
		getline(ss, s, ','); //カンマまで読み込む
		num = atoi(s.c_str()); //番号を設定
		getline(ss, s, ','); //カンマまで読み込む
		warp.image = atoi(s.c_str()); //表示する画像を設定
		getline(ss, s, ','); //カンマまで読み込む
		warp.size_x = atoi(s.c_str()); //横の大きさを設定
		getline(ss, s, ','); //カンマまで読み込む
		warp.size_y = atoi(s.c_str()); //縦の大きさを設定
		getline(ss, s, ','); //カンマまで読み込む
		warp.next_num = atoi(s.c_str()); //次のマップ番号を設定
		getline(ss, s, ','); //カンマまで読み込む
		warp.next_x = (float)atof(s.c_str()); //x座標を設定
		getline(ss, s, ','); //カンマまで読み込む
		warp.next_y = (float)atof(s.c_str()); //y座標を設定
		warp_data.emplace_back(warp);
	}

	ifs.close();
}

//マップの生成
void MapChipManager::MakeMap(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EventManager> event, shared_ptr<Image> image, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	int row = 0; //行
	int col = 0; //列

	//自機の位置を設定
	player->SetX(warp_data[warp_num].next_x);
	player->SetY(warp_data[warp_num].next_y);

	camera->SetScrollX(warp_data[warp_num].next_x); //横方向のスクロールを初期化
	camera->SetScrollY(warp_data[warp_num].next_y); //縦方向のスクロールを初期化

	if(warp_flag) SetWarpData(); //ワープ情報を再設定

	//マップチップがあれば初期化
	if (!mapchip.empty()) {
		mapchip.clear();
	}

	MakeMapChip(); //マップチップの配置
	MakeMapFront(); //見えない所のマップチップを配置
	MakeMapScroll(camera); //スクロール範囲を設定
	MakeMapEvent(); //イベントを配置
	SetBackData(image); //背景情報を設定
	MakeWarpDoor(); //ワープ扉を配置
	enemy->SetStandby(map_data[next_map].enemy_name); //敵を配置
	item->SetStandby(map_data[next_map].item_name); //アイテムを配置
	event->SetStandby(map_data[next_map].event_data_name); //イベント情報を設定

	warp_flag = false;
	warp_num = 0;

	sound->LoadBgm(bgm); //曲をロード
	sound->PlayBgm(bgm); //曲を再生
}

//マップチップの配置
void MapChipManager::MakeMapChip() {

	struct MapChipStruct
	{
		//マップチップの構造体
		int type; //種類
		bool flag; //配置したか
	};

	vector<vector<MapChipStruct>> map_layout; //マップチップの配列

	ifstream ifs(map_data[next_map].mapfile_name);

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		vector<MapChipStruct> v;
		stringstream ss{ str };
		//カンマ区切りで行を読み込み
		while (getline(ss, s, ',')) {
			MapChipStruct m = {-1, false};
			m.type = atoi(s.c_str()); //読み込んだ数値を格納
			v.emplace_back(m);
		}
		map_layout.emplace_back(v);
	}

	ifs.close();

	//マップチップの配置
	for (unsigned int i = 0; i < map_layout.size(); i++) {
		for (unsigned int j = 0; j < map_layout[i].size(); j++) {
			int num = map_layout[i][j].type;
			int size_x = mapchip_data[num].size_x; //起点の大きさ
			unsigned int plus_j = 1;
			//配置していないなら
			if (!map_layout[i][j].flag && num != -1) {
				//つなげるマップチップがあるなら
				//横の連結
				if (mapchip_data[num].link_x1 != -1 || mapchip_data[num].link_x2 != -1) {
					//はみ出すまで繰り返す
					while (j + plus_j < map_layout[i].size()) {
						int num_j = map_layout[i][j + plus_j].type;
						//つなげるマップチップでなければ終了
						if (num_j != mapchip_data[num].link_x1 + map_layout[i][j].type && num_j != mapchip_data[num].link_x2 + map_layout[i][j].type) {
							break;
						}
						size_x += mapchip_data[num_j].size_x; //大きさを増加
						map_layout[i][j + plus_j].flag = true; //配置したことに
						plus_j++;
					}
				}
				shared_ptr<AbstractMapChip> new_mapchip = SetMapChip(num, 32.0f * j + (4.0f * size_x), 32.0f * i); //マップチップを配置
				new_mapchip->SetSizeX(size_x); //大きさを設定
				new_mapchip->SetLinkX(plus_j); //連結数を設定
				new_mapchip->SetLinkImgX(mapchip_data[num].link_x1, mapchip_data[num].link_x2); //連結する画像を設定
				map_layout[i][j].flag = true; //配置したことに
				
			}
		}
	}
}

//マップチップの配置(見えない部分)
void MapChipManager::MakeMapFront() {

	int row = 0; //行
	int col = 0; //列

	ifstream ifs(map_data[next_map].mapfile_name2);

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		//カンマ区切りで行を読み込み
		while (getline(ss, s, ',')) {

			//読み込んだ数値が-1でなければ
			int num = atoi(s.c_str());
			if (num != -1) {
				//マップチップを配置
				SetMapChip(num, 32.0f * col + (4.0f * mapchip_data[num].size_x), 32.0f * row, false);
			}
			col++; //列数を増やす
		}

		//列数をリセットして行数を増やす
		col = 0;
		row++;
	}

	ifs.close();
}

//スクロール範囲の設定
void MapChipManager::MakeMapScroll(shared_ptr<Camera> camera) {

	int row = 0; //行
	int col = 0; //列

	ifstream ifs(map_data[next_map].scroll_name);

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		//カンマ区切りで行を読み込み
		while (getline(ss, s, ',')) {

			//読み込んだ数値によってスクロール範囲を決定
			switch (atoi(s.c_str()))
			{
			case 0:
				camera->SetScrollXMin(col * 32);
				camera->SetScrollYMin(row * 32);
				break;
			case 1:
				camera->SetScrollXMax((col + 1) * 32);
				camera->SetScrollYMax((row + 1) * 32);
				break;
			default:
				break;
			}
			col++; //列数を増やす
		}

		//列数をリセットして行数を増やす
		col = 0;
		row++;
	}

	ifs.close();
}

//イベント開始位置の設定
void MapChipManager::MakeMapEvent() {

	int row = 0; //行
	int col = 0; //列
	EventDataStruct new_event{};

	ifstream ifs(map_data[next_map].event_name);

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		//カンマ区切りで行を読み込み
		while (getline(ss, s, ',')) {

			//読み込んだ数値が-1でなければ
			int num = atoi(s.c_str());
			if (num != -1) {
				//イベントを配置
				new_event.flag = true;
				new_event.num = num;
				new_event.x = 32.0f * col;
				new_event.y = 32.0f * row + 16.0f;
				standby_event.emplace_back(new_event);
			}
			col++; //列数を増やす
		}

		//列数をリセットして行数を増やす
		col = 0;
		row++;
	}

	ifs.close();
}

//ワープ扉の設定
void MapChipManager::MakeWarpDoor() {
	int row = 0; //行
	int col = 0; //列

	//ワープ扉があれば初期化
	if (!warp_door.empty()) {
		warp_door.clear();
	}

	ifstream ifs(map_data[next_map].warp_name);

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		//カンマ区切りで行を読み込み
		while (getline(ss, s, ',')) {

			//読み込んだ数値が-1でなければ
			int num = atoi(s.c_str());
			if (num != -1) {
				//ワープ扉を配置
				WarpStruct warp{};
				warp.num = num;
				warp.x = 32.0f * col + (4.0f * warp_data[warp.num].size_x);
				warp.y = 32.0f * row + 32.0f - (4.0f * warp_data[warp.num].size_y);
				warp_door.emplace_back(warp);
			}
			col++; //列数を増やす
		}

		//列数をリセットして行数を増やす
		col = 0;
		row++;
	}

	ifs.close();
}

//初期化
void MapChipManager::Reset(){
	
}

//マップチップの配置
shared_ptr<AbstractMapChip> MapChipManager::SetMapChip(int num, float ini_x, float ini_y, bool hit_map) {
	shared_ptr<AbstractMapChip> new_mapchip;

	switch (mapchip_data[num].type)
	{
	case 0:
		new_mapchip = make_shared<NormalBlock>(this, mapchip_data[num].image);
		break;
	case 1:
		new_mapchip = make_shared<BombBlock>(this, mapchip_data[num].image);
		break;
		case 2:
		new_mapchip = make_shared<FuseBlock>(this, mapchip_data[num].image);
		break;
	case 3:
		new_mapchip = make_shared<PushBlock>(this, mapchip_data[num].image);
		break;
	case 4:
		new_mapchip = make_shared<LockedDoor>(this, mapchip_data[num].image);
		break;
	case 5:
		new_mapchip = make_shared<FallBlock>(this, mapchip_data[num].image);
		break;
	case 6:
		new_mapchip = make_shared<MassDriver>(this, mapchip_data[num].image);
		new_mapchip->SetAngle(0.0f);
		break;
	case 7:
		new_mapchip = make_shared<MassDriver>(this, mapchip_data[num].image);
		new_mapchip->SetAngle(PI);
		break;
	case 8:
		new_mapchip = make_shared<MassDriver>(this, mapchip_data[num].image);
		new_mapchip->SetAngle(1.5f * PI);
		break;
	case 9:
		new_mapchip = make_shared<MassDriver>(this, mapchip_data[num].image);
		new_mapchip->SetAngle(0.5f * PI);
		break;
	case 10:
		new_mapchip = make_shared<SpinMassDriver>(this, mapchip_data[num].image);
		break;
	default:
		new_mapchip = make_shared<NormalBlock>(this, mapchip_data[num].image);
		break;
	}

	new_mapchip->SetX(ini_x); //座標を設定
	new_mapchip->SetY(ini_y);
	new_mapchip->SetBaseX(ini_x); //基の座標を設定
	new_mapchip->SetBaseY(ini_y);
	new_mapchip->SetSizeX(mapchip_data[num].size_x); //大きさを設定
	new_mapchip->SetSizeY(mapchip_data[num].size_y);
	new_mapchip->SetThrough(mapchip_data[num].through); //すり抜けるか設定
	new_mapchip->SetBreakable(mapchip_data[num].breakable); //壊せるか設定
	new_mapchip->SetHitMap(mapchip_data[num].hit_map); //他のマップチップに当たるか設定
	new_mapchip->SetFlying(mapchip_data[num].flying); //浮いているか設定
	new_mapchip->SetFriction(mapchip_data[num].friction); //摩擦を設定
	new_mapchip->SetHitMap(hit_map); //他マップチップとの当たり判定を設定

	mapchip.emplace_back(new_mapchip);

	return new_mapchip;
}

//キャラがマップチップに当たっているか
bool MapChipManager::HitCheck(float cx, float cy, float hit_size, int break_power, bool abs_check) {
	bool flag = false; //当たったか
	for (auto &map : mapchip) {
		if ((!map->GetHitFlag() && !abs_check) || !map->GetLiveFlag() || !map->GetDrawFlag()) continue; //当たり判定がなければ飛ばす
		float x = 4.0f * map->GetSizeX() + hit_size; //判定用
		float sub_x = cx - map->GetX(); //x座標の差

		//x座標が当たっていないなら飛ばす
		if (!(fabsf(sub_x) < x)) {
			continue;
		}

		float y = 4.0f * map->GetSizeY() + hit_size; //判定用
		float center_y = map->GetY() + 4.0f * map->GetSizeY(); //マップチップの中心
		float sub_y = cy - center_y; //y座標の差

		//y座標が当たっているなら
		if (fabsf(sub_y) < y) {
			//x座標とy座標を比較
			//y座標の方が遠いなら
			if (fabsf(sub_x) < fabsf(sub_y)) {
				//上に当たったなら
				if (sub_y < 0.0f) {
					map->SetHitTop(true); //上に当たったことに
				}
				//下に当たったなら
				else {
					map->SetHitBottom(true); //下に当たったことに
				}
			}
			//y座標の方が遠いなら
			else {
				//左に当たったなら
				if (sub_x < 0.0f) {
					map->SetHitLeft(true); //左に当たったことに
				}
				//右に当たったなら
				else {
					map->SetHitRight(true); //右に当たったことに
				}
			}
			
			//壊すか確認していたら
			if (map->GetBreakable() <= break_power && map->GetBreakable() != 0) {
				map->SetEndFlag(true); //消滅フラグをtrueに
			}
			flag = true; //当たったフラグをtrueに
		}
	}
	return flag;
}

//キャラがマップチップに当たっているか(左の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckLeft(float cx, float cy, float hit_size) {
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag() || map->GetThrough()) continue; //当たり判定がなければ飛ばす
		float x = 4.0f * map->GetSizeX(); //判定用
		float y = 4.0f * map->GetSizeY() + hit_size - 0.01f; //判定用
		float center_y = map->GetY() + 4.0f * map->GetSizeY(); //マップチップの中心
		//そのマップチップが存在し、当たっているなら
		if (fabsf((cx - hit_size) - map->GetX()) < x && fabsf(cy - center_y) < y) {
			return map; //mapを返す
		}
	}
	return NULL;
}

//キャラがマップチップに当たっているか(右の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckRight(float cx, float cy, float hit_size) {
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag() || map->GetThrough()) continue; //当たり判定がなければ飛ばす
		float x = 4.0f * map->GetSizeX(); //判定用
		float y = 4.0f * map->GetSizeY() + hit_size - 0.01f; //判定用
		float center_y = map->GetY() + 4.0f * map->GetSizeY(); //マップチップの中心
		//そのマップチップが存在し、当たっているなら
		if (fabsf((cx + hit_size) - map->GetX()) < x && fabsf(cy - center_y) < y) {
			return map; //mapを返す
		}
	}
	return NULL;
}

//キャラがマップチップに当たっているか(上の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckTop(float cx, float cy, float hit_size) {
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag() || map->GetThrough()) continue; //当たり判定がなければ飛ばす
		float x = 4.0f * map->GetSizeX() + hit_size - 0.01f; //判定用
		float y = 8.0f * map->GetSizeY(); //判定用
		//そのマップチップが存在し、当たっているなら
		if (fabsf(cx - map->GetX()) < x && fabsf((cy - hit_size) - map->GetY()) < y && map->GetY() + y < cy) {
			return map; //mapを返す
		}
	}
	return NULL;
}

//キャラがマップチップに当たっているか(下の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckBottom(float cx, float cy, float hit_size) {
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //当たり判定がなければ飛ばす
		float x = 4.0f * map->GetSizeX() + hit_size - 0.01f; //判定用
		float y = hit_size; //判定用
		//そのマップチップが存在し、当たっているなら
		if (fabsf(cx - map->GetX()) < x && fabsf(cy - map->GetY()) < y) {
			return map; //mapを返す
		}
	}
	return NULL;
}

//キャラがマップチップに乗っているか
void MapChipManager::CheckStep(float cx, float cy, float hit_size) {
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //当たり判定がなければ飛ばす
		float x = 4.0f * map->GetSizeX() + hit_size; //判定用
		float y = 8.0f * map->GetSizeY(); //判定用
		float sub_y = (cy + hit_size) - map->GetY();
		//そのマップチップが存在し、当たっているなら
		if (fabsf(cx - map->GetX()) < x && sub_y < y && 0.0f < sub_y) {
			map->SetStep(true); //乗っているフラグをtrueに
		}
		//そうでなければ
		else {
			map->SetStep(false); //乗っているフラグをfalseに
		}
	}
}

//マップチップに乗っているキャラに足す速度を取得
float MapChipManager::GetPlusSpeedX(float cx, float cy, float hit_size) {
	float sx = 0.0f; //返す速度
	//移動前の座標を使う（直前まで乗っていたかを確認）
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //当たり判定がなければ飛ばす
		float x = 4.0f * map->GetSizeX() + hit_size; //判定用
		float y = 8.0f * map->GetSizeY(); //判定用
		float sub_y = (cy + hit_size) - map->GetLastY();
		float map_sx = map->GetAmountX() + map->GetMoveX();
		//そのマップチップが存在し、当たっているなら
		if (fabsf(cx - map->GetLastX()) < x && sub_y < y && 0.0f < sub_y) {
			//現在の速度と反対ならば
			if ((sx < 0.0f && 0.0f < map_sx) || (0.0f < sx && map_sx < 0.0f)) {
				sx += map_sx; //マップチップの速度を相殺する
			}
			//現在の速度より大きいなら
			else if (fabsf(sx) < fabsf(map_sx)) {
				sx = map_sx; //速度を上書き
			}
		}
	}
	return sx;
}

//マップチップに乗っているキャラに足す速度を取得
float MapChipManager::GetPlusSpeedY(float cx, float cy, float hit_size) {
	float sy = 0.0f; //返す速度
	for (auto &map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //当たり判定がなければ飛ばす
		float x = 4.0f * map->GetSizeX() + hit_size; //判定用
		float y = 8.0f * map->GetSizeY(); //判定用
		float sub_y = (cy + hit_size) - map->GetLastY();
		float map_sy = map->GetAmountY() + map->GetMoveY();
		//そのマップチップが存在し、当たっているなら
		if (fabsf(cx - map->GetLastX()) < x && sub_y < y && 0.0f < sub_y) {
			//現在の速度と反対ならば
			if ((sy < 0.0f && 0.0f < map_sy) || (0.0f < sy && map_sy < 0.0f)) {
				sy += map_sy; //マップチップの速度を相殺する
			}
			//現在の速度より大きいなら
			else if (fabsf(sy) < fabsf(map_sy)) {
				sy = map_sy; //速度を上書き
			}
		}
	}
	return sy;
}

//キャラがイベント発生位置に当たっているか
void MapChipManager::EventHitCheck(shared_ptr<EventManager> event, float cx, float cy) {
	for (unsigned int i = 0; i < standby_event.size(); i++) {
		bool hit_x = (fabsf(cx - standby_event[i].x) < 32.0f) || event->GetPosition(i);
		bool hit_y = (fabsf(cy - standby_event[i].y) < 32.0f) || !event->GetPosition(i);
		if (hit_x && hit_y && standby_event[i].flag) {
			//sound->PlaySoundEffect(7); //効果音を鳴らす
			event->SetEventList(standby_event[i].num, standby_event[i].x, standby_event[i].y); //イベントを予約
			standby_event[i].flag = false; //フラグをfalseに
			break;
		}
	}
}

//キャラがワープ扉に当たっているか
void MapChipManager::WarpHitCheck(shared_ptr<EventManager> event, shared_ptr<Key> key, shared_ptr<Sound> sound, float cx, float cy) {
	if (warp_door.size() <= 0 || warp_flag) return; //ワープ扉がないかすでにワープ待機なら終了
	for (auto& warp : warp_door) {
		if (!key->KeyCheckOnce(Up)) continue; //上が押されていないなら飛ばす
		bool hit_x = (fabsf(cx - warp.x) < 4.0f * warp_data[warp.num].size_x);
		bool hit_y = (fabsf(cy - warp.y) < 4.0f * warp_data[warp.num].size_y);
		//ワープ扉に当たっているなら
		if (hit_x && hit_y) {
			warp_flag = true; //ワープフラグをtrueに
			warp_num = warp.num; //参照する扉を設定
			next_map = warp_data[warp_num].next_num; // 次のマップを設定
			event->SetEvent(0); //停止イベントを予約
			sound->PlaySoundEffect(15); //効果音を鳴らす
			break;
		}
	}
}

//ワープするか取得
bool MapChipManager::GetWarpFlag() {
	return warp_flag;
}

//マップチップが他のマップチップに当たっているか(左の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckLeftMap(std::shared_ptr<AbstractMapChip> check_map) {
	
	int size_x = check_map->GetSizeX();//確認用マップチップの大きさ
	int size_y = check_map->GetSizeY();//確認用マップチップの大きさ
	float check_x = check_map->GetX(); //確認用マップチップのx座標
	float check_y = check_map->GetY() + 4.0f + size_y; //確認用マップチップのy座標

	for (auto& map : mapchip) {
		if (check_map == map || !map->GetHitFlag() || !map->GetLiveFlag() || !map->GetHitMap()) continue; //同じマップチップか当たり判定がなければ飛ばす

		float y = 4.0f * map->GetSizeY() + 4.0f * size_y; //判定用
		float center_y = map->GetY() + 4.0f * map->GetSizeY(); //マップチップの中心
		//明らかに遠いなら飛ばす
		if (!(fabsf(check_y - center_y) < y)) {
			continue;
		}

		float x = 4.0f * map->GetSizeX(); //判定用
		//そのマップチップが存在し、当たっているなら
		if (fabsf((check_x - 4.0f * size_x) - map->GetX()) < x) {
			return map; //mapを返す
		}

	}
	return NULL;
}

//マップチップが他のマップチップに当たっているか(右の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckRightMap(std::shared_ptr<AbstractMapChip> check_map) {

	int size_x = check_map->GetSizeX();//確認用マップチップの大きさ
	int size_y = check_map->GetSizeY();//確認用マップチップの大きさ
	float check_x = check_map->GetX(); //確認用マップチップのx座標
	float check_y = check_map->GetY() + 4.0f + size_y; //確認用マップチップのy座標

	for (auto& map : mapchip) {
		if (check_map == map || !map->GetHitFlag() || !map->GetLiveFlag() || !map->GetHitMap()) continue; //同じマップチップか当たり判定がなければ飛ばす

		float y = 4.0f * map->GetSizeY() + 4.0f * size_y; //判定用
		float center_y = map->GetY() + 4.0f * map->GetSizeY(); //マップチップの中心
		//明らかに遠いなら飛ばす
		if (!(fabsf(check_y - center_y) < y)) {
			continue;
		}

		float x = 4.0f * map->GetSizeX(); //判定用
		//そのマップチップが存在し、当たっているなら
		if (fabsf((check_x + 4.0f * size_x) - map->GetX()) < x) {
			return map; //mapを返す
		}
	}
	return NULL;
}

//マップチップが他のマップチップに当たっているか(上の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckTopMap(std::shared_ptr<AbstractMapChip> check_map) {
	
	int size_x = check_map->GetSizeX();//確認用マップチップの大きさ
	float check_x = check_map->GetX(); //確認用マップチップのx座標
	float check_y = check_map->GetY(); //確認用マップチップのy座標

	for (auto& map : mapchip) {
		if (check_map == map || !map->GetHitFlag() || !map->GetLiveFlag() || !map->GetHitMap() || map->GetThrough()) continue; //同じマップチップか当たり判定がなければ飛ばす

		float x = 4.0f * map->GetSizeX() + 4.0f * size_x; //判定用
		//明らかに遠いなら飛ばす
		if (!(fabsf(check_x - map->GetX()) < x)) {
			continue;
		}

		float y = 8.0f * map->GetSizeY(); //判定用
		//そのマップチップが存在し、当たっているなら
		if (fabsf(check_y - map->GetY()) < y && map->GetY() < check_y) {
			return map; //mapを返す
		}
	}
	return NULL;
}

//マップチップが他のマップチップに当たっているか(下の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckBottomMap(std::shared_ptr<AbstractMapChip> check_map, bool plus_one) {

	int size_x = check_map->GetSizeX(); //確認用マップチップの大きさ
	int size_y = check_map->GetSizeY(); //確認用マップチップの大きさ
	float check_x = check_map->GetX(); //確認用マップチップのx座標
	float check_y = check_map->GetY(); //確認用マップチップのy座標
	if (plus_one) check_y += 1.0f;

	for (auto& map : mapchip) {
		if (check_map == map || !map->GetHitFlag() || !map->GetLiveFlag() || !map->GetHitMap()) continue; //同じマップチップか当たり判定がなければ飛ばす
		
		float x = 4.0f * map->GetSizeX() + 4.0f * size_x; //判定用
		//明らかに遠いなら飛ばす
		if (!(fabsf(check_x - map->GetX()) < x)) {
			continue;
		}

		float y = 8.0f * size_y; //判定用
		//そのマップチップが存在し、当たっているなら
		if (fabsf(check_y - map->GetY()) < y) {
			return map; //mapを返す
		}
	}
	return NULL;
}

//位置の調節
void MapChipManager::AdjustPosition() {
	//取得用クラス
	shared_ptr<AbstractMapChip> hit_map;

	for (auto& map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag() || !map->GetDrawFlag()) continue; //当たり判定がなければ飛ばす
		int size_x = map->GetSizeX();//マップチップの大きさ
		int size_y = map->GetSizeY();//マップチップの大きさ
		float x = map->GetX(); //マップチップのx座標
		float y = map->GetY(); //マップチップのy座標
		float sx = map->GetXSpeed(); //マップチップの速度
		float sy = map->GetYSpeed(); //マップチップの速度
		bool hit_check = map->GetHitMap(); //マップチップに当たるか

		map->SetLastX(x); //移動前の座標を格納
		map->SetLastY(y); //移動前の座標を格納

		map->SetX(x + sx);

		//左右の判定から
		if (sx < -0.1f && hit_check) {
			hit_map = HitCheckLeftMap(map);
			while (hit_map != NULL)
			{
				map->SetX(hit_map->GetX() + 4.0f * ((float)size_x + (float)hit_map->GetSizeX()));
				map->SetXSpeed(0.0f);
				hit_map = HitCheckLeftMap(map);
			}
		}

		if (0.1f < sx && hit_check) {
			hit_map = HitCheckRightMap(map);
			while (hit_map != NULL)
			{
				map->SetX(hit_map->GetX() - 4.0f * ((float)size_x + (float)hit_map->GetSizeX()));
				map->SetXSpeed(0.0f);
				hit_map = HitCheckRightMap(map);
			}
		}

		//浮いていなければ
		if (!map->GetFlying()) {
			//直下に何もないなら
			if (HitCheckBottomMap(map, true) == NULL) {
				//速度がほぼないなら
				if (fabsf(sy) < 0.4f) {
					sy = 4.0f; //速度を設定
				}
				//速度があるなら
				else {
					sy += fabsf(sy * 0.3f); //速度を1.3(0.7)倍する
					if (JUMP_SPEED < sy) sy = JUMP_SPEED;
				}
			}
		}

		//上下の判定
		map->SetY(y + sy);

		if (sy < -0.1f && hit_check) {
			hit_map = HitCheckTopMap(map);

			while (hit_map != NULL) {
				map->SetY(hit_map->GetY() + 8.0f * hit_map->GetSizeY());
				map->SetYSpeed(0.0f);
				hit_map = HitCheckTopMap(map);
			}
		}
		if (0.1f < sy && hit_check) {
			hit_map = HitCheckBottomMap(map);
			while (hit_map != NULL) {
				map->SetY(hit_map->GetY() - 8.0f * size_y);
				map->SetYSpeed(0.0f);
				hit_map = HitCheckBottomMap(map);
			}
		}

	}
}

//画面内に収まっているか確認
void MapChipManager::WindowCheck(shared_ptr<AbstractMapChip> map, shared_ptr<Camera> camera) {
	float left = (float)camera->GetScrollX(); //画面左端
	float right = (float)camera->GetScrollX() + (float)WINDOW_X; //画面右端
	float top = (float)camera->GetScrollY(); //画面上
	float bottom = (float)camera->GetScrollY() + (float)WINDOW_Y; //画面底

	bool draw_flag; //描画するフラグ
	float x = map->GetX();
	float y = map->GetY();
	int size_x = map->GetSizeX();
	int size_y = map->GetSizeY();

	//画面内なら描画する
	draw_flag = (left - 32.0f - (4.0f * size_x) < x && x < right + 32.0f +(4.0f * size_x) && top - 32.0f - (8.0f * size_y) < y && y < bottom + 32.0f);
	map->SetDrawFlag(draw_flag);
	
}

//背景の更新
void MapChipManager::BackUpdate(shared_ptr<Image> image) {
	for (unsigned int i = 0; i < back_data.size(); i++) {
		//スクロール量を取得
		int dif_x = 0;
		int dif_y = 0;

		//背景画像の大きさを取得
		int size_x;
		int size_y;
		int image_num = image->GetBackImage(back_data[i].image);
		GetGraphSize(image_num, &size_x, &size_y);

		//スクロール量の分だけ背景を移動
		//back_data[i].x -= ((float)scroll_speed_x * back_data[i].sx);
		//back_data[i].y -= ((float)scroll_speed_y * back_data[i].sy);
		
		//背景がループする場合
		if (back_data[i].loop) {
			//背景(の右端)が画面外(左)に出た場合
			if (back_data[i].x < -size_x) {
				back_data[i].x += size_x; //画像の大きさ分右へ移動
			}

			//背景(の右端)が画面外(右)に出た場合
			if (back_data[i].x > 0) {
				back_data[i].x -= size_x; //画像の大きさ分左へ移動
			}
		}
		//しない場合
		else {
			//背景(の左端)が画面端(左)より右に出た場合
			if (back_data[i].x > 0.0f) {
				back_data[i].x = 0.0f; //背景の左端を0に移動
			}
			//背景(の右端)が画面端(右)より左に出た場合
			if (back_data[i].x + (float)size_x < WINDOW_X) {
				back_data[i].x = (float)WINDOW_X - (float)size_x; //背景の左端をウィンドウ-画像に移動
			}
		}
	}
}

//背景の描画
void MapChipManager::BackDraw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	for (auto &back : back_data) {
		//背景画像の大きさを取得
		int size_x;
		int size_y;
		int num = image->GetBackImage(back.image); //背景を取得
		GetGraphSize(num, &size_x, &size_y);
		float x = back.x;// +(float)size_x;
		float y = back.y;// +(float)size_y;

		Display::BackDraw(x, y, num); //背景を描画
		//ループする場合もう1枚
		if (back.loop) {
			Display::BackDraw(x + size_x, y, num); //背景を描画
		}
	}
}

//更新
void MapChipManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Image> image, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera){
	
	BackUpdate(image);

	for (auto &map : mapchip) {
		if (!map->GetLiveFlag()) continue;

		map->Update(player, enemy, bullet, effect, key, sound);
		map->Timer();
		map->SetHitLeft(false); //左の判定を初期化
		map->SetHitRight(false); //右の判定を初期化
		map->SetHitTop(false); //上の判定を初期化
		map->SetHitBottom(false); //下の判定を初期化

		//消滅フラグがtrueなら動作しなくなる
		if (map->GetEndFlag()) {

			map->SetLiveFlag(false);
		}

		WindowCheck(map, camera); //描画するか確認
	}
}

//描画
void MapChipManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	BackDraw(image, camera); //背景の描画

	for (auto &map : mapchip) {
		if (map->GetLiveFlag() && map->GetDrawFlag()) {
			map->Draw(image, camera);
			//DrawFormatString((int)map->GetX(), (int)map->GetY(), GetColor(255, 0, 0), "%f %d", map->GetX(), map->GetTime());
		}
	}

	for (auto& warp : warp_door) {
		int hundle = image->GetMapchipImage(warp_data[warp.num].image);
		camera->Draw(warp.x, warp.y, true, 0.0f, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
	}

	//DrawFormatString(64, 64, GetColor(255, 0, 0), "%d", mapchip.size());

	/*for (auto eve : standby_event) {
		int hundle = image->GetMapchipImage(0);
		camera->Draw(eve.x, eve.y, LEFT, 0.0f, hundle, DX_BLENDMODE_NOBLEND);
	}*/

	/*for (unsigned int i = 0; i < back_data.size(); i++) {
		DrawFormatString(64, 128 + (24 * i), GetColor(255, 0, 0), "%f %f %d", back_data[i].x, back_data[i].y, back_data[i].image);
	}*/
}