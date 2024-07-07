#pragma once
#include "DxLib.h"
#include "EventManager.h"
#include "eventlist\WaitEvent.h"
#include "eventlist\ClearEvent.h"
#include "eventlist\MissEvent.h"
#include "eventlist\TalkEvent.h"
#include "eventlist\ScrollSettingEvent.h"
#include "eventlist\PlayerMoveEvent.h"
#include "eventlist\EnemySettingEvent.h"
#include "eventlist\EffectSettingEvent.h"
#include "eventlist\PlayMusicEvent.h"
#include "eventlist\WaitBattleEvent.h"
#include "eventlist\ScrollResetEvent.h"
#include <math.h>

using namespace std;

EventManager::EventManager(){
	message_font = CreateFontToHandle("Meiryo UI", 20, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1); //�t�H���g���
	
	x = 0.0f;
	y = 0.0f;

	enemy_stop = false;
	player_stop = false;
	clear_flag = false;
	restart_flag = false;
}

EventManager::~EventManager(){
	//�X�^�b�N��S�J��
	while (!event_queue.empty())
	{
		event_queue.pop();
	}
	event_data.clear();
	DeleteFontToHandle(message_font);
}

//�C�x���g��p��
void EventManager::SetStandby(string file_name) {

	int num;

	ifstream ifs(file_name);

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		// ���s�R�[�h���폜
		if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
		if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

		stringstream ss{ str };
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		event_data[num].position = (atoi(s.c_str()) == 1); //�ԍ����擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		event_data[num].file_name = s; //�g�p����t�@�C�������擾
	}
	ifs.close();
}

//�C�x���g��\��
void EventManager::SetEvent(int num) {
	shared_ptr<AbstractEvent> new_event;
	switch (num)
	{
	case 0:
		new_event = make_shared<WaitEvent>(this, 30, true, true);
		break;
	case 1:
		new_event = make_shared<ClearEvent>(this, 180, true, false);
		break;
	case 2:
		new_event = make_shared<MissEvent>(this, 180, true, false);
		break;
	default:
		new_event = make_shared<WaitEvent>(this, 30, true, true);
		break;
	}
	event_queue.push(new_event);

	//�����ꂽ�̂��ŏ��Ȃ�J�n
	if (1 == event_queue.size()) {
		EventStart();
	}
}

//�C�x���g�𕡐��\��(�t�@�C���ԍ�)
void EventManager::SetEventList(int num, float ini_x, float ini_y) {

	int event_size = (int)event_queue.size(); //���݂̃C�x���g��

	//���W��ݒ�
	x = ini_x;
	y = ini_y;

	ifstream ifs(event_data[num].file_name);

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s[4];
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		shared_ptr<AbstractEvent> new_event;

		// ���s�R�[�h���폜
		if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
		if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

		stringstream ss{ str };
		getline(ss, s[0], ','); //�J���}�܂œǂݍ���
		getline(ss, s[1], ','); //�J���}�܂œǂݍ���
		getline(ss, s[2], ','); //�J���}�܂œǂݍ���
		getline(ss, s[3], ','); //�J���}�܂œǂݍ���

		switch (atoi(s[0].c_str()))
		{
		case 0:
			new_event = make_shared<WaitEvent>(this, atoi(s[1].c_str()), atoi(s[2].c_str()) == 1, atoi(s[3].c_str()) == 1);
			break;
		case 1:
			new_event = make_shared<ClearEvent>(this, 180, true, false);
			break;
		case 2:
			new_event = make_shared<MissEvent>(this, 180, true, false);
			break;
		case 3:
			new_event = make_shared<TalkEvent>(this, s[1], s[2], true, true);
			break;
		case 4:
			new_event = make_shared<PlayerMoveEvent>(this, (float)atof(s[1].c_str()), (float)atof(s[2].c_str()), (float)atof(s[3].c_str()), true, true);
			break;
		case 5:
			new_event = make_shared<EnemySettingEvent>(this, atoi(s[1].c_str()), (float)atof(s[2].c_str()), (float)atof(s[3].c_str()), true, true);
			break;
		case 6:
			new_event = make_shared<EffectSettingEvent>(this, atoi(s[1].c_str()), (float)atof(s[2].c_str()), (float)atof(s[3].c_str()), true, true);
			break;
		case 7:
			new_event = make_shared<PlayMusicEvent>(this, atoi(s[1].c_str()), true, true);
			break;
		case 8:
			new_event = make_shared<WaitBattleEvent>(this, false, false);
			break;
		case 9:
			new_event = make_shared<ScrollSettingEvent>(this, atoi(s[1].c_str()), atoi(s[2].c_str()), true, true);
			break;
		case 10:
			new_event = make_shared<ScrollResetEvent>(this, true, true);
			break;
		default:
			new_event = make_shared<WaitEvent>(this, 30, true, true);
			break;
		}
		event_queue.push(new_event);
	}
	ifs.close();

	enemy_stop = true;
	player_stop = true;

	//�O�ɃC�x���g���Ȃ���ΊJ�n
	if (event_size == 0) {
		EventStart();
	}
}

