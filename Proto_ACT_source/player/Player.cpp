#pragma once
#include "DxLib.h"
#include "Player.h"
#include <math.h>

using namespace std;

Player::Player(){

	message_font = CreateFontToHandle("Meiryo UI", 32, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2); //フォント情報

	head.def_angle = atan2f(-30.0f, 0.0f);
	head.def_distance = sqrtf(30.0f * 30.0f);
	head.spin_angle = 0.0f;
	head.spin_point = 0.0f;

	body.def_angle = atan2f(8.0f, 0.0f);
	body.def_distance = sqrtf(8.0f * 8.0f);
	body.spin_angle = 0.0f;
	body.spin_point = 0.0f;

	right_leg.def_angle = atan2f(18.0f, 8.0f);
	right_leg.def_distance = sqrtf((18.0f * 18.0f) + (8.0f * 8.0f));
	right_leg.spin_angle = atan2f(0.0f, 12.0f);
	right_leg.spin_point = sqrtf(12.0f * 12.0f);

	left_leg.def_angle = atan2f(18.0f, -8.0f);
	left_leg.def_distance = sqrtf((18.0f * 18.0f) + (8.0f * 8.0f));
	left_leg.spin_angle = atan2f(0.0f, 12.0f);
	left_leg.spin_point = sqrtf(12.0f * 12.0f);

	right_arm.def_angle = atan2f(-12.0f, 12.0f);
	right_arm.def_distance = sqrtf((12.0f * 12.0f) + (12.0f * 12.0f));
	right_arm.spin_angle = atan2f(0.0f, 10.0f);
	right_arm.spin_point = sqrtf(10.0f * 10.0f);

	left_arm.def_angle = atan2f(-12.0f, -12.0f);
	left_arm.def_distance = sqrtf((12.0f * 12.0f) + (12.0f * 12.0f));
	left_arm.spin_angle = atan2f(0.0f, 10.0f);
	left_arm.spin_point = sqrtf(10.0f * 10.0f);

	Reset(); //初期化
	hp = 6;
	weapon = 0;

	attack_move.push_back(&Player::Attack1);
	attack_move.push_back(&Player::Attack2);
	attack_move.push_back(&Player::Attack3);
	attack_move.push_back(&Player::Attack4);

	//当たり判定を設定
	SetHit(0.0f, 0.0f, 16.0f);
	SetHit(0.0f, 32.0f, 16.0f);
	hit[0].check_bottom = false; //足下の判定は行わない
	hit[1].check_top = false; //頭上の判定は行わない

}

Player::~Player(){
	attack_move.clear();
}

//初期化
void Player::Reset(){
	if(hp <= 0) hp = 6; //HPを初期化
	x = 128.0f;
	y = 128.0f;
	sx = 0.0f; //速度を初期化
	sy = 0.0f; //速度を初期化
	angle = 0.0f; //角度を初期化
	spin_speed = 0.0f; //回転速度を初期化
	move_time = 0;
	move_type = Move_Stand; //静止状態に設定
	jump_flag = false; //ジャンプ状態を初期化
	flying_flag = false; //飛行フラグを初期化
	through_flag = false; //すり抜けフラグを初期化
	damaged = false; //ダメージを受けたフラグを初期化
	damage_time = false; //ダメージ動作の時間を初期化
	handle = 0; //表示する画像の番号を初期化
	inv_time = 0; //無敵時間を初期化
	draw_flag = true; //描画フラグを初期化
	move_flag = true; //操作フラグを初期化
	key_num = 0; //鍵の数を初期化

	weapon_max = 4; //武器の数を初期化

	body.angle = angle;
	right_leg.angle = angle;
	left_leg.angle = angle;
	right_arm.angle = 0.0f;
	left_arm.angle = angle;

	SetParts();

	catch_effect = NULL;
	step_mapchip = NULL;

	attack.flag = false; //攻撃フラグを初期化
	attack.time = 0; //押した時間を初期化
	attack.stop = false; //足を止めるフラグを初期化
	attack.energy = max_energy; //攻撃エネルギーを初期化
	attack.res_time = 0; //回復時間を初期化
	
}

//入力履歴の確認
bool Player::RecordCheck(bool record[], int point){

	for (int i = 1; i < RECORD; i++){
		//前に押されているか
		if (record[i]) return true; //押されていたらtrue
	}
	return false; //なかったらfalse
}

