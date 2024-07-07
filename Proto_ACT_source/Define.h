#pragma once
#include "DxLib.h"

typedef enum {
	//次の画面
	Next_None,			//変えない
	Next_Opening,		//オープニング画面
	Next_Menu,			//メニュー画面
	Next_StageSelect,	//ステージセレクト画面
	Next_Game,			//ゲーム画面
	Next_Gameover,		//ゲームオーバー画面
	Next_Option,		//オプション画面
	Next_Config,		//キーコンフィグ画面
	Next_Back,			//前に戻る
} NextMode;

const static int WINDOW_X = 1280; //画面の大きさ(横)
const static int WINDOW_Y = 720; //画面の大きさ(縦)

const static int BUTTON = 9; //ボタンの総数
const static int RECORD = 12; //保存する、ボタンを押した履歴数
const static int STAGE_MAX = 3; //ステージの総数

const static int VOLUME_MAX = 100; //音量の最大値

const static bool LEFT = false; //左向きを表す
const static bool RIGHT = true; //右向きを表す

const static int HP_MAX = 6; //HPの最大値
const static int JUMP_TIME_MAX = 16; //ジャンプで上昇する時間
const static float JUMP_SPEED = 12.0f; ////ジャンプで上昇するスピードの最大
const static int DAMAGE_TIME_MAX = 10; //ダメージ動作の時間
const static int DAMAGE_INV_TIME = 60; //ダメージを受けたときの無敵時間
const static int CLEAR_MOVE_TIME_MAX = 300; //クリア時の動作時間
const static int WEAPON_MAX = 4; //武器の最大数

const static int MAPCHIP_MAX = 1024; //マップチップの最大数

const static int BACKGROUND_MAX = 2; //背景の最大数

const static float PI = 3.141592654f;	//円周率