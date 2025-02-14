#include <DxLib.h>
#include "Fps.h"

const static int LIST_LEN_MAX = 120;	//最大120フレームで待機処理を計算する(2以上にする)
const static int FPS = 60;		//FPS
const static int UPINTVL = 60;		//60フレームに一度更新する

Fps::Fps() :_counter(0), _fps(0){
	message_font = CreateFontToHandle("メイリオ", 24, 2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1); //フォントの設定
}


Fps::~Fps() {
	DeleteFontToHandle(message_font);
}

void Fps::Wait()
{
	_counter++;
	Sleep(getWaitTime());   //待つべき時間を取得して待つ
	Regist();
	if (_counter == UPINTVL) {  //更新タイミングに1回平均値を更新する
		UpdateAverage();
		_counter = 0;
	}
}

void Fps::Draw()
{
	if (_fps == 0 || !draw_flag) {
		return;
	}
	DrawFormatStringToHandle(WINDOW_X - 104, 2, GetColor(255, 255, 255), message_font, "%04.1ffps", _fps);
}

void Fps::Regist()
{
	_list.push_back(GetNowCount());   //現在の時刻を記憶
	if (_list.size() > LIST_LEN_MAX){  //器から漏れたらポップ
		_list.pop_front();
	}
}

unsigned Fps::getWaitTime()
{
	int len = (int)_list.size();
	if (len == 0){
		return 0;
	}
	int shouldTookTime = (int)(1000 / 60.0*(len));            //計算上かかるべき時間
	int actuallyTookTime = GetNowCount() - _list.front();   //実際にかかった時間
	int waitTime = shouldTookTime - actuallyTookTime;       //計算上かかるべき時間 - 実際にかかった時間　はすなわち待つべき時間
	waitTime = waitTime > 0 ? waitTime : 0;
	return (unsigned)(waitTime);
}

void Fps::UpdateAverage() {
	int len = (int)_list.size();
	if (len < LIST_LEN_MAX) {   //まだ平均を計算するレベルにまでたまっていなければ計算しない
		return;
	}
	int tookTime = _list.back() - _list.front();//LIST_LEN_MAXフレームにかかった時間
	float average = (float)tookTime / ((float)len - 1.0f);//平均を取る
	if (average == 0) {//0割り防止
		return;
	}
	_fps = (1000 / average);
}

//FPS表示を設定
void Fps::SetDrawFlag(bool flag) {
	draw_flag = flag;
}

//FPS表示を取得
bool Fps::GetDrawFlag() {
	return draw_flag;
}