#pragma once
#include "DxLib.h"
#include "Game.h"

using namespace std;

Game::Game(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {
	stage_num = modemanager->GetStageNum();

	image->LoadCharaImage(); //�L�����̉摜�����[�h
	image->LoadMapchipImage(); //�}�b�v�`�b�v�̉摜�����[�h
	image->LoadBulletImage(); //�e�̉摜�����[�h
	image->LoadItemImage(); //�A�C�e���̉摜�����[�h
	player = make_shared<Player>();
	map = make_shared<MapChipManager>(stage_num);
	enemy = make_shared<EnemyManager>();
	bullet = make_shared<BulletManager>();
	item = make_shared<ItemManager>();
	event = make_shared<EventManager>();
	effect = make_shared<EffectManager>();

	live = 2; //�c�@��ݒ�
	pause_flag = false; //�|�[�Y��ʂ͕��Ă���
	cursor = 0; //�J�[�\����������

	map->MakeMap(player, enemy, item, event, image, sound, camera);
}

Game::~Game(){
	player.reset();
	map.reset();
	enemy.reset();
	bullet.reset();
	item.reset();
	event.reset();
	camera.reset();

	image->DeleteCharaImage();
	image->DeleteMapchipImage();
	image->DeleteBulletImage();
	image->DeleteItemImage();
	sound->StopBgm();
}

//���O�̃��[�h
void Game::Load() {
	if (loaded) return; //���[�h�ς݂Ȃ�I��

	loaded = true; //���[�h�����t���O��true��
}

//�ĊJ
void Game::Restart() {
	player->Reset();
	event->Reset();
	enemy->Reset();
	bullet->Reset();
	effect->Reset();
	item->Reset();

	map->MakeMap(player, enemy, item, event, image, sound, camera);
}

//�Q�[���̍X�V
void Game::GameUpdate() {

	bool player_stop = event->GetPlayerStop();
	bool enemy_stop = event->GetEnemyStop();

	camera->SetScrollX(player->GetX());
	camera->SetScrollY(player->GetY());
	
	if (!player_stop) {
		map->Update(player, enemy, bullet, effect, image, key, sound, camera); //�}�b�v�̍X�V
	}
	map->EventHitCheck(event, player->GetX(), player->GetY());
	event->Update(player, enemy, effect, map, key, sound);

	player_stop = event->GetPlayerStop();
	enemy_stop = event->GetEnemyStop();
	
	if (!player_stop) {
		player->Update(effect, key, sound); //���@�̍X�V
	}
	item->Update(player, enemy, effect, sound); //�A�C�e���̍X�V
	map->AdjustPosition(); //�}�b�v�̈ʒu����
	player->AdjustPosition(map, (player_stop || enemy_stop)); //���@�̈ʒu����
	if (!player_stop) {
		player->AttackCheck(bullet, effect, key, sound); //���@�̍U��
	}
	if (!enemy_stop) {
		enemy->Update(map, bullet, player, effect, sound, camera); //�G�̍X�V
	}
	bullet->Update(player, enemy, item, effect, key, sound, camera); //�e�̍X�V

	effect->Update(sound); //�G�t�F�N�g�̍X�V

	item->HitCheckPlayer(player, effect, sound);
	bullet->HitCheckMap(map);
	enemy->HitCheckBullet(bullet, effect, sound);
	//enemy->HitCheckEnemy(effect);
	player->HitCheckEnemy(enemy, effect, sound);
	player->HitCheckBullet(bullet, sound);

	enemy->SpawnCheck(camera);

	//�}�b�v�ړ��̑��삪�s���Ă��邩�m�F
	map->WarpHitCheck(event, key, sound, player->GetX(), player->GetY());

	//���[�v��������������
	if (map->GetWarpFlag() && !event->GetPlayerStop()) {
		Restart(); //���̃}�b�v����ĊJ
	}

	//�܂��N���A���肪�o�Ă��Ȃ���ԂŁA�{�X��|�����Ȃ�
	if (!event->GetClearFlag() && enemy->GetBeatBoss()) {
		event->SetEvent(1); //�N���A����̃C�x���g���J�n
	}

	//�~�X�����Ȃ�
	if (player->GetHp() <= 0 && !player_stop) {
		event->AllEventEnd();
		event->SetEvent(2); //�~�X����̃C�x���g���J�n
	}

	//+��������Ă���Ȃ�
	if (key->KeyCheckOnce(Plus) /*&& !player_stop*/) {
		sound->PlaySoundEffect(1); //���ʉ���炷
		pause_flag = true; //�|�[�Y��ʂ��J��
	}
}

//�|�[�Y��ʂ̍X�V
void Game::PauseUpdate() {
	//�ォ����������Ă���Ȃ�
	if (key->KeyCheckOnce(Up) || key->KeyCheckOnce(Down)) {
		cursor = (cursor + 1) % 2; //�J�[�\�����ړ�
	}

	//���肪������Ă���Ȃ�
	if (key->KeyCheckOnce(Jump)) {
		switch (cursor)
		{
		case 0:
			pause_flag = false; //�|�[�Y��ʂ����
			break;
		case 1:
			//event->SetClearFlag(true); //�X�e�[�W�Z���N�g�ɖ߂�悤�ɂ���
			modemanager->ChangeMode(Next_Back); //��O�̉�ʂɖ߂�
			break;
		default:
			break;
		}
	}

	//+��������Ă���Ȃ�
	if (key->KeyCheckOnce(Plus)) {
		pause_flag = false; //�|�[�Y��ʂ����
	}
}

//�X�V
void Game::Update(){

	//�|�[�Y��ԂȂ�
	if (pause_flag) {
		PauseUpdate(); //�|�[�Y��ʂ̍X�V
	}
	//�����łȂ����
	else {
		GameUpdate(); //�Q�[���̍X�V
	}

	//�N���A�����Ȃ�
	if (event->GetClearFlag()) {
		modemanager->ChangeMode(Next_Back); //��O�̉�ʂɖ߂�
	}

	//���Ȃ����Ȃ�
	if (event->GetRestartFlag()) {
		live--; //�c�@�����炷
		//�c�@������Ȃ�
		if (0 <= live) {
			Restart(); //�~�X�����}�b�v����ĊJ����
		}
		else
		{
			modemanager->ChangeMode(Next_Gameover, true); //���[�h���Q�[���I�[�o�[�ɕύX
		}
	}
}

//�`��
void Game::Draw(){
	map->Draw(image, camera);
	enemy->Draw(image, camera);
	player->Draw(image, camera);
	item->Draw(image, camera);
	bullet->Draw(image, camera);
	effect->Draw(image, camera);
	event->Draw(image, camera);
	//DrawFormatString(0, 0, GetColor(0, 0, 255), "�Q�[��%d%d%d%d", stage_num, enemy->GetBeatBoss(), enemy->GetBossFlag(), event->GetPlayerStop());

	//�|�[�Y��ԂȂ�
	if (pause_flag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); //�`�惂�[�h�𔽉f

		DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true); //��ʂ��Â�����

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�`�惂�[�h��߂�
		DrawFormatString(320, 240, GetColor(0, 0, 255), "�|�[�Y%d", cursor);
	}
}