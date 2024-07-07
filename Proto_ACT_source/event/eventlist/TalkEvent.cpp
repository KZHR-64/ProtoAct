#pragma once
#include "DxLib.h"
#include "TalkEvent.h"

using namespace std;

//�R���X�g���N�^
TalkEvent::TalkEvent(EventManager* man, string name, string str, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	chara_name = name;
	message = str;
}

//�f�X�g���N�^
TalkEvent::~TalkEvent() {

}

//�X�V
void TalkEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	
	//���肪������Ă���Ȃ�I��
	if (key->KeyCheckOnce(Jump)) {
		end_flag = true;
	}
}

//�`��
void TalkEvent::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int font = manager->GetFont();
	int image_num = image->GetEffectImage(12, 0);
	Display::Draw(320.0f, 80.0f, false, 0.0f, image_num);
	DrawStringToHandle(16, 10, chara_name.c_str(), GetColor(236, 236, 236), font, GetColor(21, 169, 175));
	vector<string> v;
	string s;
	stringstream ss{ message };
	int i = 0;

	//:�ŉ��s����
	while (getline(ss, s, ':')) {
		v.push_back(s);
	}

	for (const string& s : v) {
		DrawStringToHandle(16, 40 + (32 * i), s.c_str(), GetColor(236, 236, 236), font, GetColor(21, 169, 175));
		i++;
	}
}