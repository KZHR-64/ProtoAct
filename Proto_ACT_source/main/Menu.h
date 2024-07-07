#pragma once
#include "ModeBase.h"

struct ChoiceStruct
{
	//�I�����̍\����
	int image; //�g�p����摜
	float ex_rate; //�\���{��
};

class Menu : public ModeBase {
private:
	int count; //�J�E���^�[
	int cursor_pos; //�J�[�\���̈ʒu
	int logo; //�^�C�g�����S

	ChoiceStruct choice[4]; //�I����

	void Reset(); //������
public:
	Menu(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~Menu(); //�f�X�g���N�^
	void Load(); //���O�̃��[�h
	void Update(); //�X�V
	void Draw(); //�`��
};