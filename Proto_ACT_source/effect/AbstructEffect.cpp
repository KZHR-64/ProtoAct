#pragma once
#include "DxLib.h"
#include "AbstractEffect.h"
#include <math.h>

using namespace std;

AbstractEffect::AbstractEffect(EffectManager* man, int num, float ini_x, float ini_y) : CharacterBase() {
	manager = man;

	time = 0;
	end_flag = false;
	image_num = num;
	x = ini_x;
	y = ini_y;
	base_x = x;
	base_y = y;
	sx = 0.0f;
	sy = 0.0f;
	angle = 0.0f;
	ex_rate = 1.0f;
}

AbstractEffect::~AbstractEffect(){

}