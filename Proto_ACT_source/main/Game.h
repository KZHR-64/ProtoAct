#pragma once
#include "ModeBase.h"
#include "Parameter.h"
#include "..\player\Player.h"
#include "..\map\MapChipManager.h"
#include "..\enemy\EnemyManager.h"
#include "..\bullet\BulletManager.h"
#include "..\effect\EffectManager.h"
#include "..\item\ItemManager.h"
#include "..\event\EventManager.h"
#include "..\camera\Camera.h"
#include <memory>

class GameBase;
class Player;
class MapChipManager;
class EnemyManager;
class BulletManager;
class EffectManager;
class ItemManager;
class EventManager;
class Camera;

class Game : public ModeBase {
private:
	std::shared_ptr<Player> player;
	std::shared_ptr<MapChipManager> map;
	std::shared_ptr<EnemyManager> enemy;
	std::shared_ptr<BulletManager> bullet;
	std::shared_ptr<ItemManager> item;
	std::shared_ptr<EventManager> event;
	std::shared_ptr<EffectManager> effect;
	int stage_num; //�X�e�[�W�ԍ�
	int live; //�c�@
	bool pause_flag; //�|�[�Y��ʂ��J���Ă��邩
	int cursor; //�|�[�Y��ʂ̃J�[�\��
	
	void GameUpdate(); //�Q�[���̍X�V
	void PauseUpdate(); //�|�[�Y��ʂ̍X�V

public:
	Game(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~Game(); //�f�X�g���N�^
	void Load(); //���O�̃��[�h
	void Restart(); //�ĊJ
	void Update(); //�X�V
	void Draw(); //�`��
};