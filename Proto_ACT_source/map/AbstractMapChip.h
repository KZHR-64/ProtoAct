#pragma once
#include "../character/CharacterBase.h"
#include "MapChipManager.h"
#include "../Define.h"
#include "../player/Player.h"
#include "../bullet/BulletManager.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../system/Sound.h"
#include "../tool/Display.h"
#include <memory>

class MapChipManager;
class BulletManager;
class Player;
class EnemyManager;
class EffectManager;

class AbstractMapChip : public CharacterBase{
protected:
	MapChipManager* manager;

	bool draw_flag; //描画するか
	int link_img_x1; //連結した画像番号（横、つなぎ）
	int link_img_x2; //連結した画像番号（横、終端）
	int link_img_y1; //連結した画像番号（縦、つなぎ）
	int link_img_y2; //連結した画像番号（縦、終端）
	float last_x; //一つ前のx座標
	float last_y; //一つ前のy座標
	int size_x; //横の大きさ
	int size_y; //縦の大きさ
	bool hit_map; //他のマップチップに当たるか
	bool through; //すり抜けるか
	int breakable; //壊せるか(0=壊せない、1=脆い、2=硬い)
	float friction; //摩擦
	float move_x; //乗っているキャラクターに干渉する速度
	float move_y; //乗っているキャラクターに干渉する速度
	bool step; //キャラが乗っているか
	bool hit_left; //左側に攻撃が当たったか
	bool hit_right; //右側に攻撃が当たったか
	bool hit_top; //上側に攻撃が当たったか
	bool hit_bottom; //下側に攻撃が当たったか
	int link_x; //連結したマップチップ数（横）
	int link_y; //連結したマップチップ数（縦）
public:
	AbstractMapChip(MapChipManager* man, int num); //コンストラクタ(画像の番号)
	~AbstractMapChip(); //デストラクタ

	bool GetLiveFlag(); //動作するかを取得
	void SetLiveFlag(bool flag); //動作するかを設定
	bool GetDrawFlag(); //描画するかを取得
	void SetDrawFlag(bool flag); //描画するかを設定
	void SetLinkImgX(int ini_x1, int ini_x2); //連結する画像を設定（imageに足す数）
	void SetLinkImgY(int ini_y1, int ini_y2); //連結する画像を設定
	float GetLastX(); //一つ前のx座標を返す
	void SetLastX(float set_x); //一つ前のx座標を設定
	float GetLastY(); //一つ前のy座標を返す
	void SetLastY(float set_y); //一つ前のy座標を設定
	float GetAmountX(); //x方向の移動量を取得
	float GetAmountY(); //y方向の移動量を取得
	int GetSizeX(); //マップチップの横の大きさを返す
	void SetSizeX(int set_size); //マップチップの横の大きさを設定
	int GetSizeY(); //マップチップの縦の大きさを返す
	void SetSizeY(int set_size); //マップチップの縦の大きさを設定
	bool GetHitMap(); //他のマップに当たるかを取得
	void SetHitMap(bool flag); //他のマップに当たるかを設定
	bool GetThrough(); //すり抜けるかを取得
	void SetThrough(bool flag); //すり抜けるかを設定
	int GetBreakable(); //壊せるかを取得
	void SetBreakable(int set_bre); //壊せるかを設定
	float GetFriction(); //摩擦を取得
	void SetFriction(float set_fri); //摩擦を取得
	float GetMoveX(); //乗っているキャラに対するx方向の速度を返す
	void SetMoveX(float set_x); //乗っているキャラに対するx方向の速度を設定
	float GetMoveY(); //乗っているキャラに対するy方向の速度を返す
	void SetMoveY(float set_y); //乗っているキャラに対するy方向の速度を設定
	bool GetStep(); //キャラが乗っているかを取得
	void SetStep(bool flag); //キャラが乗っているかを設定
	bool GetHitLeft(); //左側に攻撃が当たったかを取得
	void SetHitLeft(bool flag); //左側に攻撃が当たったかを設定
	bool GetHitRight(); //右側に攻撃が当たったかを取得
	void SetHitRight(bool flag); //右側に攻撃が当たったかを設定
	bool GetHitTop(); //上側に攻撃が当たったかを取得
	void SetHitTop(bool flag); //上側に攻撃が当たったかを設定
	bool GetHitBottom(); //下側に攻撃が当たったかを取得
	void SetHitBottom(bool flag); //下側に攻撃が当たったかを設定
	void SetLinkX(int ini_link); //連結したマップチップ数を設定
	void SetLinkY(int ini_link); //連結したマップチップ数を設定

	virtual void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound) = 0;
};