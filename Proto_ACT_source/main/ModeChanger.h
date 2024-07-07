#pragma once
#include "Parameter.h"
#include "../Define.h"

class ModeChanger {
public:
	ModeChanger() = default;
	virtual ~ModeChanger() = default;
	virtual void ChangeMode(NextMode nmode, bool erase_now = false, bool change_window = false) = 0; //次のモードにする
	virtual void ChangeMode(NextMode nmode, Parameter &parameter, bool erase_now = false) = 0; //次のモードにする
	virtual void BackMode() = 0; //前のモードに戻る
};