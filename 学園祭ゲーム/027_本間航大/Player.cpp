#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//							プレイヤーの初期セット							//
// ------------------------------------------------------------------------ //
void PlayerInit() {
	// ---------------------------- // 
	//		キャラ情報セット		//
	// ---------------------------- //
	Player.pos = VGet(0.0f, 500.0f, 0.0f);		 // 草原
	Player.mode = STAND;
	Player.direction = DOWN;
	Player.charahitinfo.Height = PC_HEIGHT;
	Player.charahitinfo.Width = PC_WIDTH;
	Player.charahitinfo.CenterPosition = Player.pos;
	Player.move = VGet(0.0f, 0.0f, 0.0f);

	// ---------------------------- // 
	//		キャラモデルセット		//
	// ---------------------------^ // 
	Player.model = MV1LoadModel("..\\Data\\Ninja\\忍者.mv1");
	Player.attachidx = MV1AttachAnim(Player.model, 0, plyanim_nutral);
	Player.anim_totaltime = MV1GetAttachAnimTotalTime(Player.model, Player.attachidx);
	// アニメーションして動いてもその場で動いてるような状態
	Player.rootflm = MV1SearchFrame(Player.model, "root");
	MV1SetFrameUserLocalMatrix(Player.model, Player.rootflm, MGetIdent());
	Player.playtime = 0.0f;
}

// ------------------------------------------------------------------------ //
//							プレイヤーの移動関数							//
// ------------------------------------------------------------------------ //
void PlayerMove() {
	key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// 下を押下 手前に移動
	if (key & PAD_INPUT_DOWN) {
		Player.move.x = 0.0f;
		Player.move.z = +12.0f;
		Player.direction = DOWN;
	}

	// 上を押下 奥に移動
	if (key & PAD_INPUT_UP) {
		Player.move.x = 0.0f;
		Player.move.z = -12.0f;
		Player.direction = UP;
	}

	// 左を押下 左に移動
	if (key & PAD_INPUT_LEFT) {
		Player.move.x = +12.0f;
		Player.move.z = 0.0f;
		Player.direction = LEFT;
		// 下を押下 手前に移動
		if (key & PAD_INPUT_DOWN) {
			Player.move.z = 12.0f;
			Player.direction = 0.5f;
		}
		// 上を押下 奥に移動
		if (key & PAD_INPUT_UP) {
			Player.move.z = -12.0f;
			Player.direction = 1.5f;
		}
	}

	// 右方向への移動処理
	if (key & PAD_INPUT_RIGHT) {
		Player.move.x = -12.0f;
		Player.move.z = 0.0f;
		Player.direction = RIGHT;
		// 下を押下 手前に移動
		if (key & PAD_INPUT_DOWN) {
			Player.move.z = +12.0f;
			Player.direction = 3.5f;
		}
		// 上を押下 奥に移動
		if (key & PAD_INPUT_UP) {
			Player.move.z = -12.0f;
			Player.direction = 2.5f;
		}
	}

	// 攻撃ボタン Dキー
/*	if (key & PAD_INPUT_6) {
		if (Player.mode == RUN) {
			if ((Player.direction >= 0) & (Player.direction < 1)) {
				Player.move.z += (Player.direction - 1) * PLAYER_ATTACK_SPEED;
				Player.move.x += (-Player.direction) * PLAYER_ATTACK_SPEED;
			}
			else if ((Player.direction >= 1) & (Player.direction < 2)) {
				Player.move.z += (Player.direction - 1) * PLAYER_ATTACK_SPEED;
				Player.move.x += (Player.direction - 2) * PLAYER_ATTACK_SPEED;
			}
			else if ((Player.direction >= 2) & (Player.direction < 3)) {
				Player.move.z += (3 - Player.direction) * PLAYER_ATTACK_SPEED;
				Player.move.x += (Player.direction - 2) * PLAYER_ATTACK_SPEED;
			}
			else if ((Player.direction >= 3) & (Player.direction < 4)) {
				Player.move.z += (3 - Player.direction) * PLAYER_ATTACK_SPEED;
				Player.move.x += (4 - Player.direction) * PLAYER_ATTACK_SPEED;
			}
		}
		AnimationPlayer(ATTACK);
		Player.playtime = 0.0f;
		MV1SetAttachAnimTime(Player.model, Player.attachidx, Player.playtime);
	}
*/
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		Player.move.y = 1200.0f;
		printf("aaaaaaaa");
	}

	if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {
		Player.move.x *= 2.0f;
		Player.move.z *= 2.0f;
	}

	if (Player.pos.x < -5300.0f) {
		if (Player.move.x < 0.0)
			Player.move.x = 0.0f;
	}
	if (Player.pos.x > 6640.0f) {
		if (Player.move.x > 0.0)
			Player.move.x = 0.0f;
	}
	if (Player.pos.z > 4000.0f) {
		if (Player.move.z > 0)
			Player.move.z = 0.0f;
	}
	if (Player.pos.z < -6640.0f) {
		if (Player.move.z < 0)
			Player.move.z = 0.0f;
	}
}



