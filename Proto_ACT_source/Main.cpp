#pragma once
#include "DxLib.h"
#include "Define.h"
#include "main\System.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	System system;
	system.Setting();
	system.Update();
	system.Finalize();
	return 0;
}
