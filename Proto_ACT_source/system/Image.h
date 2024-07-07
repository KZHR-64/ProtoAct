#pragma once
#include "../Define.h"
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct CharaImageStruct{
	//キャラクター画像の構造体
	std::string name; //ファイル名
	int num_x; //画像の分割数(横)
	int num_y; //画像の分割数(縦)
	int size_x; //1枚の大きさ(横)
	int size_y; //1枚の大きさ(縦)
};

struct MapchipConvertStruct{
	//マップチップ番号変換の構造体
	int key_num; //大元の画像番号
	int image_num; //使用する画像番号
};

class Image {
private:
	int player_image[28]; //自機の画像
	int map_image[44]; //マップチップの画像
	int warp_image; //ワープ地点の画像
	std::map<int, int> background; //背景画像
	std::map<int, CharaImageStruct> back_data; //背景画像の情報
	std::map<int, std::vector<int>> enemy_image; //キャラの画像
	std::map<int, CharaImageStruct> enemy_graphic_data; //キャラ画像の情報
	std::map<int, std::vector<int>> effect_image; //エフェクトの画像
	std::map<int, CharaImageStruct> effect_graphic_data; //エフェクト画像の情報
	std::map<int, std::vector<int>> bullet_image; //弾の画像
	std::map<int, CharaImageStruct> bullet_graphic_data; //弾画像の情報
	std::map<int, std::vector<int>> mapchip_image; //マップチップの画像
	std::map<int, CharaImageStruct> mapchip_graphic_data; //マップチップ画像の情報
	std::map<int, MapchipConvertStruct> mapchip_convert; //マップチップ番号変換情報
	std::map<int, std::vector<int>> item_image; //アイテムの画像
	std::map<int, CharaImageStruct> item_graphic_data; //アイテム画像の情報
	std::vector<int> image_hundle; //画像(メモリ取得用)

	void LoadMapchipData(); //マップチップ情報の読み込み
	void LoadMapchipConvertData(); //マップチップ番号変換情報の読み込み
	void LoadBackData(); //背景情報の読み込み
	void LoadCharaData(); //キャラ画像情報の読み込み
	void LoadEffectData(); //エフェクト画像情報の読み込み
	void LoadBulletData(); //弾画像情報の読み込み
	void LoadItemData(); //アイテム画像情報の読み込み

public:
	Image(); //コンストラクタ
	~Image(); //デストラクタ

	void Reset(); //初期化

	void LoadMapImage(); //マップチップの画像をロード
	int GetMapImage(int num); //マップチップの画像を返す(画像の番号)
	int GetWarpImage(); //ワープ地点の画像を返す
	void DeleteMapImage(); //マップチップの画像を削除

	void LoadMapchipImage(); //マップチップの画像をロード
	int GetMapchipImage(int image_num); //マップチップの画像を返す(画像の番号)
	int GetMapchipImage(int map_num, int image_num); //マップチップの画像を返す(マップチップの番号、画像の番号)
	void DeleteMapchipImage(); //マップチップの画像を削除

	void LoadBackImage(int num); //背景の画像をロード(画像の番号)
	int GetBackImage(int num); //背景の画像を返す(画像の番号)
	void DeleteBackImage(); //背景の画像を削除

	void LoadCharaImage(); //キャラの画像をロード
	int GetCharaImage(int enemy_num, int image_num); //キャラの画像を返す(キャラの番号、画像の番号)
	void DeleteCharaImage(); //キャラの画像を削除

	void LoadEffectImage(); //エフェクトの画像をロード
	int GetEffectImage(int effect_num, int image_num); //エフェクトの画像を返す(エフェクトの番号、画像の番号)
	int GetEffectSize(int effect_num); //エフェクトの画像数を返す(エフェクトの番号)
	void DeleteEffectImage(); //エフェクトの画像を削除

	void LoadBulletImage(); //弾の画像をロード
	int GetBulletImage(int bullet_num, int image_num); //弾の画像を返す(弾の番号、画像の番号)
	void DeleteBulletImage(); //弾の画像を削除

	void LoadItemImage(); //アイテムの画像をロード
	int GetItemImage(int item_num, int image_num); //アイテムの画像を返す(弾の番号、画像の番号)
	void DeleteItemImage(); //アイテムの画像を削除

	int LoadSingleImage(char file_name[64]); //分割した画像を読み込む(ファイル名)
	void DeleteImage(); //画像を削除
};