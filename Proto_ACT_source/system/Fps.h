#pragma once
#include "../Define.h"
#include <list>

class Fps {
private:
	std::list<int> _list;
	float _fps;
	unsigned _counter;

	void UpdateAverage();
	void Regist();
	unsigned getWaitTime();

	bool draw_flag; //fps表示を行うか
	int message_font; //フォント情報

public:
	Fps();
	~Fps();
	void Wait();
	void Draw();

	bool GetDrawFlag(); //FPS表示を取得
	void SetDrawFlag(bool flag); //FPS表示を設定(フラグ)
};