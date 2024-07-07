#pragma once
#include "Display.h"
#include "DxLib.h"

Display::Display() {

}

//•`‰æ
void Display::Draw(float x, float y, bool reverse, float angle, int image, float ex_rate, int BlendMode, int Pal) {

	SetDrawBlendMode(BlendMode, Pal); //•`‰æƒ‚[ƒh‚ğ”½‰f

	DrawRotaGraph((int)x, (int)y, ex_rate, angle, image, true, reverse);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //•`‰æƒ‚[ƒh‚ğ–ß‚·
}

//”wŒi‚Ì•`‰æ
void Display::BackDraw(float x, float y, int image, int BlendMode, int Pal) {
	//”wŒi‰æ‘œ‚Ì‘å‚«‚³‚ğæ“¾
	int size_x;
	int size_y;
	GetGraphSize(image, &size_x, &size_y);

	// ÀÛ‚Ég‚¤‚Ì‚Í”¼•ª‚Ì‘å‚«‚³
	size_x = size_x / 2;
	size_y = size_y / 2;

	SetDrawBlendMode(BlendMode, Pal); //•`‰æƒ‚[ƒh‚ğ”½‰f

	DrawRotaGraph((int)x + size_x, (int)y + size_y, 1.0f, 0.0f,image, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //•`‰æƒ‚[ƒh‚ğ–ß‚·
}

//“–‚½‚è”»’è‚Ì•`‰æ
void Display::HitDraw(float x, float y, float hit_size) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192); //•`‰æƒ‚[ƒh‚ğ”½‰f

	DrawCircle((int)x, (int)y, (int)hit_size, GetColor(255, 96, 96));

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //•`‰æƒ‚[ƒh‚ğ–ß‚·
}