//自機の操作
void Player::Control(shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	if (!move_flag) {
		attack.flag = false;
		attack.time = 0;
		return; //操作不可なら終了
	}

	//左が押されていたら
	if (key->KeyCheck(Left) && !attack.flag) {
		//攻撃状態でない場合
		if (!attack.flag) {
			reverse = true; //向きを左に
		}
		// 直前に左が押されていなかったら
		if (!commando[Left][0]) {
			//その前に押されていた場合
			if (RecordCheck(commando[Left], 1)) {
			}
		}
	}
	//右が押されていたら
	if (key->KeyCheck(Right) && !attack.flag) {
		//攻撃状態でない場合
		if (!attack.flag) {
			reverse = false; //向きを右に
		}
		// 直前に右が押されていなかったら
		if (!commando[Right][0]) {
			//その前に押されていた場合
			if (RecordCheck(commando[Right], 1)) {
			}
		}
	}

	float max_speed = (reverse ? -move_speed : move_speed); //向きによって速度上限を設定

	float start_speed = (reverse ? -0.5f : 0.5f); //移動し始めの速度(向きによって速度を設定)

	float accel = (reverse ? -0.2f : 0.2f); //加速速度(向きによって加速速度を設定)

	float slip = 0.9f; //減速

	//マップチップに乗っていたらその滑りやすさを加える
	if (step_mapchip != NULL) {
		float sl = 1.0f - step_mapchip->GetFriction();
		slip += (sl / 10.0f);
	}

	//両方押されていないか両方押されているか攻撃中なら
	if ((!key->KeyCheck(Left) && !key->KeyCheck(Right)) || (key->KeyCheck(Left) && key->KeyCheck(Right)) || attack.flag) {
		if (fabsf(sx) <= (move_speed * 0.5f) && !jump_flag) sx = 0.0f; //歩きの速度の5割でジャンプしてないなら停止
		else {
			sx *= slip; //違うなら減速
			if (fabsf(sx) <= 0.1f) sx = 0.0f; //かなり減速したなら停止
		}
	}
	//どちらか押されていたら
	else {
		if (fabsf(sx) < fabsf(start_speed)) sx = start_speed; //歩き始めの速度未満で進んでいるか止まっているなら速度を0.5に
		else sx += (fabsf(sx) * accel); //加速(減速)
		if (fabsf(max_speed) < fabsf(sx)) sx = max_speed; //速度が上限を超えていたら調整
	}

	//ジャンプ
	//ジャンプが押されていて、今ジャンプしていなくて、攻撃していないなら
	if (key->KeyCheck(Jump) && !jump_flag && !jumped && !attack.flag) {
		//初めて押されたかちょっと前から押されていたら
		if (!commando[Jump][0] || RecordCheck(jump_book)) {
			jump_flag = true; //フラグをtrueに
			jump_time = 0; //ジャンプ時間を0に
			jumped = true; //ボタンが押されたことを反映
			sy = -JUMP_SPEED; //上昇開始
			effect->SetEffect(10, x, y + 40.0f, 0.25f); //エフェクトを発生
			effect->SetEffect(10, x - 16.0f, y + 32.0f, 0.4f);
			effect->SetEffect(10, x + 16.0f, y + 32.0f, 0.4f);
			sound->PlaySoundEffect(5); //効果音を鳴らす
		}
	}

	//床すり抜け
	//下が押されていて、ジャンプしていなかったら
	if (key->KeyCheckOnce(Down) && !jump_flag && !through_flag) {
		through_flag = true; //すり抜け開始
		jump_flag = true;
		jump_time = JUMP_TIME_MAX;
		sy = JUMP_SPEED / 10.0f;
	}
}

//ダメージ動作
void Player::DamageAction() {
	//ダメージを受けたばかりなら
	if (damage_time == DAMAGE_TIME_MAX) {
		sx = 0.0f; //x速度を初期化
		sy = 0.0f; //y速度を初期化
		move_type = Move_Stand; //動作を静止状態に
	}
	damage_time--; //動作時間が減少
	//動作時間が完了したら
	if (damage_time == 0) {
		damaged = false; //フラグをfalseに
	}
}

//移動
void Player::Move(shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	//ダメージを受けていたら
	if (damaged) {
		DamageAction(); //ダメージ動作
	}
	//受けていなかったら
	else {
		Control(effect, key, sound); //通常の操作
	}
}

//当たり判定の更新
void Player::HitUpdate() {
	for (int i = 0; i < 2; i++) {
		hit[i].x = x + (hit[i].distance * cosf(hit[i].angle));
		hit[i].y = y + (hit[i].distance * sinf(hit[i].angle));
	}
}

