#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//壊せる足場

class Verlift : public AbstractMapChip{
protected:
public:
	Verlift(MapChipManager* man, int num); //コンストラクタ(番号)
	~Verlift(); //デストラクタ
	void Update(); //更新
	void Draw() override; //描画
};
