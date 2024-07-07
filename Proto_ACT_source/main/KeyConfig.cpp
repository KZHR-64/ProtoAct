#pragma once
#include "DxLib.h"
#include "KeyConfig.h"

using namespace std;

KeyConfig::KeyConfig(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {

	Reset();

	message_font = CreateFontToHandle("Meiryo UI", 24, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1); //�t�H���g���

	key_map[KEY_INPUT_BACK] = "BackSpace";	// �o�b�N�X�y�[�X�L�[
	key_map[KEY_INPUT_TAB] = "Tab";	// �^�u�L�[
	key_map[KEY_INPUT_RETURN] = "Enter";	// �G���^�[�L�[
	key_map[KEY_INPUT_LSHIFT] = "LShift";	// ���V�t�g�L�[
	key_map[KEY_INPUT_RSHIFT] = "Rshift";	// �E�V�t�g�L�[
	key_map[KEY_INPUT_LCONTROL] = "LCtrl";	// ���R���g���[���L�[
	key_map[KEY_INPUT_RCONTROL] = "Rctrl";	// �E�R���g���[���L�[
	key_map[KEY_INPUT_ESCAPE] = "Esc";	// �G�X�P�[�v�L�[
	key_map[KEY_INPUT_SPACE] = "Space";	// �X�y�[�X�L�[
	key_map[KEY_INPUT_PGUP] = "PgUp";	// �o�������t�o�L�[
	key_map[KEY_INPUT_PGDN] = "PgDn";	// �o�������c�������L�[
	key_map[KEY_INPUT_END] = "End";	// �G���h�L�[
	key_map[KEY_INPUT_HOME] = "Home";	// �z�[���L�[
	key_map[KEY_INPUT_LEFT] = "��";	// ���L�[
	key_map[KEY_INPUT_UP] = "��";	// ��L�[
	key_map[KEY_INPUT_RIGHT] = "��";	// �E�L�[
	key_map[KEY_INPUT_DOWN] = "��";	// ���L�[
	key_map[KEY_INPUT_INSERT] = "Insert";	// �C���T�[�g�L�[
	key_map[KEY_INPUT_DELETE] = "Delete";	// �f���[�g�L�[
	key_map[KEY_INPUT_MINUS] = "-";	// �|�L�[
	key_map[KEY_INPUT_YEN] = "\\";	// ���L�[
	key_map[KEY_INPUT_PREVTRACK] = "^";	// �O�L�[
	key_map[KEY_INPUT_PERIOD] = ".";	// �D�L�[
	key_map[KEY_INPUT_SLASH] = "/";	// �^�L�[
	key_map[KEY_INPUT_LALT] = "LAlt";	// ���`�k�s�L�[
	key_map[KEY_INPUT_RALT] = "RAlt";	// �E�`�k�s�L�[
	key_map[KEY_INPUT_SCROLL] = "ScrollLock";	// ScrollLock�L�[
	key_map[KEY_INPUT_SEMICOLON] = ";";	// �G�L�[
	key_map[KEY_INPUT_COLON] = ":";	// �F�L�[
	key_map[KEY_INPUT_LBRACKET] = "[";	// �m�L�[
	key_map[KEY_INPUT_RBRACKET] = "]";	// �n�L�[
	key_map[KEY_INPUT_AT] = "@";	// ���L�[
	key_map[KEY_INPUT_BACKSLASH] = "�_";	// �_�L�[
	key_map[KEY_INPUT_COMMA] = ",";	// �C�L�[
	key_map[KEY_INPUT_CAPSLOCK] = "CapsLock";	// CaspLock�L�[
	key_map[KEY_INPUT_PAUSE] = "Pause";	// PauseBreak�L�[
	key_map[KEY_INPUT_NUMPAD0] = "0";	// �e���L�[�O
	key_map[KEY_INPUT_NUMPAD1] = "1";	// �e���L�[�P
	key_map[KEY_INPUT_NUMPAD2] = "2";	// �e���L�[�Q
	key_map[KEY_INPUT_NUMPAD3] = "3";	// �e���L�[�R
	key_map[KEY_INPUT_NUMPAD4] = "4";	// �e���L�[�S
	key_map[KEY_INPUT_NUMPAD5] = "5";	// �e���L�[�T
	key_map[KEY_INPUT_NUMPAD6] = "6";	// �e���L�[�U
	key_map[KEY_INPUT_NUMPAD7] = "7";	// �e���L�[�V
	key_map[KEY_INPUT_NUMPAD8] = "8";	// �e���L�[�W
	key_map[KEY_INPUT_NUMPAD9] = "9";	// �e���L�[�X
	key_map[KEY_INPUT_MULTIPLY] = "*";	// �e���L�[���L�[
	key_map[KEY_INPUT_ADD] = "+";	// �e���L�[�{�L�[
	key_map[KEY_INPUT_SUBTRACT] = "-";	// �e���L�[�|�L�[
	key_map[KEY_INPUT_DECIMAL] = ".";	// �e���L�[�D�L�[
	key_map[KEY_INPUT_DIVIDE] = "/";	// �e���L�[�^�L�[
	key_map[KEY_INPUT_NUMPADENTER] = "Enter";	// �e���L�[�̃G���^�[�L�[
	key_map[KEY_INPUT_F1] = "F1";	// �e�P�L�[
	key_map[KEY_INPUT_F2] = "F2";	// �e�Q�L�[
	key_map[KEY_INPUT_F3] = "F3";	// �e�R�L�[
	key_map[KEY_INPUT_F4] = "F4";	// �e�S�L�[
	key_map[KEY_INPUT_F5] = "F5";	// �e�T�L�[
	key_map[KEY_INPUT_F6] = "F6";	// �e�U�L�[
	key_map[KEY_INPUT_F7] = "F7";	// �e�V�L�[
	key_map[KEY_INPUT_F8] = "F8";	// �e�W�L�[
	key_map[KEY_INPUT_F9] = "F9";	// �e�X�L�[
	key_map[KEY_INPUT_F10] = "F10";	// �e�P�O�L�[
	key_map[KEY_INPUT_F11] = "F11";	// �e�P�P�L�[
	key_map[KEY_INPUT_F12] = "F12";	// �e�P�Q�L�[
	key_map[KEY_INPUT_A] = "A";	// �`�L�[
	key_map[KEY_INPUT_B] = "B";	// �a�L�[
	key_map[KEY_INPUT_C] = "C";	// �b�L�[
	key_map[KEY_INPUT_D] = "D";	// �c�L�[
	key_map[KEY_INPUT_E] = "E";	// �d�L�[
	key_map[KEY_INPUT_F] = "F";	// �e�L�[
	key_map[KEY_INPUT_G] = "G";	// �f�L�[
	key_map[KEY_INPUT_H] = "H";	// �g�L�[
	key_map[KEY_INPUT_I] = "I";	// �h�L�[
	key_map[KEY_INPUT_J] = "J";	// �i�L�[
	key_map[KEY_INPUT_K] = "K";	// �j�L�[
	key_map[KEY_INPUT_L] = "L";	// �k�L�[
	key_map[KEY_INPUT_M] = "M";	// �l�L�[
	key_map[KEY_INPUT_N] = "N";	// �m�L�[
	key_map[KEY_INPUT_O] = "O";	// �n�L�[
	key_map[KEY_INPUT_P] = "P";	// �o�L�[
	key_map[KEY_INPUT_Q] = "Q";	// �p�L�[
	key_map[KEY_INPUT_R] = "R";	// �q�L�[
	key_map[KEY_INPUT_S] = "S";	// �r�L�[
	key_map[KEY_INPUT_T] = "T";	// �s�L�[
	key_map[KEY_INPUT_U] = "U";	// �t�L�[
	key_map[KEY_INPUT_V] = "V";	// �u�L�[
	key_map[KEY_INPUT_W] = "W";	// �v�L�[
	key_map[KEY_INPUT_X] = "X";	// �w�L�[
	key_map[KEY_INPUT_Y] = "Y";	// �x�L�[
	key_map[KEY_INPUT_Z] = "Z";	// �y�L�[
	key_map[KEY_INPUT_0] = "0";	// �O�L�[
	key_map[KEY_INPUT_1] = "1";	// �P�L�[
	key_map[KEY_INPUT_2] = "2";	// �Q�L�[
	key_map[KEY_INPUT_3] = "3";	// �R�L�[
	key_map[KEY_INPUT_4] = "4";	// �S�L�[
	key_map[KEY_INPUT_5] = "5";	// �T�L�[
	key_map[KEY_INPUT_6] = "6";	// �U�L�[
	key_map[KEY_INPUT_7] = "7";	// �V�L�[
	key_map[KEY_INPUT_8] = "8";	// �W�L�[
	key_map[KEY_INPUT_9] = "9";	// �X�L�[
}

KeyConfig::~KeyConfig() {
	key_map.clear();
	DeleteFontToHandle(message_font);
}

//������
void KeyConfig::Reset() {

	key_cursor = 0; //�J�[�\���̈ʒu
	pad_cursor = 0; //�J�[�\���̈ʒu

}

//���O�̃��[�h
void KeyConfig::Load() {
	if (loaded) return; //���[�h�ς݂Ȃ�I��

	sound->LoadBgm(1); //�Ȃ����[�h
	image->LoadBackImage(2); //�w�i�����[�h

	key->GetKey(button); //�L�[�����擾

	loaded = true; //���[�h�����t���O��true��
}

//�X�V
void KeyConfig::Update(){
	//�ؑփt���O��true�̏ꍇ
	if (start_flag) {
		Reset();
		sound->PlayBgm(1); //�Ȃ��Đ�
		start_flag = false; //�ؑփt���O��false��
	}

	int key_num = key->GetKeyOnce(); //������Ă���L�[���擾
	int pad = key->GetPadOnce(); //������Ă���{�^�����擾
	int flag = false; //�R���t�B�O�I���t���O

	//������Ă���L�[������ꍇ
	if (key_num != -1) {
		// �Ō�܂Őݒ肵�Ă��Ȃ��ꍇ
		if (key_cursor < BUTTON) {
			//���̃L�[���m�F
			for (int i = 0; i < BUTTON; i++)
			{
				if (i == key_cursor) continue; //i���J�[�\���ƈ�v�����ꍇ�̓X���[
				//���łɃL�[���ݒ肳��Ă���ꍇ
				if (button[i].key == key_num) {
					button[i].key = button[key_cursor].key; //����ւ���
				}
			}
			button[key_cursor].key = key_num; //�����ꂽ�L�[���i�[
			key_cursor++; //�J�[�\��������Ɉړ�
		}
		// �Ō�܂Őݒ肵�Ă���ꍇ
		else {
			flag = true; //�R���t�B�O�I���t���O�𗧂Ă�
		}
		sound->PlaySoundEffect(1); //���ʉ���炷
	}

	//������Ă���{�^��������ꍇ
	if (pad != -1) {
		// �Ō�܂Őݒ肵�Ă��Ȃ��ꍇ
		if (pad_cursor < BUTTON) {
			//���̃{�^�����m�F
			for (int i = 0; i < BUTTON; i++)
			{
				if (i == pad_cursor) continue; //i���J�[�\���ƈ�v�����ꍇ�̓X���[
				//���łɃ{�^�����ݒ肳��Ă���ꍇ
				if (button[i].pad == pad) {
					button[i].pad = button[pad_cursor].pad; //����ւ���
				}
			}
			button[pad_cursor].pad = pad; //�����ꂽ�{�^�����i�[
			pad_cursor++; //�J�[�\��������Ɉړ�
		}
		// �Ō�܂Őݒ肵�Ă���ꍇ
		else {
			flag = true; //�R���t�B�O�I���t���O�𗧂Ă�
		}
		sound->PlaySoundEffect(1); //���ʉ���炷
	}

	//�R���t�B�O�I���t���O��true�̏ꍇ
	if (flag) {
		key->SetKey(button); //�ݒ���m�肷��
		key->SaveSetting(); //�ݒ��ۑ�����
		modemanager->ChangeMode(Next_Back); //���j���[�ɖ߂�
	}
}

//�`��
void KeyConfig::Draw(){
	int back = image->GetBackImage(2); //�w�i���擾
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y / 2, false, 0.0f, back); //�w�i��`��

	//�J�[�\���̑傫�����w��
	int cursor_size_x = 256;
	int cursor_size_y = 60;

	//�J�[�\���̈ʒu���w��
	int key_cursor_x = 616;
	int key_cursor_y = 98 + (cursor_size_y * key_cursor);

	//�J�[�\���̈ʒu���w��
	int pad_cursor_x = 952;
	int pad_cursor_y = 98 + (cursor_size_y * pad_cursor);

	//�I������ʒu�ȊO�͏����Â�����
	for (int i = 0; i <= BUTTON; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		if (i != key_cursor)DrawBox(key_cursor_x, 98 + (cursor_size_y * i), key_cursor_x + cursor_size_x, 98 + (cursor_size_y * i) + cursor_size_y, GetColor(128, 128, 128), true);
		if (i != pad_cursor) DrawBox(pad_cursor_x, 98 + (cursor_size_y * i), pad_cursor_x + cursor_size_x, 98 + (cursor_size_y * i) + cursor_size_y, GetColor(128, 128, 128), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	for (int i = 0; i < BUTTON; i++)
	{
		DrawFormatStringToHandle(key_cursor_x + 24, 98 + (cursor_size_y * i) + 14, GetColor(255, 255, 255), message_font, "%s", key_map[button[i].key].c_str());
		
		int pad_num = (int)log2((float)(button[i].pad));
		DrawFormatStringToHandle(pad_cursor_x + 24, 98 + (cursor_size_y * i) + 14, GetColor(255, 255, 255), message_font, "%d %d", pad_num, button[i].pad);
	}
}