//表示する画像を決定
void Player::SetGraphic() {
	int old_move = move_type; //前の動作

	//ダッシュ攻撃をしているなら
	if (attack.flag && weapon == 3) {
		move_type = Move_Dash; //動作をダッシュ状態に
	}
	//攻撃しているなら
	else if (attack.flag) {
		move_type = Move_Attack; //動作を攻撃状態に
	}
	//ジャンプしているなら
	else if (jump_flag) {
		move_type = Move_Jump; //動作をジャンプ状態に
	}
	//歩いているなら
	else if (0.8f < fabsf(sx)) {
		move_type = Move_Walk; //動作を歩行状態に
	}
	//止まっているなら
	else {
		move_type = Move_Stand; //動作を静止状態に
	}

	//前の動作と同じなら
	if (old_move == move_type) {
		move_time++; //動作時間を増加
	}
	//前の動作と異なれば
	else {
		move_time = 0; //動作時間を0に
		//停止状態でなければ
		if (move_type != Move_Stand) {
			//パーツの角度を初期化
			body.angle = 0.0f;
			right_leg.angle = 0.5f * PI;
			right_arm.angle = 0.5f * PI;
			left_leg.angle = 0.5f * PI;
			left_arm.angle = 0.5f * PI;
		}
	}
}

//キーの履歴を更新
void Player::SetKeyRecord(shared_ptr<Key> key) {
	//入力履歴の更新
	for (int i = 0; i < BUTTON; i++){
		for (int j = RECORD - 1; j > 0; j--){
			commando[i][j] = commando[i][j - 1]; //前のキーを取得
		}
	}
	for (int i = 0; i < BUTTON; i++) commando[i][0] = key->KeyCheck(i); //今押されているのを挿入

	for (int i = RECORD - 1; i > 0; i--) jump_book[i] = jump_book[i - 1]; //前のジャンプを押した履歴を取得
	jump_book[0] = key->KeyCheckOnce(Jump); //今初めてジャンプを押したか挿入
	//ジャンプしてからボタンが離されたら
	if (jumped && !key->KeyCheck(Jump)) {
		jumped = false; //ボタンが離されたのを反映
	}

}

