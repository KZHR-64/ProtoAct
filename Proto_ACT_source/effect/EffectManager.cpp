#pragma once
#include "DxLib.h"
#include "EffectManager.h"
#include "effectlist/BlackOut.h"
#include "effectlist/Explode.h"
#include "effectlist/Smoke.h"
#include "effectlist/LightSphere.h"
#include "effectlist/MarkPoint.h"
#include <math.h>

using namespace std;

EffectManager::EffectManager(){
	SetData();
}

EffectManager::~EffectManager(){
	effect_data.clear();
	effect.clear();
}

//������
void EffectManager::Reset(){
	effect.clear();
}

//�e���̐ݒ�
void EffectManager::SetData() {
	int num;
	ifstream ifs("data/effect/effect_data.csv");

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
		effect_data[num].type = atoi(s.c_str()); //��ނ��擾
		getline(ss, s, ','); //�J���}�܂œǂݍ���
		effect_data[num].image = atoi(s.c_str()); //�摜�̔ԍ����擾
	}
	ifs.close();

}

//�G�t�F�N�g�̔z�u
std::shared_ptr<AbstractEffect> EffectManager::SetEffect(int num, float ini_x, float ini_y, float ini_rate) {
	std::shared_ptr<AbstractEffect> new_effect;

	switch (effect_data[num].type)
	{
	case 0:
		new_effect = make_shared<BlackOut>(this, effect_data[num].image, ini_x, ini_y);
		break;
	case 1:
		new_effect = make_shared<Explode>(this, effect_data[num].image, ini_x, ini_y);
		break;
	case 2:
		new_effect = make_shared<Smoke>(this, effect_data[num].image, ini_x, ini_y);
		break;
	case 3:
		new_effect = make_shared<LightSphere>(this, effect_data[num].image, ini_x, ini_y);
		break;
	case 4:
		new_effect = make_shared<MarkPoint>(this, effect_data[num].image, ini_x, ini_y);
		break;
	default:
		new_effect = make_shared<Explode>(this, effect_data[num].image, ini_x, ini_y);
		break;
	}

	new_effect->SetExRate(ini_rate);

	effect.emplace_back(new_effect);

	return new_effect;
}

//�X�V
void EffectManager::Update(shared_ptr<Sound> sound){
	if (effect.size() == 0) return;
	for (auto& eff : effect) {
		eff->Update(sound);
		eff->SetX(eff->GetX() + eff->GetXSpeed());
		eff->SetY(eff->GetY() + eff->GetYSpeed());
		int time = eff->GetTime();
		time++;
		eff->SetTime(time);
	}

	for (auto eff = effect.begin(); eff != effect.end();) {
		//�����t���O��true�Ȃ����
		if ((*eff)->GetEndFlag()) {
			eff = effect.erase(eff);
		}
		else {
			eff++;
		}
	}
}

//�`��
void EffectManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	if (effect.size() == 0) return;
	for (auto& eff : effect) {
		eff->Draw(image, camera);
	}
}