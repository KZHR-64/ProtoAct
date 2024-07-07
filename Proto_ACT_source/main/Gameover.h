#pragma once
#include "ModeBase.h"

class GameBase;

class Gameover : public ModeBase {
private:
	void Reset(); //������
	
	int cursor_pos; //�J�[�\���̈ʒu
	int select_hundle[2]; //�I�����̉摜

public:
	Gameover(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~Gameover(); //�f�X�g���N�^
	void Load(); //���O�̃��[�h
	void Update(); //�X�V
	void Draw(); //�`��
};