//������
void EventManager::Reset(){
	enemy_stop = false;
	player_stop = false;
	clear_flag = false;
	restart_flag = false;
	//�X�^�b�N��S�J��
	while (!event_queue.empty())
	{
		event_queue.pop();
	}
	event_data.clear();
}

//�C�x���g���J�n
void EventManager::EventStart() {
	//��~�t���O��ݒ�
	if (event_queue.empty()) {
		player_stop = false;
		enemy_stop = false;
		return;
	}
	player_stop = event_queue.front()->GetPlayerStop();
	enemy_stop = event_queue.front()->GetEnemyStop();
}

//�I�������C�x���g������
void EventManager::EventEnd() {
	//��~�t���O������
	player_stop = false;
	enemy_stop = false;

	event_queue.pop();

	//��������ΊJ�n
	if (1 <= event_queue.size()) {
		EventStart();
	}
}

//�C�x���g��S�ď���
void EventManager::AllEventEnd() {
	//��~�t���O������
	enemy_stop = false;
	player_stop = false;
	//�X�^�b�N��S�J��
	while (!event_queue.empty())
	{
		event_queue.pop();
	}
}

//���@���~�߂邩�擾
bool EventManager::GetPlayerStop() {
	return player_stop;
}

//���@���~�߂邩�ݒ�
void EventManager::SetPlayerStop(bool flag) {
	player_stop = flag;
}

//�G���~�߂邩�擾
bool EventManager::GetEnemyStop() {
	return enemy_stop;
}

//�G���~�߂邩�ݒ�
void EventManager::SetEnemyStop(bool flag) {
	enemy_stop = flag;
}

//�N���A���������擾
bool EventManager::GetClearFlag() {
	return clear_flag;
}

//�N���A��������ݒ�
void EventManager::SetClearFlag(bool flag) {
	clear_flag = flag;
}

//���Ȃ��������擾
bool EventManager::GetRestartFlag() {
	return restart_flag;
}

//���Ȃ�������ݒ�
void EventManager::SetRestartFlag(bool flag) {
	restart_flag = flag;
}

//�t�H���g�����擾
int EventManager::GetFont() {
	return message_font;
}

//�Q�Ƃ�����W���擾
bool EventManager::GetPosition(int num) {
	if (event_data.size() < (unsigned)num) return false;
	return event_data[num].position;
}


//x���W��Ԃ�
float EventManager::GetX() {
	return x;
}

//y���W��Ԃ�
float EventManager::GetY() {
	return y;
}

//�X�V
void EventManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<MapChipManager> map, shared_ptr<Key> key, shared_ptr<Sound> sound){
	if (event_queue.empty()) return;
	
	int time = event_queue.front()->GetTime();
	if (time == 0 && player_stop) {
		player->SetXSpeed(0.0f);
		player->SetYSpeed(0.0f);
	}
	event_queue.front()->Update(player, enemy, effect, key, sound);
	time++;
	event_queue.front()->SetTime(time);
	//�C�x���g���I�����Ă��������
	if (event_queue.front()->GetEndFlag()) {
		EventEnd();
	}
}

//�`��
void EventManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	/*for (unsigned int i = 0; i < event_data.size(); i++) {
		DrawFormatString(128, 64 + (24 * i), GetColor(255, 0, 0), "%s", event_data[i].file_name);
	}*/

	if (event_queue.size() == 0) return;
	event_queue.front()->Draw(image, camera);

}