//パーツをそろえる
void Player::SetParts() {
	//歩いているなら手足を振る
	if (move_type == Move_Walk) {
		body.angle = Calculation::HomingSpin(body.angle, PI * 0.025f, 0.0f);
		right_leg.angle = 0.5f * PI + (0.125f * PI * sinf(PI * 2.0f / 60.0f * move_time)); //足を前後に振る
		right_arm.angle = 0.5f * PI - (0.25f * PI * sinf(PI * 2.0f / 60.0f * move_time)); //腕を前後に振る
		left_leg.angle = 0.5f * PI - (0.125f * PI * sinf(PI * 2.0f / 60.0f * move_time)); //足を前後に振る
		left_arm.angle = 0.5f * PI + (0.25f * PI * sinf(PI * 2.0f / 60.0f * move_time)); //腕を前後に振る
	}
	//攻撃しているなら腕を前に出す
	else if (move_type == Move_Attack) {
		body.angle = Calculation::HomingSpin(body.angle, PI * 0.025f, 0.0f);
		right_arm.angle = 0.0f;
	}
	//ダッシュ攻撃をしているなら腕を後ろにする
	else if (move_type == Move_Dash) {
		body.angle = Calculation::HomingSpin(body.angle, PI * 0.025f, 0.125f * PI);
		right_arm.angle = Calculation::HomingSpin(right_arm.angle, PI * 0.125, 0.875f * PI);
		left_arm.angle = Calculation::HomingSpin(left_arm.angle, PI * 0.1f, 0.875f * PI);
	}
	//ジャンプしているなら腕を上げ、足は少し閉じる
	else if (move_type == Move_Jump) {
		body.angle = Calculation::HomingSpin(body.angle, PI * 0.025f, 0.0f);
		right_arm.angle = Calculation::HomingSpin(right_arm.angle, PI * 0.125f, -0.475f * PI);
		left_arm.angle = Calculation::HomingSpin(left_arm.angle, PI * 0.125f, -0.475f * PI);
		right_leg.angle = Calculation::HomingSpin(right_leg.angle, PI * 0.025f, 0.625f * PI);
		left_leg.angle = Calculation::HomingSpin(left_leg.angle, PI * 0.025f, 0.375f * PI);
	}
	//止まっているなら戻す
	else {
		body.angle = Calculation::HomingSpin(body.angle, PI * 0.025, 0.0f);
		right_leg.angle = Calculation::HomingSpin(right_leg.angle, PI * 0.05f, 0.5f * PI);
		right_arm.angle = Calculation::HomingSpin(right_arm.angle, PI * 0.05f, 0.5f * PI);
		left_leg.angle = Calculation::HomingSpin(left_leg.angle, PI * 0.05f, 0.5f * PI);
		left_arm.angle = Calculation::HomingSpin(left_arm.angle, PI * 0.05f, 0.5f * PI);
	}

	head.angle = 0.0f;

	float sum_angle = 0.0f; //合計の角度
	float sum_spin = 0.0f; //合計の回転角
	float direction = (reverse) ? -1.0f : 1.0f; //向きに応じた計算用

	//胴体
	body.total_angle = (angle + body.angle) * direction;
	sum_angle = (body.def_angle + body.total_angle) * direction;
	body.x = x + (body.def_distance * cosf(sum_angle));
	body.y = y + (body.def_distance * sinf(sum_angle)) * direction;

	//頭
	head.total_angle = body.total_angle + head.angle;
	sum_angle = head.def_angle + head.total_angle;
	head.x = body.x + (head.def_distance * cosf(sum_angle));
	head.y = body.y + (head.def_distance * sinf(sum_angle));

	//右足
	right_leg.total_angle = body.total_angle + (right_leg.angle * direction);
	sum_angle = body.total_angle + (right_leg.def_angle * direction);
	sum_spin = (right_leg.spin_angle + right_leg.total_angle) * direction;
	right_leg.x = body.x + (((right_leg.def_distance * cosf(sum_angle) * direction)) + (right_leg.spin_point * cosf(sum_spin) * direction));
	right_leg.y = body.y + ((right_leg.def_distance * sinf(sum_angle) * direction)) + (right_leg.spin_point * sinf(sum_spin));

	//左足
	left_leg.total_angle = body.total_angle + (left_leg.angle * direction);
	sum_angle = body.total_angle + (left_leg.def_angle * direction);
	sum_spin = (left_leg.spin_angle + left_leg.total_angle) * direction;
	left_leg.x = body.x + (((left_leg.def_distance * cosf(sum_angle) * direction)) + (left_leg.spin_point * cosf(sum_spin) * direction));
	left_leg.y = body.y + ((left_leg.def_distance * sinf(sum_angle) * direction)) + (left_leg.spin_point * sinf(sum_spin));

	//右腕
	right_arm.total_angle = body.total_angle + (right_arm.angle * direction);
	sum_angle = body.total_angle + (right_arm.def_angle * direction);
	sum_spin = (right_arm.spin_angle + right_arm.total_angle) * direction;
	right_arm.x = body.x + (((right_arm.def_distance * cosf(sum_angle) * direction) + (right_arm.spin_point * cosf(sum_spin) * direction)));
	right_arm.y = body.y + ((right_arm.def_distance * sinf(sum_angle) * direction) + (right_arm.spin_point * sinf(sum_spin)));

	//左腕
	left_arm.total_angle = body.total_angle + (left_arm.angle * direction);
	sum_angle = body.total_angle + (left_arm.def_angle * direction);
	sum_spin = (left_arm.spin_angle + left_arm.total_angle) * direction;
	left_arm.x = body.x + (((left_arm.def_distance * cosf(sum_angle) * direction) + (left_arm.spin_point * cosf(sum_spin) * direction)));
	left_arm.y = body.y + ((left_arm.def_distance * sinf(sum_angle) * direction) + (left_arm.spin_point * sinf(sum_spin)));
}

//攻撃1（速射弾）
void Player::Attack1(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	shared_ptr<AbstractBullet> bul;
	float shoot_angle = (reverse ? PI : 0.0f); //向きによって撃つ角度を決定
	//攻撃(決定)のボタンが押されていたら
	if (key->KeyCheck(Attack)) {
		attack.flag = true; //攻撃フラグをtrueに
		attack.stop = true; //停止フラグをtrueに
		//初めて攻撃ボタンを押したか押してしばらくしたら
		if (attack.time % 12 == 0) {
			//エネルギーがある場合
			if (0 < attack.energy) {
				bul = bullet->SetBullet(0, x, y, 16.0f, shoot_angle); //弾を発射sound
				sound->PlaySoundEffect(7); //効果音を鳴らす
				attack.energy--; //エネルギーを消費
				attack.res_time = res_time; //回復時間を設定
			}
			//ない場合
			else {
				sound->PlaySoundEffect(3); //効果音を鳴らす
			}
		}
		attack.time++; //攻撃している時間を増加
	}
	else {
		attack.flag = false; //攻撃フラグをfalseに
		attack.stop = false; //停止フラグをfalseに
		attack.time = 0; //押している時間を初期化
	}
}

