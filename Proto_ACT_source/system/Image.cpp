#pragma once
#include "Image.h"
#include "DxLib.h"

using namespace std;

//コンストラクタ
Image::Image() {
	LoadMapchipConvertData(); //マップチップ番号変換情報を読み込む
	LoadMapchipData(); //マップチップ情報を読み込む
	LoadBackData(); //背景情報を読み込む
	LoadCharaData(); //キャラの画像情報を読み込む
	LoadEffectData(); //エフェクトの画像情報を読み込む
	LoadBulletData(); //弾の画像情報を読み込む
	LoadItemData(); //アイテムの画像情報を読み込む
}

//デストラクタ
Image::~Image() {
	image_hundle.clear();
	mapchip_convert.clear();
	enemy_graphic_data.clear();
	effect_graphic_data.clear();
	bullet_graphic_data.clear();
	item_graphic_data.clear();
	mapchip_graphic_data.clear();
	back_data.clear();
	DeleteMapchipImage();
	DeleteBackImage();
	DeleteCharaImage();
	DeleteEffectImage();
	DeleteBulletImage();
	DeleteImage();
}

//初期化
void Image::Reset() {
	image_hundle.clear();
	DeleteBackImage();
	DeleteCharaImage();
	DeleteEffectImage();
	DeleteBulletImage();
	DeleteImage();
	LoadBackData(); //背景情報を読み込む
	LoadCharaData(); //キャラの画像情報を読み込む
	LoadEffectData(); //エフェクトの画像情報を読み込む
	LoadBulletData(); //弾の画像情報を読み込む
	LoadItemData(); //アイテムの画像情報を読み込む
	LoadItemData(); //アイテムの画像情報を読み込む
}

//マップチップ情報の読み込み
void Image::LoadMapchipData() {
	int num;

	ifstream ifs("data/graphic/mapchip/mapchip_graphic.csv");

	//なければ終了
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ',');
		mapchip_graphic_data[num].name = "data/graphic/mapchip/" + s; //ファイル名を格納
		getline(ss, s, ',');
		mapchip_graphic_data[num].num_x = atoi(s.c_str()); //画像の枚数（横）を設定
		getline(ss, s, ',');
		mapchip_graphic_data[num].num_y = atoi(s.c_str()); //画像の枚数（縦）を設定
		getline(ss, s, ',');
		mapchip_graphic_data[num].size_x = atoi(s.c_str()); //画像の大きさ（横）を設定
		getline(ss, s, ',');
		mapchip_graphic_data[num].size_y = atoi(s.c_str()); //画像の大きさ（縦）を設定
	}
	ifs.close();

}

//マップチップ番号変換情報の読み込み
void Image::LoadMapchipConvertData() {

	int num;

	ifstream ifs("data/graphic/mapchip/mapchip_convert.csv");

	//なければ終了
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ',');
		mapchip_convert[num].key_num = atoi(s.c_str()); //大元の画像番号を設定
		getline(ss, s, ',');
		mapchip_convert[num].image_num = atoi(s.c_str()); //使用する画像番号を設定
	}
	ifs.close();
}

//背景情報の読み込み
void Image::LoadBackData() {

	int num;

	ifstream ifs("data/graphic/back/back_data.csv");

	//なければ終了
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ',');
		back_data[num].name = "data/graphic/back/" + s; //ファイル名を格納
	}
	ifs.close();
}

//キャラ画像情報の読み込み
void Image::LoadCharaData() {

	int num;

	ifstream ifs("data/graphic/character/character_graphic.csv");

	//なければ終了
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ',');
		enemy_graphic_data[num].name = "data/graphic/character/" + s; //ファイル名を格納
		getline(ss, s, ',');
		enemy_graphic_data[num].num_x = atoi(s.c_str()); //画像の枚数（横）を設定
		getline(ss, s, ',');
		enemy_graphic_data[num].num_y = atoi(s.c_str()); //画像の枚数（縦）を設定
		getline(ss, s, ',');
		enemy_graphic_data[num].size_x = atoi(s.c_str()); //画像の大きさ（横）を設定
		getline(ss, s, ',');
		enemy_graphic_data[num].size_y = atoi(s.c_str()); //画像の大きさ（縦）を設定
	}
	ifs.close();
}

//エフェクト画像情報の読み込み
void Image::LoadEffectData() {

	int num;

	ifstream ifs("data/graphic/effect/effect_graphic.csv");

	//なければ終了
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ',');
		effect_graphic_data[num].name = "data/graphic/effect/" + s; //ファイル名を格納
		getline(ss, s, ',');
		effect_graphic_data[num].num_x = atoi(s.c_str()); //画像の枚数（横）を設定
		getline(ss, s, ',');
		effect_graphic_data[num].num_y = atoi(s.c_str()); //画像の枚数（縦）を設定
		getline(ss, s, ',');
		effect_graphic_data[num].size_x = atoi(s.c_str()); //画像の大きさ（横）を設定
		getline(ss, s, ',');
		effect_graphic_data[num].size_y = atoi(s.c_str()); //画像の大きさ（縦）を設定
	}
	ifs.close();
}

