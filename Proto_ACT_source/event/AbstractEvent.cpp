#pragma once
#include "DxLib.h"
#include "AbstractEvent.h"
#include <math.h>

using namespace std;

AbstractEvent::AbstractEvent(EventManager* man, bool stop_player, bool stop_enemy){
	manager = man;
	time = 0;
	end_flag = false;
	player_stop = stop_player; //©‹@‚Ì“®‚«‚ğ~‚ß‚é‚©
	enemy_stop = stop_enemy; //“G‚Ì“®‚«‚ğ~‚ß‚é‚©
}

AbstractEvent::~AbstractEvent(){

}

//ŠÔ‚ğ•Ô‚·
int AbstractEvent::GetTime() {
	return time;
}

//ŠÔ‚ğİ’è
void AbstractEvent::SetTime(int set_time) {
	time = set_time;
}

//I—¹‚µ‚½‚©æ“¾
bool AbstractEvent::GetEndFlag() {
	return end_flag;
}

//©‹@‚ğ~‚ß‚é‚©æ“¾
bool AbstractEvent::GetPlayerStop() {
	return player_stop;
}

//“G‚ğ~‚ß‚é‚©æ“¾
bool AbstractEvent::GetEnemyStop() {
	return enemy_stop;
}