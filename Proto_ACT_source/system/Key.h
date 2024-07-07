#pragma once
#include "../Define.h"
#include "Singleton.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct Key_Func{
	int key; //対応するキーの識別子
	int pad; //対応するボタンの識別子
};

typedef enum {
	//ボタン
	Up, //上
	Down, //下
	Left, //左
	Right, //右
	Jump, //ジャンプ(決定)
	Attack, //攻撃(戻る)
	L, //SwitchでいうL
	R, //SwitchでいうR
	Plus, //Switchでいう+
	//Minus, //Switchでいう-
} Button;

class Key {
private:
	char key_list[256]; //現在入力されているキー
	char old_key_list[256]; //一つ前に入力されたキー
	int pad; //パッドで押されたボタン
	int old_pad; //一つ前にパッドで押されたボタン
	Key_Func button[BUTTON]; //対応するボタン

	void LoadSetting(); //設定ファイルの読み込み
public:
	Key(); //コンストラクタ
	void Update(); //更新
	void SaveSetting(); //設定の保存
	void GetKey(Key_Func* set_key); //操作に対応するキーを取得
	void SetKey(Key_Func* set_key); //操作に対応するキーを変更
	bool KeyCheck(int check); //キーが押されているか(押し続けに対応)
	bool KeyCheckOnce(int check); //キーが一度押されたか(判定は押されてすぐのみ)
	bool KeyCheckLetGo(int check); //キーが一度放されたか(判定は放されたすぐのみ)
	int GetKeyOnce(); //押されたキーを一つ返す(判定は押されてすぐのみ)
	int GetPadOnce(); //押されたボタンを一つ返す(判定は押されてすぐのみ)
};