//弾画像情報の読み込み
void Image::LoadBulletData() {
	int num;

	ifstream ifs("data/graphic/bullet/bullet_graphic.csv");

	//なければ終了
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ',');
		bullet_graphic_data[num].name = "data/graphic/bullet/" + s; //ファイル名を格納
		getline(ss, s, ',');
		bullet_graphic_data[num].num_x = atoi(s.c_str()); //画像の枚数（横）を設定
		getline(ss, s, ',');
		bullet_graphic_data[num].num_y = atoi(s.c_str()); //画像の枚数（縦）を設定
		getline(ss, s, ',');
		bullet_graphic_data[num].size_x = atoi(s.c_str()); //画像の大きさ（横）を設定
		getline(ss, s, ',');
		bullet_graphic_data[num].size_y = atoi(s.c_str()); //画像の大きさ（縦）を設定
	}
	ifs.close();
}

//アイテム画像情報の読み込み
void Image::LoadItemData() {
	int num;

	ifstream ifs("data/graphic/item/item_graphic.csv");

	//なければ終了
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ',');
		item_graphic_data[num].name = "data/graphic/item/" + s; //ファイル名を格納
		getline(ss, s, ',');
		item_graphic_data[num].num_x = atoi(s.c_str()); //画像の枚数（横）を設定
		getline(ss, s, ',');
		item_graphic_data[num].num_y = atoi(s.c_str()); //画像の枚数（縦）を設定
		getline(ss, s, ',');
		item_graphic_data[num].size_x = atoi(s.c_str()); //画像の大きさ（横）を設定
		getline(ss, s, ',');
		item_graphic_data[num].size_y = atoi(s.c_str()); //画像の大きさ（縦）を設定
	}
	ifs.close();
}

//マップチップの画像をロード
void Image::LoadMapImage() {
	LoadDivGraph("data/graphic/mapchip/mapchip.png", 44, 22, 2, 32, 32, map_image); //マップチップの画像をロード

	warp_image = LoadGraph("data/graphic/mapchip/warp.png"); //ワープ地点の画像をロード
}

//マップチップの画像を返す(画像の番号)
int Image::GetMapImage(int num) {
	return map_image[num];
}

//ワープ地点の画像を返す 
int Image::GetWarpImage() {
	return warp_image;
}

//マップチップの画像を削除
void Image::DeleteMapImage() {
	int size = sizeof(map_image) / sizeof(int);
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(map_image[i]);
	}
	DeleteGraph(warp_image);
}

//マップチップの画像をロード
void Image::LoadMapchipImage() {
	// キャラ画像のメモリを確保
	for (auto& var : mapchip_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //画像の総数
		int *eimage = new int[image_num]; //一旦画像を入れる変数

		LoadDivGraph(var.second.name.c_str(), image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, eimage); //画像をロード

		for (int i = 0; i < image_num; i++)
		{
			mapchip_image[var.first].push_back(eimage[i]); //画像を入れる
		}
	}
}

//マップチップの画像を返す
int Image::GetMapchipImage(int image_num) {
	int key_num = mapchip_convert[image_num].key_num;
	int image = mapchip_convert[image_num].image_num;

	//画像を探す
	auto einum = mapchip_image.find(key_num); //画像を検索
	//あった場合
	if (einum != mapchip_image.end()) {
		if ((unsigned)image < mapchip_image[key_num].size()) {
			return mapchip_image[key_num][image]; //画像を返す
		}
	}
	return -1;
}

//マップチップの画像を返す
int Image::GetMapchipImage(int map_num, int image_num) {
	//画像を探す
	auto einum = mapchip_image.find(map_num); //画像を検索
	//あった場合
	if (einum != mapchip_image.end()) {
		if ((unsigned)image_num < mapchip_image[map_num].size()) {
			return mapchip_image[map_num][image_num]; //画像を返す
		}
	}
	return -1;
}

//マップチップの画像を削除
void Image::DeleteMapchipImage() {
	// マップチップ画像のメモリを解放
	for (auto& var : mapchip_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //メモリを解放
	}
	mapchip_image.clear(); //メモリを解放
}

//背景の画像をロード
void Image::LoadBackImage(int num) {
	//背景情報を探す
	auto data_num = back_data.find(num);
	//なかった場合
	if (data_num == back_data.end()) {
		return; //終了
	}

	//背景を探す
	auto back_num = background.find(num); //背景を検索
	//なかった場合
	if (back_num == background.end()) {
		background[num] = LoadGraph(back_data[num].name.c_str()); //背景をロード
	}
}

//背景の画像を返す(画像の番号)
int Image::GetBackImage(int num) {
	//背景を探す
	auto back_num = background.find(num); //背景を検索
	//あった場合
	if (back_num != background.end()) {
		return background[num]; //背景を返す
	}
	return -1;
}

//背景の画像を削除
void Image::DeleteBackImage() {
	for (auto& var : background)
	{
		DeleteGraph(var.second);
	}
	background.clear(); //メモリを解放
}