//攻撃2（操作弾）
void Player::Attack2(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	float shoot_angle = (reverse ? PI : 0.0f); //向きによって撃つ角度を決定
	//攻撃(決定)のボタンが押されていたら
	if (key->KeyCheck(Attack)) {
		attack.flag = true; //攻撃フラグをtrueに
		attack.stop = true; //停止フラグをtrueに
		//初めて攻撃ボタンを押したら
		if (attack.time == 0) {
			//エネルギーがある場合
			if (1 < attack.energy) {
				player_bullet = bullet->SetBullet(1, x, y, 8.0f, shoot_angle); //弾を発射
				sound->PlaySoundEffect(8); //効果音を鳴らす
				attack.energy -= 2; //エネルギーを消費
				attack.res_time = res_time; //回復時間を設定
			}
			//ない場合
			else {
				sound->PlaySoundEffect(3); //効果音を鳴らす
			}
		}
		attack.time++; //攻撃している時間を増加
	}
	else {
		player_bullet.reset(); //弾の権利を放棄
		attack.flag = false; //攻撃フラグをfalseに
		attack.stop = false; //停止フラグをfalseに
		attack.time = 0; //押している時間を初期化
	}
}

//攻撃3（ロケットハンド）
void Player::Attack3(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	float shoot_angle = (reverse ? PI : 0.0f); //向きによって撃つ角度を決定
	//攻撃していない状態で攻撃(決定)のボタンが押されたら
	if (key->KeyCheckOnce(Attack) && !attack.flag) {
		//エネルギーがある場合
		if (1 < attack.energy) {
			attack.flag = true; //攻撃フラグをtrueに
			attack.stop = true; //停止フラグをtrueに
			player_bullet = bullet->SetBullet(2, x, y, 16.0f, shoot_angle); //弾を発射
			sound->PlaySoundEffect(6); //効果音を鳴らす
			attack.energy -= 2; //エネルギーを消費
			attack.res_time = res_time; //回復時間を設定
		}
		//ない場合
		else {
			sound->PlaySoundEffect(3); //効果音を鳴らす
		}
	}
	//攻撃中なら
	if (attack.flag) {
		attack.time++; //攻撃している時間を増加
		//弾が消えたら
		if (player_bullet.use_count() <= 1) {
			player_bullet.reset(); //弾の権利を放棄
			attack.flag = false; //攻撃フラグをfalseに
			attack.stop = false; //停止フラグをfalseに
			attack.time = 0; //押している時間を初期化
		}
	}
}

//攻撃4（ダッシュ）
void Player::Attack4(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	//攻撃していない状態で攻撃(決定)のボタンが押されたら
	if (key->KeyCheckOnce(Attack) && !attack.flag) {
		//エネルギーがある場合
		if (1 < attack.energy) {
			inv_time = DAMAGE_INV_TIME; //無敵時間を設定
			flying_flag = true; //飛行フラグをtrueに
			attack.flag = true; //攻撃フラグをtrueに
			attack.stop = false; //停止フラグをfalseに
			player_bullet = bullet->SetBullet(3, x, y, 0.0f, 0.0f); //弾を発射
			sound->PlaySoundEffect(9); //効果音を鳴らす
			attack.energy -= 2; //エネルギーを消費
			attack.res_time = res_time; //回復時間を設定
		}
		//ない場合
		else {
			sound->PlaySoundEffect(3); //効果音を鳴らす
		}
	}
	//攻撃中なら
	if (attack.flag) {
		if (player_bullet != NULL) {
			player_bullet->SetX(x); //座標を合わせる
			player_bullet->SetY(y);
		}
		//一定時間経過したら
		if (30 == attack.time) {
			inv_time = 0; //無敵時間を0に
			flying_flag = false; //飛行フラグをfalseに
			attack.stop = true; //停止フラグをtrueに
			player_bullet->SetEndFlag(true); //弾を消す
			player_bullet.reset();//弾の権利を放棄
			player_bullet = NULL;
		}
		else if (attack.time < 30) {
			sx = (reverse ? -8.0f : 8.0f); //向きによって速度を決定
			sy = 0.0f;
		}
		else if (36 < attack.time) {
			attack.flag = false; //攻撃フラグをfalseに
			attack.stop = false; //停止フラグをfalseに
			attack.time = 0; //押している時間を初期化
		}
		attack.time++; //攻撃している時間を増加
	}
}

