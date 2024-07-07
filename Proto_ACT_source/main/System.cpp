#pragma once
#include "DxLib.h"
#include "System.h"
#include <time.h>

System::System(){

}

System::~System() {

}

//èâä˙ê›íËÇÃì«Ç›çûÇ›
void System::Setting() {

	SetOutApplicationLogValidFlag(false);
	SetAlwaysRunFlag(TRUE);
	SetWindowSizeChangeEnableFlag(TRUE);
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_X, WINDOW_Y, 16);
	SetMainWindowText("Project_ACT");
	if (DxLib_Init() == -1) DebugBreak();
	SetDrawScreen(DX_SCREEN_BACK);

	time_t now = time(NULL);
	struct tm pnow;
	localtime_s(&pnow, &now);

	SRand(pnow.tm_hour + pnow.tm_min + pnow.tm_sec);
}

//èIóπ
void System::Finalize() {
	DxLib_End();
}

//çXêV
void System::Update(){
	ModeManager mode;
	mode.Setting();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		mode.Draw();
		mode.Update();
	}
}