//キャラの画像をロード
void Image::LoadCharaImage() {
	// キャラ画像のメモリを確保
	for (auto& var : enemy_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //画像の総数
		int *eimage = new int[image_num]; //一旦画像を入れる変数

		LoadDivGraph(var.second.name.c_str(), image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, eimage); //画像をロード

		for (int i = 0; i < image_num; i++)
		{
			enemy_image[var.first].push_back(eimage[i]); //画像を入れる
		}
	}
}

//キャラの画像を返す(キャラの番号、画像の番号)
int Image::GetCharaImage(int enemy_num, int image_num) {
	//画像を探す
	auto einum = enemy_image.find(enemy_num); //画像を検索
	//あった場合
	if (einum != enemy_image.end()) {
		if ((unsigned)image_num < enemy_image[enemy_num].size()) {
			return enemy_image[enemy_num][image_num]; //画像を返す
		}
	}
	return -1;
}

//キャラの画像を削除
void Image::DeleteCharaImage() {
	// キャラ画像のメモリを解放
	for (auto& var : enemy_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //メモリを解放
	}
	enemy_image.clear(); //メモリを解放
}

//エフェクトの画像をロード
void Image::LoadEffectImage() {
	// エフェクト画像のメモリを確保
	for (auto& var : effect_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //画像の総数
		int *eimage = new int[image_num]; //一旦画像を入れる変数

		LoadDivGraph(var.second.name.c_str(), image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, eimage); //画像をロード

		for (int i = 0; i < image_num; i++)
		{
			effect_image[var.first].push_back(eimage[i]); //画像を入れる
		}
	}
}

//エフェクトの画像を返す
int Image::GetEffectImage(int effect_num, int image_num) {
	//画像を探す
	auto einum = effect_image.find(effect_num); //画像を検索
	//あった場合
	if (einum != effect_image.end()) {
		if ((unsigned)image_num < effect_image[effect_num].size()) {
			return effect_image[effect_num][image_num]; //画像を返す
		}
	}
	return -1;
}

//エフェクトの画像数を返す
int Image::GetEffectSize(int effect_num) {
	//画像を探す
	auto einum = effect_image.find(effect_num); //画像を検索
	//あった場合
	if (einum != effect_image.end()) {
		return effect_image[effect_num].size(); //画像を返す
	}
	return 0;
}

//エフェクトの画像を削除
void Image::DeleteEffectImage() {
	// エフェクト画像のメモリを解放
	for (auto& var : effect_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //メモリを解放
	}
	effect_image.clear(); //メモリを解放
}

//弾の画像をロード
void Image::LoadBulletImage() {
	//弾画像のメモリを確保
	for (auto& var : bullet_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //画像の総数
		int *bimage = new int[image_num]; //一旦画像を入れる変数

		LoadDivGraph(var.second.name.c_str(), image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, bimage); //画像をロード

		for (int i = 0; i < image_num; i++)
		{
			bullet_image[var.first].push_back(bimage[i]); //画像を入れる
		}
	}
}

//弾の画像を返す
int Image::GetBulletImage(int bullet_num, int image_num) {
	//画像を探す
	auto einum = bullet_image.find(bullet_num); //画像を検索
	//あった場合
	if (einum != bullet_image.end()) {
		if ((unsigned)image_num < bullet_image[bullet_num].size()) {
			return bullet_image[bullet_num][image_num]; //画像を返す
		}
	}
	return -1;
}

//弾の画像を削除
void Image::DeleteBulletImage() {
	//弾画像のメモリを解放
	for (auto& var : bullet_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //メモリを解放
	}
	bullet_image.clear(); //メモリを解放
}

//アイテムの画像をロード
void Image::LoadItemImage() {
	//弾画像のメモリを確保
	for (auto& var : item_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //画像の総数
		int* iimage = new int[image_num]; //一旦画像を入れる変数

		LoadDivGraph(var.second.name.c_str(), image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, iimage); //画像をロード

		for (int i = 0; i < image_num; i++)
		{
			item_image[var.first].push_back(iimage[i]); //画像を入れる
		}
	}
}

//アイテムの画像を返す
int Image::GetItemImage(int item_num, int image_num) {
	//画像を探す
	auto inum = item_image.find(item_num); //画像を検索
	//あった場合
	if (inum != item_image.end()) {
		if ((unsigned)image_num < item_image[item_num].size()) {
			return item_image[item_num][image_num]; //画像を返す
		}
	}
	return -1;
}

//アイテムの画像を削除
void Image::DeleteItemImage() {
	//アイテム画像のメモリを解放
	for (auto& var : item_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //メモリを解放
	}
	item_image.clear(); //メモリを解放
}

//分割した画像を読み込む
int Image::LoadSingleImage(char file_name[64]) {
	int num = LoadGraph(file_name);
	image_hundle.push_back(num);
	return num;
}

//画像を削除
void Image::DeleteImage() {
	//画像のメモリを解放
	const int size = image_hundle.size();
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(image_hundle[i]);
	}
	image_hundle.clear();
}