//位置の調節
void Player::AdjustPosition(std::shared_ptr<MapChipManager> map, bool event_flag) {
	//取得用クラス
	shared_ptr<AbstractMapChip> mapchip;

	bool left_hit = false; //左側が当たっているか
	bool right_hit = false; //右側が当たっているか
	bool top_hit = false; //上側が当たっているか
	bool bottom_hit = false; //下側が当たっているか

	float sub = 0.0f; //足場にどれだけめり込んでいるか

	//乗っている足場の速度の合計
	float mx = map->GetPlusSpeedX(hit[1].x, hit[1].y + 0.1f, hit[1].size);
	float my = map->GetPlusSpeedY(hit[1].x, hit[1].y + 0.1f, hit[1].size);

	//加速度
	float accel = 0.3f;

	float left = 0.0f; //画面左端
	float right = (float)WINDOW_X; //画面右端
	float top = 0.0f; //画面上
	float bottom = (float)WINDOW_Y; //画面底

	//角度を設定
	angle += spin_speed;

	//左右の判定から行う

	//行く予定の座標を決定
	x += sx + mx;

	//当たり判定の更新
	HitUpdate();

	//イベント中でなければ画面内に収める
	/*if (!event_flag) {
		if (fx < left + hit_size) {
			fx = left + hit_size;
			left_hit = true; //左側が当たったことに
		}
		if (right - hit_size < fx) {
			fx = right - hit_size;
			right_hit = true; //右側が当たったことに
		}
	}*/

	//マップチップとの接触判定
	for (int i = 0; i < 2; i++)
	{
		//mapchip = map->HitCheckLeft(x, y, hit[i].size);
		mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			left_hit = true; //左側が当たったことに
			sub = (hit[i].x - hit[i].size) - (mapchip->GetX() + 4.0f * mapchip->GetSizeX()); //めり込み具合を計算
			//x = mapchip->GetX() + 4.0f * mapchip->GetSizeX() + hit_size;
			x += fabsf(sub);
			sx = 0.0f;
			angle = 0.0f;
			spin_speed = 0.0f;
			HitUpdate(); //当たり判定の更新
			//操作不可能なら
			if (!move_flag) {
				flying_flag = false; //飛行終了
				move_flag = true; //操作可能に
			}
			mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			right_hit = true; //右側が当たったことに
			sub = (hit[i].x + hit[i].size) - (mapchip->GetX() - 4.0f * mapchip->GetSizeX()); //めり込み具合を計算
			//x = mapchip->GetX() - 4.0f * mapchip->GetSizeX() - hit_size;
			x -= fabsf(sub);
			sx = 0.0f;
			angle = 0.0f;
			spin_speed = 0.0f;
			HitUpdate(); //当たり判定の更新
			//操作不可能なら
			if (!move_flag) {
				flying_flag = false; //飛行終了
				move_flag = true; //操作可能に
			}
			mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//両側が当たっていたら
	if (left_hit && right_hit) {
		hp = 0; //HPを0に
		damaged = true;
		//速度を初期化
		sx = 0.0f;
		sy = 0.0f;
		return;
	}

	//次に上下の判定

	//ジャンプ中
	if (jump_flag) {
		//ジャンプが押されていてダメージを受けていなければ
		if (commando[Jump][0] && !damaged) {
			jump_time++; //時間を増加
		}
		//押されてなかったら
		else {
			jump_time = JUMP_TIME_MAX; //下降開始
		}
	}

	//上昇時間に達した場合
	if (jump_flag && jump_time >= JUMP_TIME_MAX && !flying_flag) {
		if (fabsf(sy) < 0.4f) sy = 0.4f;
		sy += fabsf(sy * accel); //速度を1.3(0.7)倍する
		if (JUMP_SPEED < sy) sy = JUMP_SPEED;
	}

	//行く予定の座標を決定
	y += sy + my;

	//当たり判定の更新
	HitUpdate();

	//イベント中でなければ画面内に収める
	/*if (!event_flag) {
		if (y < top + hit_size) {
			y = top + hit_size;
			top_hit = true; //上側が当たったことに
		}
		if (bottom - hit_size < y) {
			y = bottom - hit_size;
			bottom_hit = true; //下側が当たったことに
		}
	}*/

	//マップチップとの接触判定
	for (int i = 0; i < 2; i++)
	{
		//頭上
		if (!hit[i].check_top) continue;
		mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			top_hit = true; //上側が当たったことに
			sub = (hit[i].y - hit[i].size) - (mapchip->GetY() + 8.0f * mapchip->GetSizeY()); //めり込み具合を計算
			//y = mapchip->GetY() + 8.0f * mapchip->GetSizeY() + hit_size;
			y += fabsf(sub);
			sy = 0.0f;
			angle = 0.0f;
			spin_speed = 0.0f;
			HitUpdate(); //当たり判定の更新
			//操作不可能なら
			if (!move_flag) {
				flying_flag = false; //飛行終了
				move_flag = true; //操作可能に
			}
			mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		//足下
		if (!hit[i].check_bottom) continue;
		mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		if (mapchip != NULL) bottom_hit = true; //下側が当たったことに
		while (mapchip != NULL && 0.0f < sy && !(mapchip->GetThrough() && through_flag)) {
			sub = (hit[i].y + hit[i].size) - (mapchip->GetY()); //めり込み具合を計算
			//y = mapchip->GetY() - hit_size;
			y -= fabsf(sub);
			sy = 0.0f;
			angle = 0.0f;
			spin_speed = 0.0f;
			jump_flag = false; //フラグをfalseに
			HitUpdate(); //当たり判定の更新
			//操作不可能なら
			if (!move_flag) {
				flying_flag = false; //飛行終了
				move_flag = true; //操作可能に
			}
			mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//両側が当たっていたら
	if (top_hit && bottom_hit) {
		hp = 0; //HPを0に
		damaged = true;
		//速度を初期化
		sx = 0.0f;
		sy = 0.0f;
		return;
	}

	//画面外に落ちたら
	if (bottom + 128.0f < y) {
		hp = 0; //HPを0に
		damaged = true;
		//速度を初期化
		sx = 0.0f;
		sy = 0.0f;
		return;
	}

	HitUpdate(); //当たり判定の更新

	step_mapchip = map->HitCheckBottom(hit[1].x, hit[1].y + 1.0f, hit[1].size); //乗っている足場を設定

	//ジャンプしていないで空中にいる場合
	if (step_mapchip == NULL && !jump_flag && !flying_flag) {
		jump_flag = true; //フラグをtrueに
		jump_time = JUMP_TIME_MAX; //下降開始
	}

	//空中にいたら
	if (!bottom_hit) {
		through_flag = false; //すり抜け終了
	}

	//乗っているマップチップを確認
	map->CheckStep(hit[1].x, hit[1].y + 1.0f, hit[1].size);

	SetGraphic(); //表示するポーズを設定
	SetParts(); //パーツの配置
}

//攻撃
void Player::AttackCheck(shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {
	//武器変更のボタンが押されていたら
	if (key->KeyCheckOnce(L) && !attack.flag) {
		weapon--; //武器を変更
		sound->PlaySoundEffect(0); //効果音を鳴らす
	}
	if (key->KeyCheckOnce(R) && !attack.flag) {
		weapon++; //武器を変更
		sound->PlaySoundEffect(0); //効果音を鳴らす
	}
	//武器の番号が0未満なら
	if (weapon < 0) {
		weapon = weapon_max - 1; //最大値にする
	}
	//武器の番号が最大値を超えたら
	if (weapon_max <= weapon) {
		weapon = 0; //0にする
	}

	if (!move_flag) return; //操作不可ならここで終了

	if ((unsigned)weapon < attack_move.size()) {
		(this->*attack_move[weapon])(bullet, effect, key, sound);
	}

	//攻撃していない場合
	if (!attack.flag) {
		//回復時間がある場合
		if (0 < attack.res_time) {
			attack.res_time--; //回復時間を減少
			//回復時間が0の場合
			if (attack.res_time == 0 && attack.energy < max_energy) {
				attack.energy++; //エネルギーを回復
				//エネルギーが回復しきっていない場合
				if (attack.energy < max_energy) {
					attack.res_time = res_time; //回復時間を設定
				}
			}
		}
	}

}

//敵に当たっているか
void Player::HitCheckEnemy(shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (0 < inv_time) return; //無敵時間中なら終了

	int damage = (move_flag) ? 0 : 65535; //大砲で飛んでいるかで接触ダメージを設定

	for (int i = 0; i < 2; i++)
	{
		//敵に当たっていたら
		if (enemy->HitCheckChara(x, y, hit[i].size, effect, sound, damage)) {
			//大砲で飛んでいないなら
			if (move_flag) {
				hp--; //HPを減少
				damaged = true; //ダメージ状態
				damage_time = DAMAGE_TIME_MAX; //ダメージ時間を設定
				inv_time = DAMAGE_INV_TIME; //無敵時間を設定
				sound->PlaySoundEffect(10); //効果音を鳴らす
			}
			return; //終了
		}
	}
}

//弾に当たっているか
void Player::HitCheckBullet(shared_ptr<BulletManager> bullet, shared_ptr<Sound> sound) {
	if (0 < inv_time || !move_flag) return; //無敵時間中なら終了
	
	for (int i = 0; i < 2; i++) {
		//弾に当たっていたら
		if (0 < bullet->HitCheckChara(x, y, hit[i].size, true, false)) {
			hp--; //HPを減少
			damaged = true; //ダメージ状態
			damage_time = DAMAGE_TIME_MAX; //ダメージ時間を設定
			inv_time = DAMAGE_INV_TIME; //無敵時間を設定
			sound->PlaySoundEffect(10); //効果音を鳴らす
			return; //終了
		}
	}
}

//アイテムに当たっているか
bool Player::HitCheckItem(float cx, float cy, float hit_size) {
	for (int i = 0; i < 2; i++)
	{
		float dif_x = cx - hit[i].x;
		float dif_y = cy - hit[i].y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + hit[i].size) {
			return true;
		}
	}
	return false;
}

//描画するか設定
void Player::SetDrawFlag(bool flag) {
	draw_flag = flag;
}

//操作できるか設定
void Player::SetMoveFlag(bool flag) {
	move_flag = flag;
}

//鍵の数を取得
int Player::GetKeyNum() {
	return key_num;
}

//鍵の数を設定
void Player::SetKeyNum(int num) {
	key_num = num;
}

//武器の数を設定
void Player::SetWeaponMax(int num) {
	weapon_max = num;
}

//必ず行う更新
void Player::AbsUpdate() {

}

//更新
void Player::Update(shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){
	Move(effect, key, sound);
	SetKeyRecord(key); //キーの履歴を更新
	
	//無敵時間中なら
	if (0 < inv_time) {
		inv_time--; //無敵時間を減少
	}


}

//描画
void Player::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	int image1 = image->GetCharaImage(0, 0); //自機の画像を取得（胴）
	int image2 = image->GetCharaImage(1, 0); //自機の画像を取得（頭）
	int image3 = image->GetCharaImage(2, 0); //自機の画像を取得（腕）
	int image4 = image->GetCharaImage(3, 0); //自機の画像を取得（足）

	//HP周りの画像を取得
	int en_point = image->GetEffectImage(9, 0);
	int life = image->GetEffectImage(8, 0);
	int life_bar = image->GetEffectImage(7, 0);

	//武器回りの画像を取得
	int weapon_window = image->GetEffectImage(13, 0);
	int weapon_name = image->GetEffectImage(14, weapon);

	int trance = 255; //透明度

	//HP周りの描画
	Display::Draw(172.0f, (float)WINDOW_Y - 32.0f, false, 0.0f, life_bar);
	for (int i = 0; i < hp; i++) {
		Display::Draw(74.0f + (16.0f * i), (float)WINDOW_Y - 32.0f, false, 0.0f, life);
	}
	for (int i = 0; i < attack.energy; i++) {
		Display::Draw(238.0f + (24.0f * i), (float)WINDOW_Y - 32.0f, false, 0.0f, en_point);
	}
	//武器の表示
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y - 32.0f, false, 0.0f, weapon_window);
	Display::Draw((float)WINDOW_X / 2, (float)WINDOW_Y - 32.0f, false, 0.0f, weapon_name);

	//無敵時間中は点滅する
	if (0 < inv_time) {
		if (inv_time % 10 < 5) {
			trance = 96;
		}
		else {
			trance = 192;
		}
	}

	//自機の描画
	if (draw_flag) {

		camera->Draw(right_arm.x, right_arm.y, reverse, right_arm.total_angle, image3, 1.0f, DX_BLENDMODE_ALPHA, trance); //自機を描画（腕）
		camera->Draw(head.x, head.y, reverse, head.total_angle, image2, 1.0f, DX_BLENDMODE_ALPHA, trance); //自機を描画（頭）
		camera->Draw(right_leg.x, right_leg.y, reverse, right_leg.total_angle, image4, 1.0f, DX_BLENDMODE_ALPHA, trance);//自機を描画（足）
		camera->Draw(left_leg.x, left_leg.y, reverse, left_leg.total_angle, image4, 1.0f, DX_BLENDMODE_ALPHA, trance);//自機を描画（足）
		camera->Draw(body.x, body.y, reverse, body.total_angle, image1, 1.0f, DX_BLENDMODE_ALPHA, trance); //自機を描画（胴）
		camera->Draw(left_arm.x, left_arm.y, reverse, left_arm.total_angle, image3, 1.0f, DX_BLENDMODE_ALPHA, trance);//自機を描画（腕）

		for (auto &h : hit)
		{
			camera->HitDraw(h.x, h.y, h.size); //当たり判定を描画
		}

	}

	//DrawFormatString(0, 100, GetColor(0, 0, 255), "%d %d", through_flag, key_num);
	//DrawFormatString(0, 128, GetColor(0, 0, 255), "%d %f %f %f", weapon, x, y, hit[1].y);
	
}
