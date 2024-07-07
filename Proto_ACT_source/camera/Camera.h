#pragma once
#include "DxLib.h"
#include "../Define.h"
#include "..\tool\Display.h"
#include "..\tool\Calculation.h"
#include "..\system\Image.h"
#include <memory>
#include <thread>
#include <vector>

class ModeManager;
class EnvSetting;
class Key;
class Sound;
class Image;
class Fps;

class Camera {
private:

	int scroll_x; //横方向のスクロール
	int scroll_y; //縦方向のスクロール
	int scroll_x_min; //横方向のスクロール下限
	int scroll_x_max; //横方向のスクロール上限
	int scroll_y_min; //縦方向のスクロール下限
	int scroll_y_max; //縦方向のスクロール上限
	int scroll_dif_x; //横にどれだけスクロールしたか
	int scroll_dif_y; //縦にどれだけスクロールしたか
	int back_x_max; //変更前のスクロール上限
	int back_y_max; //変更前のスクロール上限

public:
	Camera(); //コンストラクタ
	~Camera(); //デストラクタ
	void Draw(float x, float y, bool reverse, float angle, int img, float ex_rate = 1.0f, int BlendMode = DX_BLENDMODE_NOBLEND, int Pal = 0); //スクロールを反映させた描画(x,y座標、左右の向き、角度、画像、ブレンドモード、パラメータ)
	void BackDraw(float x, float y, int img, int BlendMode = DX_BLENDMODE_NOBLEND, int Pal = 0); //背景の描画(x,y座標、画像、ブレンドモード、パラメータ)
	void FixedDraw(float x, float y, bool lr, float angle, int img, float ex_rate = 1.0f, int BlendMode = DX_BLENDMODE_NOBLEND, int Pal = 0); //スクロールを反映させない描画(x,y座標、左右の向き、角度、画像、倍率、ブレンドモード、パラメータ)
	void HitDraw(float x, float y, float hit_size); //当たり判定の描画
	int GetScrollX(); //横方向にどれだけスクロールしているか返す
	int GetScrollY(); //縦方向にどれだけスクロールしているか返す
	void SetScrollX(float x); //横方向にどれだけスクロールさせるか設定する(基準となるx座標)
	void SetScrollY(float y); //縦方向にどれだけスクロールさせるか設定する(基準となるy座標)
	int GetScrollXMin(); //横方向のスクロール下限を返す
	int GetScrollYMin(); //縦方向のスクロール下限を返す
	int GetScrollXMax(); //横方向のスクロール上限を返す
	int GetScrollYMax(); //縦方向のスクロール上限を返す
	void SetScrollXMin(int x); //横方向のスクロール下限を設定する(マップの左隅)
	void SetScrollYMin(int y); //縦方向のスクロール下限を設定する(マップの上)
	void SetScrollXMax(int x); //横方向のスクロール上限を設定する(マップの右隅)
	void SetScrollYMax(int y); //縦方向のスクロール上限を設定する(マップの下)
	void ReSetScrollXMax(); //横方向のスクロール上限を戻す
	void ReSetScrollYMax(); //縦方向のスクロール上限を戻す
	int GetScrollDifX(); //横方向にどれだけスクロールしたか返す
	int GetScrollDifY(); //縦方向にどれだけスクロールしたか返す
};