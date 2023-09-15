#include <DxLib.h>
#include "Common.h"

// ------------------------------------------------------------------------ //
//							プレイヤーの初期セット							//
// ------------------------------------------------------------------------ //
void PlayerInit() {
	// ---------------------------- // 
	//		キャラ情報セット		//
	// ---------------------------- //
	if (CHOICESTAGE == 1) {
		Player[0].pos = VGet(200.0f, 700.0f, 0.0f);		 // 草原
	}
	else {
		Player[0].pos = VGet(500.0f, 800.0f, 2800.0f); // 洞窟
	}
	Player[0].mode = STAND;
	Player[0].direction = DOWN;
	Player[0].charahitinfo.Height = PC_HEIGHT;
	Player[0].charahitinfo.Width = PC_WIDTH;
	Player[0].charahitinfo.CenterPosition = Player[0].pos;
	Player[0].move = VGet(0.0f, 0.0f, 0.0f);

	// ---------------------------- // 
	//		キャラモデルセット		//
	// ---------------------------^ // 
	Player[0].model = MV1LoadModel("..\\Data\\Ninja\\忍者_sub.mv1");
	Player[0].attachidx = MV1AttachAnim(Player[0].model, 0, plyanim_nutral);
	Player[0].anim_totaltime = MV1GetAttachAnimTotalTime(Player[0].model, Player[0].attachidx);
	// アニメーションして動いてもその場で動いてるような状態
	Player[0].rootflm = MV1SearchFrame(Player[0].model, "root");
	MV1SetFrameUserLocalMatrix(Player[0].model, Player[0].rootflm, MGetIdent());
	Player[0].playtime = 0.0f;
}

// ------------------------------------------------------------------------ //
//							プレイヤーの移動関数							//
// ------------------------------------------------------------------------ //
void PlayerMove() {
	key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// 下を押下 手前に移動
	if (key & PAD_INPUT_DOWN) {
		Player[0].move.x = 0.0f;
		Player[0].move.z = -12.0f;
		Player[0].direction = DOWN;
	}

	// 上を押下 奥に移動
	if (key & PAD_INPUT_UP) {
		Player[0].move.x = 0.0f;
		Player[0].move.z = +12.0f;
		Player[0].direction = UP;
	}

	// 左を押下 左に移動
	if (key & PAD_INPUT_LEFT) {
		Player[0].move.x = -12.0f;
		Player[0].move.z = 0.0f;
		Player[0].direction = LEFT;
		// 下を押下 手前に移動
		if (key & PAD_INPUT_DOWN) {
			Player[0].move.z = -12.0f;
			Player[0].direction = 0.5f;
		}
		// 上を押下 奥に移動
		if (key & PAD_INPUT_UP) {
			Player[0].move.z = +12.0f;
			Player[0].direction = 1.5f;
		}
	}

	// 右方向への移動処理
	if (key & PAD_INPUT_RIGHT) {
		Player[0].move.x = +12.0f;
		Player[0].move.z = 0.0f;
		Player[0].direction = RIGHT;
		// 下を押下 手前に移動
		if (key & PAD_INPUT_DOWN) {
			Player[0].move.z = -12.0f;
			Player[0].direction = 3.5f;
		}
		// 上を押下 奥に移動
		if (key & PAD_INPUT_UP) {
			Player[0].move.z = +12.0f;
			Player[0].direction = 2.5f;
		}
	}

	// 攻撃ボタン Dキー
/*	if (key & PAD_INPUT_6) {
		if (Player[0].mode == RUN) {
			if ((Player[0].direction >= 0) & (Player[0].direction < 1)) {
				Player[0].move.z += (Player[0].direction - 1) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (-Player[0].direction) * Player[0]_ATTACK_SPEED;
			}
			else if ((Player[0].direction >= 1) & (Player[0].direction < 2)) {
				Player[0].move.z += (Player[0].direction - 1) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (Player[0].direction - 2) * Player[0]_ATTACK_SPEED;
			}
			else if ((Player[0].direction >= 2) & (Player[0].direction < 3)) {
				Player[0].move.z += (3 - Player[0].direction) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (Player[0].direction - 2) * Player[0]_ATTACK_SPEED;
			}
			else if ((Player[0].direction >= 3) & (Player[0].direction < 4)) {
				Player[0].move.z += (3 - Player[0].direction) * Player[0]_ATTACK_SPEED;
				Player[0].move.x += (4 - Player[0].direction) * Player[0]_ATTACK_SPEED;
			}
		}
		AnimationPlayer[0](ATTACK);
		Player[0].playtime = 0.0f;
		MV1SetAttachAnimTime(Player[0].model, Player[0].attachidx, Player[0].playtime);
	}
*/
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		Player[0].pos.y += 30.0f;
		Player[0].move.y = 40.0f;
	}
	if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {
		Player[0].move.x *= 2.0f;
		Player[0].move.z *= 2.0f;
	}

	if (Player[0].pos.x < -5300.0f) {
		if (Player[0].move.x < 0.0)
			Player[0].move.x = 0.0f;
	}
	if (Player[0].pos.x > 6150.0f) {
		if (Player[0].move.x > 0.0)
			Player[0].move.x = 0.0f;
	}
	if (Player[0].pos.z > 4000.0f) {
		if (Player[0].move.z > 0)
			Player[0].move.z = 0.0f;
	}
	if (Player[0].pos.z < -6640.0f) {
		if (Player[0].move.z < 0)
			Player[0].move.z = 0.0f;
	}
}



