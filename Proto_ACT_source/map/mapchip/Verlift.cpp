#pragma once
#include "DxLib.h"
#include "Verlift.h"

using namespace std;

//コンストラクタ
Verlift::Verlift(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	
}

//デストラクタ
Verlift::~Verlift() {

}

//更新
void Verlift::Update(){

}

//描画
void Verlift::Draw() {
	DrawBox((int)x - (4 * size_x), (int)y, (int)x + (4 * size_x), (int)y + (8 * size_y), GetColor(128, 128, 128), true);
}